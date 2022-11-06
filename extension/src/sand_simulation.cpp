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
#include "elements/lead_azide.h"
#include "elements/soil.h"
#include "elements/seed.h"
#include "elements/germ_seed.h"
#include "elements/grass.h"
#include "elements/marble.h"
#include "elements/dust.h"
#include "elements/steel.h"
#include "elements/wood.h"
#include "elements/ice.h"
#include "elements/lava.h"
#include "elements/acid.h"
#include "elements/acid_gas.h"
#include "elements/fairy.h"
#include "elements/blue_fire.h"
#include "elements/glass.h"
#include "elements/laser.h"
#include "elements/crystal.h"
#include "elements/air.h"
#include "elements/black_hole.h"
#include "elements/oil.h"
#include "elements/urchin.h"
#include "elements/dragon.h"
#include "elements/critter.h"
#include "elements/nuclear_explosion.h"
#include "elements/uranium.h"
#include "elements/neutron_beam.h"
#include "elements/electricity.h"
#include "elements/plasma.h"
#include "elements/electricity_storm.h"
#include "elements/storm_plasma.h"
#include "elements/hurricane.h"
#include "elements/powder.h"
#include "elements/liquid_powder.h"


#include <godot_cpp/core/class_db.hpp>
#include <random>

using namespace godot;

SandSimulation::SandSimulation() {
    // Each element has a single object instance so that the program
    // can use polymorphism rather than explicity stating which method
    // is called for each element type

    // The order in the vector is arbitrary, but it must match the list order in main.gd
    elements.resize(64);
    elements.at(0) = new Void();
    elements.at(1) = new Sand();
    elements.at(2) = new Rock();
    elements.at(3) = new Water();
    elements.at(4) = new Polliwog();
    elements.at(5) = new Fire();
    elements.at(6) = new Smoke();
    elements.at(7) = new Algae();
    elements.at(8) = new SandDuck();
    elements.at(9) = new Explosion();
    elements.at(10) = new LeadAzide();
    elements.at(11) = new Soil();
    elements.at(12) = new Seed();
    elements.at(13) = new GerminatedSeed();
    elements.at(14) = new Grass();
    elements.at(15) = new Marble();
    elements.at(16) = new Dust();
    elements.at(17) = new Steel();
    elements.at(18) = new Wood();
    elements.at(19) = new Ice();
    elements.at(20) = new Lava();
    elements.at(21) = new Acid();
    elements.at(22) = new AcidGas();
    elements.at(23) = new Fairy();
    elements.at(24) = new BlueFire();
    elements.at(25) = new Glass();
    elements.at(26) = new Laser();
    elements.at(27) = new Crystal();
    elements.at(28) = new Air();
    elements.at(29) = new BlackHole();
    elements.at(30) = new Oil();
    elements.at(31) = new Urchin();
    elements.at(32) = new Dragon();
    elements.at(33) = new Critter();
    elements.at(34) = new NuclearExplosion();
    elements.at(35) = new Uranium();
    elements.at(36) = new NeutronBeam();
    elements.at(37) = new Electricity();
    elements.at(38) = new Plasma();
    elements.at(39) = new ElectricityStorm();
    elements.at(40) = new StormPlasma();
    elements.at(41) = new Hurricane();
    elements.at(42) = new Powder();
    elements.at(43) = new LiquidPowder();

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

    // Keep a vector of active chunk indices
    std::vector<int> active_chunks;
    for (int chunk = 0; chunk < chunks.size(); chunk++) {
        if (chunks.at(chunk) != 0) {
            active_chunks.resize(active_chunks.size() + 1);
            active_chunks.at(active_chunks.size() - 1) = chunk;
        }
    }
    
    std::uniform_int_distribution<std::mt19937::result_type> randChunk(0, active_chunks.size() - 1);

    // Randomly select a cell to process within an active chunk
    // Do more iterations when more chunks are active to prevent speed inconsistencies
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
        // Since only explosions/lasers grow into all cells, we run a check for explosion resistance
        // This should probably be inside the explosion element code, but this is more convenient
        if (randf() >= (1.0 - elements.at(get_cell(row, col))->get_explode_resistance())) {
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
            if (x == 0 && y == 0 || !in_bounds(row + y, col + x)) {
                continue;
            }
            int c = get_cell(row + y, col + x);
            if (c == 10 || c == 21 || c == 22 || c == 35) {
                return true;
            }
        }
    } 
    return false; 
}

// Check if a cell is touching any flame producing elements
bool SandSimulation::is_on_fire(int row, int col) {
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (x == 0 && y == 0 || !in_bounds(row + y, col + x)) {
                continue;
            }
            int c = get_cell(row + y, col + x);
            if (c == 24 || c == 5 || c == 9 || c == 20 || c == 26 || c == 34 || c == 37 || c == 38 || c == 40) {
                return true;
            }
        }
    } 
    return false;
}

inline float SandSimulation::randf() { 
    g_seed = (214013 * g_seed + 2531011); 
    return ((g_seed>>16) & 0x7FFF) / (double) 0x7FFF; 
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

void SandSimulation::set_chunk_size(int new_size) {
    chunk_size = new_size;
    resize(width, height);
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
    ClassDB::bind_method(D_METHOD("cardinal_touch_count"), &SandSimulation::cardinal_touch_count);
    ClassDB::bind_method(D_METHOD("in_bounds"), &SandSimulation::in_bounds);

    ClassDB::bind_method(D_METHOD("get_cell"), &SandSimulation::get_cell);
    ClassDB::bind_method(D_METHOD("set_cell"), &SandSimulation::set_cell);
    ClassDB::bind_method(D_METHOD("get_chunk"), &SandSimulation::get_chunk);

    ClassDB::bind_method(D_METHOD("get_draw_data"), &SandSimulation::get_draw_data);

    ClassDB::bind_method(D_METHOD("get_width"), &SandSimulation::get_width);
    ClassDB::bind_method(D_METHOD("get_height"), &SandSimulation::get_height);
    ClassDB::bind_method(D_METHOD("resize"), &SandSimulation::resize);
    ClassDB::bind_method(D_METHOD("set_chunk_size"), &SandSimulation::set_chunk_size);
    
    ClassDB::bind_method(D_METHOD("clean_up"), &SandSimulation::clean_up);
}