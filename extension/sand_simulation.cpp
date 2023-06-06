#include "sand_simulation.h"
#include "elements/element.h"
#include "elements/all_elements.h"

using namespace godot;

SandSimulation::SandSimulation() {
    AllElements::fill_elements(&elements);

    draw_data = PackedByteArray();

    draw_data.resize(width * height);
    draw_data.fill(0);
    visited.resize(width * height);
    cells.resize(width * height);
    chunks.resize(chunk_width * chunk_height);
}

SandSimulation::~SandSimulation() {}

// Run the simulation `iterations` times
void SandSimulation::step(int iterations) {
    for (int i = 0; i < iterations; i++) {
        for (int chunk = chunks.size() - 1; chunk >= 0; chunk--) {
            if (chunks.at(chunk) == 0)
                continue;
            for (int row = chunk_size - 1; row >= 0; row--) {
                for (int col = 0; col < chunk_size; col++) {
                    int r_row = (chunk / chunk_width) * chunk_size + row;
                    int r_col = (chunk % chunk_width) * chunk_size + col;
                    if (r_row >= height || r_col >= width)
                        continue;
                    if (visited.at(r_row * width + r_col)) 
                        visited.at(r_row * width + r_col) = false;
                    else {
                        // Taps are the element offset by 128; get_cell() returns only the first few bits, so we can use this to spawn the element!
                        if (cells.at(r_row * width + r_col) >= 128 && randf() < 1.0 / 16) {
                            int x = cells.at(r_row * width + r_col) - 128;
                            grow(r_row + 1, r_col, 0, x);
                            grow(r_row + 1, r_col + 1, 0, x);
                            grow(r_row + 1, r_col - 1, 0, x);
                            grow(r_row - 1, r_col, 0, x);
                            grow(r_row - 1, r_col + 1, 0, x);
                            grow(r_row - 1, r_col - 1, 0, x);
                            grow(r_row, r_col, 0, x);
                            grow(r_row, r_col + 1, 0, x);
                            grow(r_row, r_col - 1, 0, x);
                        } else {
                            elements.at(get_cell(r_row, r_col))->process(this, r_row, r_col);
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
    if (elements.at(get_cell(row2, col2))->get_state() == 0)
        return;
    if (elements.at(get_cell(row, col))->get_state() != 0)
        if (elements.at(get_cell(row, col))->get_density() <= elements.at(get_cell(row2, col2))->get_density()) 
            if (get_cell(row, col) != get_cell(row2, col2))
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
        if (randf() >= (1.0 - elements.at(get_cell(row, col))->get_explode_resistance())) 
            return;
    } else if (get_cell(row, col) != food) 
        return;
    set_cell(row, col, replacer);
}

void SandSimulation::liquid_process(int row, int col, int fluidity) {
    for (int i = 0; i < fluidity; i++) {
        int new_col = col + (randf() < 0.5 ? 1 : -1);
        if (randf() < 1.0 / 32)
            new_col = col;
        int new_row = row + (is_swappable(row, col, row + 1, new_col) && randf() > 0.2 ? 1 : 0);
        if (is_swappable(row, col, new_row, new_col) && (randf() < 0.3 || !is_swappable(row, col, new_row + 1, new_col))) {
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
            if (elements.at(get_cell(row + y, col + x))->get_toxicity() == 1) 
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
            if (elements.at(get_cell(row + y, col + x))->get_temperature() == 1) 
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
            if (elements.at(get_cell(row + y, col + x))->get_temperature() == -1) 
                return true;
        }
    } 
    return false;
}


bool SandSimulation::is_swappable(int row, int col, int row2, int col2) {
    if (!in_bounds(row, col) || !in_bounds(row2, col2)) 
        return false;

    if (elements.at(get_cell(row2, col2))->get_state() == 0)
        return false;

    if (elements.at(get_cell(row, col))->get_state() != 0 && elements.at(get_cell(row, col))->get_density() <= elements.at(get_cell(row2, col2))->get_density()) 
        return false;

    return true;
}

inline float SandSimulation::randf() { 
    g_seed = (214013 * g_seed + 2531011); 
    return ((g_seed>>16) & 0x7FFF) / (double) 0x7FFF; 
} 

int SandSimulation::get_cell(int row, int col) {
    if (cells.at(row * width + col) > 127)
        return 15;
    return cells.at(row * width + col);
}

void SandSimulation::set_cell(int row, int col, int type) {
    if (cells.at(row * width + col) == 0 && type != 0) 
        chunks.at((row / chunk_size) * chunk_width + (col / chunk_size))++;
    else if (cells.at(row * width + col) != 0 && type == 0) 
        chunks.at((row / chunk_size) * chunk_width + (col / chunk_size))--;
    
    visited.at(row * width + col) = type != 0;
    cells.at(row * width + col) = type;
    draw_data.set(row * width + col, type);
}

void SandSimulation::draw_cell(int row, int col, int type) {
    set_cell(row, col, type);
    visited.at(row * width + col) = false;
}


int SandSimulation::get_chunk(int c) {
    return chunks.at(c);
}

PackedByteArray SandSimulation::get_data() {
    return draw_data;
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

    draw_data.resize(new_width * new_height);
    draw_data.fill(0);

    // Data has to be copied cell-by-cell since the dimensions of the vectors changed
    for (int row = height - 1, new_row = new_height - 1; row >= 0 && new_row >= 0; row--, new_row--) {
        for (int col = 0, new_col = 0; col < width && new_col < new_width; col++, new_col++) {
            cells.at(new_row * new_width + new_col) = temp.at(row * width + col);
            draw_data.set(new_row * new_width + new_col, temp.at(row * width + col));
            if (cells.at(new_row * new_width + new_col) != 0) 
                chunks.at((new_row / chunk_size) * chunk_width + (new_col / chunk_size))++;
        }
    }

    width = new_width;
    height = new_height;   
}

void SandSimulation::set_chunk_size(int new_size) {
    chunk_size = new_size;
    resize(width, height);
}

PackedByteArray SandSimulation::get_color_image() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            
        }
    }
    return draw_data;
}

void SandSimulation::set_element_material_map(Dictionary dict) {
    element_material_map = dict;
}

void SandSimulation::_bind_methods() {
    ClassDB::bind_method(D_METHOD("step"), &SandSimulation::step);
    ClassDB::bind_method(D_METHOD("in_bounds"), &SandSimulation::in_bounds);
    ClassDB::bind_method(D_METHOD("get_cell"), &SandSimulation::get_cell);
    ClassDB::bind_method(D_METHOD("set_cell"), &SandSimulation::set_cell);
    ClassDB::bind_method(D_METHOD("draw_cell"), &SandSimulation::draw_cell);
    ClassDB::bind_method(D_METHOD("get_data"), &SandSimulation::get_data);
    ClassDB::bind_method(D_METHOD("get_color_image"), &SandSimulation::get_color_image);
    ClassDB::bind_method(D_METHOD("get_width"), &SandSimulation::get_width);
    ClassDB::bind_method(D_METHOD("get_height"), &SandSimulation::get_height);
    ClassDB::bind_method(D_METHOD("resize"), &SandSimulation::resize);
    ClassDB::bind_method(D_METHOD("set_chunk_size"), &SandSimulation::set_chunk_size);
    ClassDB::bind_method(D_METHOD("set_element_material_map"), &SandSimulation::set_element_material_map);
}
