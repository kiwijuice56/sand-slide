#include "sand_simulation.h"
#include "elements/element.h"
#include "elements/all_elements.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

// Faster versions of math functions for graphics 

inline int fast_floor(double x) noexcept {
    return (int) x - (x < (int) x);
}

template<typename T>
inline T fast_cos(T x) noexcept {
    constexpr T tp = 1./(2.0 * 3.14159265);
    x *= tp;
    x -= T(.25) + fast_floor(x + T(.25));
    x *= T(16.) * (std::abs(x) - T(.5));
    return x;
}

SandSimulation::SandSimulation() {
    AllElements::fill_elements(&elements);
    for (int i = 0; i <= 4096; i++) {
        if (i > 167 && i < 2048) {
            continue;
        }
        elements[i]->my_sim = this;
        elements[i]->custom_id = i;
    }  

    draw_data = PackedByteArray();
    draw_data.resize(width * height * 3);

    visited.resize(width * height);
    cells.resize(width * height);
    chunks.resize(chunk_width * chunk_height);
}

SandSimulation::~SandSimulation() {}

// Run the simulation `iterations` times
void SandSimulation::step(int iterations) {
    time += 0.001;
    for (int i = 0; i < iterations; i++) {
        for (int chunk = chunks.size() - 1; chunk >= 0; chunk--) {
            if (chunks[chunk] == 0) {
                continue;
            }
            for (int row = chunk_size - 1; row >= 0; row--) {
                for (int col = 0; col < chunk_size; col++) {
                    int r_row = (chunk / chunk_width) * chunk_size + row;
                    int r_col = (chunk % chunk_width) * chunk_size + col;
                    if (r_row >= height || r_col >= width) {
                        continue;
                    }
                    
                    if (visited[r_row * width + r_col]) {
                        visited[r_row * width + r_col] = false;
                    } else {
                        // Elements (including custom) are stored using numbers 0 - 4096
                        // Taps share the ID of their spawn material, but offset by 4097
                        if (cells[r_row * width + r_col] > 4096 && randf() < 1.0 / 16) {
                            int x = cells[r_row * width + r_col] - 4097;
                            // Grow in all 8 directions
                            grow(r_row + 1, r_col, 0, x); grow(r_row + 1, r_col + 1, 0, x); grow(r_row + 1, r_col - 1, 0, x); grow(r_row - 1, r_col, 0, x); 
                            grow(r_row - 1, r_col + 1, 0, x); grow(r_row - 1, r_col - 1, 0, x); grow(r_row, r_col + 1, 0, x); grow(r_row, r_col - 1, 0, x);
                        } else {
                            elements[get_cell(r_row, r_col)]->process(this, r_row, r_col);
                        }
                    }
                }
            }
        }
    }
}

// Swap the elements at the two cells if the first cell has a higher density
void SandSimulation::move_and_swap(int row, int col, int row2, int col2) {
    if (!in_bounds(row, col) || !in_bounds(row2, col2)) 
        return;
    if (get_cell(row, col) == 15 || get_cell(row2, col2) == 15) {
        return;
    }
    if (elements[get_cell(row2, col2)]->get_state() == 0)
        return;
    if (elements[get_cell(row, col)]->get_state() != 0)
        if (elements[get_cell(row, col)]->get_density() <= elements[get_cell(row2, col2)]->get_density()) 
            return;
    int old = get_cell(row, col);
    set_cell(row, col, get_cell(row2, col2));
    set_cell(row2, col2, old);
}

// Move the `replacer` element into the given cell if it is of type `food`
// A `food` value of -1 is equivalent to all elements
void SandSimulation::grow(int row, int col, int food, int replacer) {
    if (!in_bounds(row, col)) 
        return;

    if (food == -1) {
        // Since only explosions/lasers grow into all cells, we run a check for explosion resistance
        if (randf() >= (1.0 - elements[get_cell(row, col)]->get_explode_resistance())) 
            return;
    } else if (get_cell(row, col) != food) 
        return;
    set_cell(row, col, replacer);
}

void SandSimulation::liquid_process(int row, int col, int fluidity) {
    for (int i = 0; i < fluidity; i++) {
        double random = randf();
        int new_col = col + (random < (0.5 + 1.0 / 32) ? 1 : -1);
        if (random < 1.0 / 32)
            new_col = col;
        
        int new_row = row + (is_swappable(row, col, row + 1, new_col) ? 1 : 0);
        if (is_swappable(row, col, new_row, new_col) && (randf() < 0.6 || !is_swappable(row, col, new_row + 1, new_col))) {
            move_and_swap(row, col, new_row, new_col);
            row = new_row;
            col = new_col;
        }
    }
}

// Returns the amount of cells of `type` surrounding the given cell
int SandSimulation::touch_count(int row, int col, int type) {
    int touches = 0;

    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (x == 0 && y == 0 || !in_bounds(row + y, col + x)) 
                continue;
            if (get_cell(row + y, col + x) == type) 
                touches++;
        }
    }
    return touches;
}

// Returns the amount of cells of `type` surrounding the given cell, but only checking
// immediate four closest cells
int SandSimulation::cardinal_touch_count(int row, int col, int type) {
    int touches = 0;

    if (in_bounds(row - 1, col) && get_cell(row - 1, col) == type)
        touches++;
    if (in_bounds(row + 1, col) && get_cell(row + 1, col) == type)
        touches++;
    if (in_bounds(row, col - 1) && get_cell(row, col - 1) == type)
        touches++;
    if (in_bounds(row, col + 1) && get_cell(row, col + 1) == type)
        touches++;
    return touches;
}

bool SandSimulation::in_bounds(int row, int col) {
    return row >= 0 && col >= 0 && row < height && col < width;
}

// Check if the cell is touching an element intended to destroy life, such as acid
bool SandSimulation::is_poisoned(int row, int col) {
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (x == 0 && y == 0 || !in_bounds(row + y, col + x)) 
                continue;
            int c = get_cell(row + y, col + x);
            
            if (elements[get_cell(row + y, col + x)]->get_toxicity() == 1) 
                return true;
        }
    } 
    return false; 
}

// Check if a cell is touching any hot elements
bool SandSimulation::is_on_fire(int row, int col) {
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (x == 0 && y == 0 || !in_bounds(row + y, col + x))
                continue;
            if (elements[get_cell(row + y, col + x)]->get_temperature() == 1) 
                return true;
        }
    } 
    return false;
}

// Check if a cell is touching any cold elements
bool SandSimulation::is_cold(int row, int col) {
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (x == 0 && y == 0 || !in_bounds(row + y, col + x))
                continue;
            if (elements[get_cell(row + y, col + x)]->get_temperature() == -1) 
                return true;
        }
    } 
    return false;
}


bool SandSimulation::is_swappable(int row, int col, int row2, int col2) {
    if (!in_bounds(row, col) || !in_bounds(row2, col2)) 
        return false;

    if (elements[get_cell(row2, col2)]->get_state() == 0)
        return false;

    if (elements[get_cell(row, col)]->get_state() != 0 && elements[get_cell(row, col)]->get_density() <= elements[get_cell(row2, col2)]->get_density()) 
        return false;

    return true;
}

inline float SandSimulation::randf() { 
    g_seed = (214013 * g_seed + 2531011); 
    return ((g_seed>>16) & 0x7FFF) / (double) 0x7FFF; 
} 

inline float SandSimulation::randf_loc(int row, int col) { 
    int n_seed = (214013 * row + 2531011 * col +  row * col * 234152); 
    n_seed = ((214012313 * n_seed + 2521331011) >> 22) << 22; 
    n_seed = (114062313 * n_seed + 253101411);
    return ((n_seed>>16) & 0x7FFF) / (double) 0x7FFF; 
} 

int SandSimulation::get_cell(int row, int col) {
    // Taps should be mostly indestructible, so treat them as the wall element for processing
    if (cells[row * width + col] > 4096) {
        return 15;
    }
    return cells[row * width + col];
}

void SandSimulation::set_cell(int row, int col, int type) { 
    if (get_cell(row, col) == 15 && type != 0) {
        return;
    }

    if (cells[row * width + col] == 0 && type != 0) 
        chunks[(row / chunk_size) * chunk_width + (col / chunk_size)]++;
    else if (cells[row * width + col] != 0 && type == 0) 
        chunks[(row / chunk_size) * chunk_width + (col / chunk_size)]--;
    
    visited[row * width + col] = type != 0;
    cells[row * width + col] = type;
}

void SandSimulation::draw_cell(int row, int col, int type) {
    set_cell(row, col, type);
    visited[row * width + col] = false;
}

int SandSimulation::get_chunk(int c) {
    return chunks[c];
}

int SandSimulation::get_width() {
    return width;
}

int SandSimulation::get_height() {
    return height;
}

void SandSimulation::resize(int new_width, int new_height) {
    std::vector<int> temp(cells);
    
    cells.clear();
    cells.resize(new_width * new_height);
    
    visited.clear();
    visited.resize(new_width * new_height);

    chunk_width = (int) std::ceil(new_width / (float) chunk_size);
    chunk_height = (int) std::ceil(new_height / (float) chunk_size);
    
    chunks.clear();
    chunks.resize(chunk_width * chunk_height);

    draw_data.resize(new_width * new_height * 3);

    // Data has to be copied cell-by-cell since the dimensions of the vectors changed
    for (int row = height - 1, new_row = new_height - 1; row >= 0 && new_row >= 0; row--, new_row--) {
        for (int col = 0, new_col = 0; col < width && new_col < new_width; col++, new_col++) {
            cells[new_row * new_width + new_col] = temp[row * width + col];
            if (cells[new_row * new_width + new_col] != 0) 
                chunks[(new_row / chunk_size) * chunk_width + (new_col / chunk_size)]++;
        }
    }

    width = new_width;
    height = new_height;   
}

void SandSimulation::set_chunk_size(int new_size) {
    chunk_size = new_size;
    resize(width, height);
}

PackedByteArray SandSimulation::get_data() {
    PackedByteArray data = PackedByteArray();
    data.resize(width * height * 4);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int id = cells[y * width + x];
            int idx = (y * width + x) * 4;
            data.set(idx + 0, (id & 0xFF000000) >> 24);
            data.set(idx + 1, (id & 0x00FF0000) >> 16);
            data.set(idx + 2, (id & 0x0000FF00) >> 8);
            data.set(idx + 3, (id & 0x000000FF) >> 0);
        }
    }
    return data;
}

// Graphic methods

void SandSimulation::initialize_flat_color(Dictionary dict) {
    flat_color.clear();
    flat_color.resize(4097);
    Array ids = dict.keys();
    for (int i = 0; i < dict.size(); i++) {
        int id = ids[i];
        Flat f;
        f.init = true;

        f.color = int(dict[id]) >> 8;
        flat_color[id] = f;
    }
}

void SandSimulation::initialize_gradient_color(Dictionary dict) {
    gradient_color.clear();
    gradient_color.resize(4097);

    Array ids = dict.keys();
    for (int i = 0; i < dict.size(); i++) {
        int id = ids[i];
        Gradient g;
        g.init = true;

        Array arr = dict[id];

        g.colors[0] = int(arr[0]) >> 8;
        g.colors[1] = int(arr[1]) >> 8;
        g.colors[2] = int(arr[2]) >> 8;
        g.colors[3] = int(arr[3]) >> 8;
        g.colors[4] = int(arr[4]) >> 8;
        g.offsets[0] = arr[5];
        g.offsets[1] = arr[6];
        g.offsets[2] = arr[7];

        gradient_color[id] = g;
    }
}

void SandSimulation::initialize_metal_color(Dictionary dict) {
    metal_color.clear();
    metal_color.resize(4097);
    
    Array ids = dict.keys();
    for (int i = 0; i < dict.size(); i++) {
        int id = ids[i];
        Gradient g;
        g.init = true;

        Array arr = dict[id];

        g.colors[0] = int(arr[0]) >> 8;;
        g.colors[1] = int(arr[1]) >> 8;;

        metal_color[id] = g;
    }
}

void SandSimulation::initialize_fluid_color(Dictionary dict) {
    fluid_color.clear();
    fluid_color.resize(4097);
    
    Array ids = dict.keys();
    for (int i = 0; i < dict.size(); i++) {
        int id = ids[i];
        Gradient f;
        f.init = true;

        Array arr = dict[id];

        f.colors[0] = int(arr[0]) >> 8;
        f.colors[1] = int(arr[1]) >> 8;
        f.colors[2] = int(arr[2]) >> 8;

        fluid_color[id] = f;
    }
}

uint32_t SandSimulation::lerp_color(uint32_t a, uint32_t b, double x) {
    uint32_t re = uint32_t(((a & 0xFF0000) >> 16) * (1.0 - x) + ((b & 0xFF0000) >> 16) * x) << 16;
    uint32_t gr = uint32_t(((a & 0x00FF00) >> 8) * (1.0 - x) + ((b & 0x00FF00) >> 8) * x) << 8;
    uint32_t bl = uint32_t((a & 0x0000FF) * (1.0 - x) + (b & 0x0000FF) * x);
    return re | gr | bl;
}

uint32_t SandSimulation::add_color(uint32_t a, uint32_t b) {
    uint32_t re = (((a & 0xFF0000) >> 16) + ((b & 0xFF0000) >> 16));
    if (re > 255) re = 255;
    uint32_t gr = (((a & 0x00FF00) >> 8) + ((b & 0x00FF00) >> 8));
    if (gr > 255) gr = 255;
    uint32_t bl = ((a & 0x0000FF) + (b & 0x0000FF));
    if (bl > 255) bl = 255;
    return (re << 16) | (gr << 8) | bl;
}

// https://thebookofshaders.com/glossary/?search=smoothstep
double SandSimulation::smooth_step(double edge0, double edge1, double x) {
    // Scale, bias and saturate x to 0..1 range
    x = (x - edge0) / (edge1 - edge0);
    if (x < 0.0) x = 0.0;
    if (x > 1.0) x = 1.0;
    // Evaluate polynomial
    return x * x * (3.0 - 2.0 * x);
}

uint32_t SandSimulation::get_color(int row, int col, bool flat_mode) {
    int id = cells[row * width + col];

    if (id > 4096) {
        return 0xFFFFFF;
    }

    if (fluid_color[id].init) {
        Gradient f = fluid_color[id];

        if (id == 127) {
            f.colors[0] = lerp_color(0x4396e8, 0x62eb4d, 0.5 + fast_cos(time * 24.0) * 0.5);
        }

        if (flat_mode) {
            return lerp_color(f.colors[0], f.colors[1], 0.5);
        }

        double x = touch_count(row, col, id) / 8.0;
        uint32_t base_color = lerp_color(f.colors[1], f.colors[0], row / double(height));
        return lerp_color(base_color, f.colors[2], 1.0 - x);
    }

    if (flat_color[id].init) {
        return flat_color[id].color;
    }

    if (gradient_color[id].init) {
        Gradient g = gradient_color[id];
        if (flat_mode) {
            return lerp_color(g.colors[0], g.colors[4], 0.5);
        }
        double x = touch_count(row, col, id) / 8.0;

        uint32_t out = lerp_color(g.colors[0], g.colors[1], smooth_step(0.0, g.offsets[0], x));
        out = lerp_color(out, g.colors[2], smooth_step(g.offsets[0], g.offsets[1], x));
        out = lerp_color(out, g.colors[3], smooth_step(g.offsets[1], g.offsets[2], x));
        out = lerp_color(out, g.colors[4], smooth_step(g.offsets[2], 1.0, x));

        return out;
    }

    if (metal_color[id].init) {
        Gradient g = metal_color[id];
        if (flat_mode) {
            return lerp_color(g.colors[0], g.colors[1], 0.5);
        }

        return lerp_color(g.colors[0], g.colors[1], row / double(height));
    }

    if (id == 117) {
        return uint32_t(randf() * 0xFFFFFF) << 8;
    }

    if (id == 131) {
        double x = (touch_count(row, col, 131) + touch_count(row, col, 0)) / 8.0;
        return lerp_color(0xFFFFFF, flat_color[0].color, x);
    }

    if (id == 151 || id == 152) {
        double x = 2.0 * (time - fast_floor(time)) + randf_loc(row, col) * 0.06 + 0.006 * touch_count(row, col, id);
        x = x - fast_floor(x);

        uint32_t out = lerp_color(0xba52ff, 0xff5297, smooth_step(0.0, 1.0/6, x));
        out = lerp_color(out, 0xffba52, smooth_step(1.0/6, 2.0/6, x));
        out = lerp_color(out, 0x97ff52, smooth_step(2.0/6, 3.0/6, x));
        out = lerp_color(out, 0x52ffba, smooth_step(3.0/6, 4.0/6, x));
        out = lerp_color(out, 0x52ffba, smooth_step(4.0/6, 5.0/6, x));
        out = lerp_color(out, 0xba52ff, smooth_step(5.0/6, 6.0/6, x));

        return out;
    }

    if (id == 160) {
        double x = time - fast_floor(time);
        if (x < 1.0 / 2) {
            return 0xf786c0;
        } else  {
            return 0x86f7f4;
        }
    }

    return 0xFFFFFF;
}

PackedByteArray SandSimulation::get_color_image(bool flat_mode) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint32_t col = get_color(y, x, flat_mode);
            
            int idx = (y * width + x) * 3;
            draw_data.set(idx, (col & 0xFF0000) >> 16);
            draw_data.set(idx + 1, (col & 0x00FF00) >> 8);
            draw_data.set(idx + 2, col & 0x0000FF);
        }
    }
    return draw_data;
}

void SandSimulation::initialize_custom_elements(Dictionary dict) {
    custom_elements.clear();
    custom_elements.resize(4097);
    
    Array ids = dict.keys();
    for (int i = 0; i < dict.size(); i++) {
        int id = ids[i];
        CustomElement f;
        f.init = true;

        Array arr = dict[id];

        f.state = int(arr[0]);
        f.density = float(arr[1]);
        f.viscosity = float(arr[2]);
        f.conductivity = float(arr[3]);
        f.temperature = float(arr[4]);
        f.flammability = float(arr[5]);
        f.reactivity = float(arr[6]);
        f.durability = float(arr[7]);
        f.power = float(arr[8]);
        f.explosive = bool(arr[9]);
        f.evaporable = bool(arr[10]);
        f.alive = bool(arr[11]);
        f.toxic = bool(arr[12]);
        f.attractive = bool(arr[13]);
        f.infectious = bool(arr[14]);
        f.soluble = bool(arr[15]);
        f.reactant_1 = int(arr[16]);
        f.product_1 = int(arr[17]);
        f.reactant_2 = int(arr[18]);
        f.product_2 = int(arr[19]);
        f.reactant_3 = int(arr[20]);
        f.product_3 = int(arr[21]);


        custom_elements[id] = f;
    }
}

void SandSimulation::_bind_methods() {
    ClassDB::bind_method(D_METHOD("step"), &SandSimulation::step);
    ClassDB::bind_method(D_METHOD("in_bounds"), &SandSimulation::in_bounds);
    ClassDB::bind_method(D_METHOD("get_cell"), &SandSimulation::get_cell);
    ClassDB::bind_method(D_METHOD("set_cell"), &SandSimulation::set_cell);
    ClassDB::bind_method(D_METHOD("draw_cell"), &SandSimulation::draw_cell);
    ClassDB::bind_method(D_METHOD("get_data"), &SandSimulation::get_data);
    ClassDB::bind_method(D_METHOD("get_width"), &SandSimulation::get_width);
    ClassDB::bind_method(D_METHOD("get_height"), &SandSimulation::get_height);
    ClassDB::bind_method(D_METHOD("resize"), &SandSimulation::resize);
    ClassDB::bind_method(D_METHOD("set_chunk_size"), &SandSimulation::set_chunk_size);
    ClassDB::bind_method(D_METHOD("get_color_image"), &SandSimulation::get_color_image);

    ClassDB::bind_method(D_METHOD("initialize_custom_elements"), &SandSimulation::initialize_custom_elements);

    ClassDB::bind_method(D_METHOD("initialize_flat_color"), &SandSimulation::initialize_flat_color);
    ClassDB::bind_method(D_METHOD("initialize_gradient_color"), &SandSimulation::initialize_gradient_color);
    ClassDB::bind_method(D_METHOD("initialize_fluid_color"), &SandSimulation::initialize_fluid_color);
    ClassDB::bind_method(D_METHOD("initialize_metal_color"), &SandSimulation::initialize_metal_color);
}
