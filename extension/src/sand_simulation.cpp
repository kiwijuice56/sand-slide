#include "sand_simulation.h"

#include "elements/sand.h"
#include "elements/rock.h"
#include "elements/void.h"
#include "elements/water.h"
#include "elements/polliwog.h"
#include "elements/fire.h"
#include "elements/smoke.h"
#include "elements/algae.h"
#include "elements/sandduck.h"
#include "elements/explosion.h"
#include "elements/leadazide.h"
#include "elements/soil.h"
#include "elements/seed.h"
#include "elements/germinatedseed.h"
#include "elements/grass.h"
#include "elements/marble.h"
#include "elements/dust.h"

#include <godot_cpp/core/class_db.hpp>
#include <random>

using namespace godot;

SandSimulation::SandSimulation() {
    // Each element has a single object instance so that the program
    // can use polymorphism rather than explicity stating which method
    // is called for each element type

    elements.resize(32);
    Void* voidP = new Void();
    Sand* sand = new Sand();
    Rock* rock = new Rock();
    Water* water = new Water();
    Polliwog* polliwog = new Polliwog();
    Fire* fire = new Fire();
    Smoke* smoke = new Smoke();
    Algae* algae = new Algae();
    SandDuck* sand_duck = new SandDuck();
    Explosion* explosion = new Explosion();
    LeadAzide* lead_azide = new LeadAzide();
    Soil* soil = new Soil();
    Seed* seed = new Seed();
    GerminatedSeed* germinated_seed = new GerminatedSeed();
    Grass* grass = new Grass();
    Marble* marble = new Marble();
    Dust* dust = new Dust();

    elements.at(0) = voidP;
    elements.at(1) = sand;
    elements.at(2) = rock;
    elements.at(3) = water;
    elements.at(4) = polliwog;
    elements.at(5) = fire;
    elements.at(6) = smoke;
    elements.at(7) = algae;
    elements.at(8) = sand_duck;
    elements.at(9) = explosion;
    elements.at(10) = lead_azide;
    elements.at(11) = soil;
    elements.at(12) = seed;
    elements.at(13) = germinated_seed;
    elements.at(14) = grass;
    elements.at(15) = marble;
    elements.at(16) = dust;
    
    draw_data = PackedByteArray();

    draw_data.resize(width * height);
    draw_data.fill(0);
    cells.resize(width * height);
    chunks.resize(chunk_width * chunk_height);
}

SandSimulation::~SandSimulation() {}

// Run the simulation `iterations` times
void SandSimulation::step(int iterations) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randCell(0, chunk_size - 1);

    // Keep track of which chunks are active to iterate over
    std::vector<int> active_chunks;
    for (int chunk = 0; chunk < chunks.size(); chunk++) {
        if (chunks.at(chunk) != 0) {
            active_chunks.resize(active_chunks.size() + 1);
            active_chunks.at(active_chunks.size() - 1) = chunk;
        }
    }
    
    std::uniform_int_distribution<std::mt19937::result_type> randChunk(0, active_chunks.size() - 1);

    for (int i = 0; i < iterations * active_chunks.size(); i++) {
        int chunk = active_chunks.at(randChunk(rng));
        int row = std::min((unsigned int) get_height() - 1, (chunk / chunk_width) * chunk_size + randCell(rng));
        int col = std::min((unsigned int) get_width() - 1, (chunk % chunk_width) * chunk_size + randCell(rng));
        if (get_cell(row, col) == 0) {
            continue;
        }
        elements.at(get_cell(row, col))->process(this, row, col);
    }
    
}

// Swap the elements at the two cells if the first cell has a higher density
void SandSimulation::move_and_swap(int row, int col, int row2, int col2) {
    if (!in_bounds(row, col) || !in_bounds(row2, col2)) {
        return;
    }

    if (elements.at(get_cell(row, col))->get_density() <= elements.at(get_cell(row2, col2))->get_density()) {
        return;
    }

    int old = get_cell(row, col);
    set_cell(row, col, get_cell(row2, col2));
    set_cell(row2, col2, old);
}

// Move the `replacer` element into the given cell if it is of type `food`
// A `food` value of -1 is equivalent to all elements
void SandSimulation::grow(int row, int col, int food, int replacer) {
    if (!in_bounds(row, col)) {
        return;
    }
    if (food == -1) {
        float prob = elements.at(get_cell(row, col))->get_density() / 32.0;
        if (prob > Element::randf()) {
            return;
        }
    } else {
        if (get_cell(row, col) != food) {
            return;
        }
    }

    set_cell(row, col, replacer);
}

// Returns the amount of cells of `type` surrounding the given cell
int SandSimulation::touch_count(int row, int col, int type) {
    int touches = 0;
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (x == 0 && y == 0 || !in_bounds(row + y, col + x)) {
                continue;
            }
            if (get_cell(row + y, col + x) == type) {
                touches++;
            }
        }
    }
    return touches;
}

bool SandSimulation::in_bounds(int row, int col) {
    return row >= 0 && col >= 0 && row < height && col < width;
}

int SandSimulation::get_cell(int row, int col) {
    return cells.at(row * width + col);
}

void SandSimulation::set_cell(int row, int col, int type) {
    if (cells.at(row * width + col) == 0 && type != 0) {
        chunks.at((row / chunk_size) * chunk_width + (col / chunk_size))++;
    } else if (cells.at(row * width + col) != 0 && type == 0) {
        chunks.at((row / chunk_size) * chunk_width + (col / chunk_size))--;
    }
    cells.at(row * width + col) = type;
    draw_data.set(row * width + col, type);
}


int SandSimulation::get_chunk(int c) {
    return chunks.at(c);
}


PackedByteArray SandSimulation::get_draw_data() {
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
    
    chunk_width = (int) std::ceil(new_width / (float) chunk_size);
    chunk_height = (int) std::ceil(new_height / (float) chunk_size);
    
    chunks.clear();
    chunks.resize(chunk_width * chunk_height);

    draw_data.resize(new_width * new_height);
    draw_data.fill(0);

    // Data has to be copied cell-by-cell since the dimensions of the vectors changed
    for (int row = 0; row < std::min(new_height, height); row++) {
        for (int col = 0; col < std::min(new_width, width); col++) {
            cells.at(row * new_width + col) = temp.at(row * width + col);
            draw_data.set(row * new_width + col, temp.at(row * width + col));
            if (temp.at(row * width + col) != 0) {
                chunks.at((row / chunk_size) * chunk_width + (col / chunk_size))++;
            }
        }
    }

    width = new_width;
    height = new_height;   
}

// Handle created instances on program close
void SandSimulation::clean_up() {
    for (auto e : elements) {
        delete e;
    }
}

void SandSimulation::_bind_methods() {
    ClassDB::bind_method(D_METHOD("step"), &SandSimulation::step);

    ClassDB::bind_method(D_METHOD("move_and_swap"), &SandSimulation::move_and_swap);
    ClassDB::bind_method(D_METHOD("grow"), &SandSimulation::grow);
    ClassDB::bind_method(D_METHOD("touch_count"), &SandSimulation::touch_count);
    ClassDB::bind_method(D_METHOD("in_bounds"), &SandSimulation::in_bounds);

    ClassDB::bind_method(D_METHOD("get_cell"), &SandSimulation::get_cell);
    ClassDB::bind_method(D_METHOD("set_cell"), &SandSimulation::set_cell);
    ClassDB::bind_method(D_METHOD("get_chunk"), &SandSimulation::get_chunk);

    ClassDB::bind_method(D_METHOD("get_draw_data"), &SandSimulation::get_draw_data);

    ClassDB::bind_method(D_METHOD("get_width"), &SandSimulation::get_width);
    ClassDB::bind_method(D_METHOD("get_height"), &SandSimulation::get_height);
    ClassDB::bind_method(D_METHOD("resize"), &SandSimulation::resize);
    
    ClassDB::bind_method(D_METHOD("clean_up"), &SandSimulation::clean_up);
}