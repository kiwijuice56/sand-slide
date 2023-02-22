#include "sand_simulation.h"

#include "elements/sand.h"
#include "elements/rock.h"
#include "elements/void.h"
#include "elements/water.h"
#include "elements/polliwog.h"
#include "elements/fire.h"
#include "elements/smoke.h"
#include "elements/algae_green.h"
#include "elements/sandduck.h"
#include "elements/explosion.h"
#include "elements/lead_azide.h"
#include "elements/soil.h"
#include "elements/seed.h"
#include "elements/germ_seed.h"
#include "elements/grass.h"
#include "elements/wall.h"
#include "elements/dust.h"
#include "elements/iron.h"
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
#include "elements/powder_a.h"
#include "elements/liquid_powder.h"
#include "elements/mercury.h"
#include "elements/potassium.h"
#include "elements/potassium_explosion.h"
#include "elements/hydrogen.h"
#include "elements/hydrogen_explosion.h"
#include "elements/penguin.h"
#include "elements/burning_oil.h"
#include "elements/gold.h"
#include "elements/molten_gold.h"
#include "elements/molten_glass.h"
#include "elements/algae_red.h"
#include "elements/algae_brown.h"
#include "elements/cool_lava.h"
#include "elements/obsidian.h"
#include "elements/vapor.h"
#include "elements/acid_water.h"
#include "elements/oxidized_potassium.h"
#include "elements/burning_potassium.h"
#include "elements/rust.h"
#include "elements/powder_b.h"
#include "elements/powder_c.h"
#include "elements/kuiper.h"
#include "elements/firework_a.h"
#include "elements/firework_b.h"
#include "elements/firework_c.h"
#include "elements/firework_trail.h"
#include "elements/salt.h"
#include "elements/salt_water.h"
#include "elements/fish_left.h"
#include "elements/fish_right.h"
#include "elements/strange.h"
#include "elements/meteor_a.h"
#include "elements/meteor_b.h"
#include "elements/meteor_c.h"
#include "elements/lapis.h"
#include "elements/ruby.h"
#include "elements/emerald.h"
#include "elements/worm_hole.h"
#include "elements/iodine.h"
#include "elements/iodine_gas.h"
#include "elements/iodine_liquid.h"
#include "elements/snow.h"
#include "elements/slime.h"
#include "elements/cloud.h"
#include "elements/ice_explosion.h"
#include "elements/ice_dust.h"
#include "elements/icework_a.h"
#include "elements/icework_b.h"
#include "elements/icework_c.h"
#include "elements/ice_bomb.h"
#include "elements/beam.h"
#include "elements/nanobot.h"
#include "elements/sandstone.h"
#include "elements/carbon_dioxide.h"
#include "elements/osmium.h"
#include "elements/dry_sponge.h"
#include "elements/wet_sponge.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

SandSimulation::SandSimulation() {
    // Each element has a single object instance so that the program
    // can use polymorphism rather than explicitly stating which method
    // is called for each element type

    // The order in the vector is arbitrary, but it must match the list order in main.gd
    elements.resize(128);
    elements.at(0) = new Void();
    elements.at(1) = new Sand();
    elements.at(2) = new Rock();
    elements.at(3) = new Water();
    elements.at(4) = new Polliwog();
    elements.at(5) = new Fire();
    elements.at(6) = new Smoke();
    elements.at(7) = new AlgaeGreen();
    elements.at(8) = new SandDuck();
    elements.at(9) = new Explosion();
    elements.at(10) = new LeadAzide();
    elements.at(11) = new Soil();
    elements.at(12) = new Seed();
    elements.at(13) = new GerminatedSeed();
    elements.at(14) = new Grass();
    elements.at(15) = new Wall();
    elements.at(16) = new Dust();
    elements.at(17) = new Iron();
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
    elements.at(42) = new PowderA();
    elements.at(43) = new LiquidPowder();
    elements.at(44) = new Mercury();
    elements.at(45) = new Potassium();
    elements.at(46) = new PExplosion();
    elements.at(47) = new Hydrogen();
    elements.at(48) = new HydrogenExplosion();
    elements.at(49) = new Penguin();
    elements.at(50) = new BurningOil();
    elements.at(51) = new Gold();
    elements.at(52) = new MoltenGold();
    elements.at(53) = new MoltenGlass();
    elements.at(54) = new AlgaeRed();
    elements.at(55) = new AlgaeBrown();
    elements.at(56) = new CoolLava();
    elements.at(57) = new Obsidian();
    elements.at(58) = new Vapor();
    elements.at(59) = new AcidWater();
    elements.at(60) = new OxidizedPotassium();
    elements.at(61) = new BurningPotassium();
    elements.at(62) = new Rust();
    elements.at(63) = new PowderB();
    elements.at(64) = new PowderB();
    elements.at(65) = new Kuiper();
    elements.at(66) = new FireworkA();
    elements.at(67) = new FireworkB();
    elements.at(68) = new FireworkC();
    elements.at(69) = new FireworkTrail();
    elements.at(70) = new Salt();
    elements.at(71) = new SaltWater();
    elements.at(72) = new FishLeft();
    elements.at(73) = new FishRight();
    elements.at(74) = new Strange();
    elements.at(75) = new MeteorA();
    elements.at(76) = new MeteorB();
    elements.at(77) = new MeteorC();
    elements.at(78) = new Lapis();
    elements.at(79) = new Ruby();
    elements.at(80) = new Emerald();
    elements.at(81) = new WormHole();
    elements.at(82) = new Iodine();
    elements.at(83) = new IodineGas();
    elements.at(84) = new IodineLiquid();
    elements.at(85) = new Snow();
    elements.at(86) = new Slime();
    elements.at(87) = new Cloud();
    elements.at(88) = new IceExplosion();
    elements.at(89) = new IceDust();
    elements.at(90) = new IceworkA();
    elements.at(91) = new IceworkB();
    elements.at(92) = new IceworkC();
    elements.at(93) = new IceBomb();
    elements.at(94) = new Beam();
    elements.at(95) = new Nanobot();
    elements.at(96) = new CarbonDioxide();
    elements.at(97) = new Sandstone();
    elements.at(98) = new Osmium();
    elements.at(99) = new DrySponge();
    elements.at(100) = new WetSponge();

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
                    int rRow = (chunk / chunk_width) * chunk_size + row;
                    int rCol = (chunk % chunk_width) * chunk_size + col;
                    if (rRow >= height || rCol >= width)
                        continue;
                    if (visited.at(rRow * width + rCol)) 
                        visited.at(rRow * width + rCol) = false;
                    else {
                        // Taps are the element offset by 128; get_cell() returns only the first few bits, so we can use this to spawn the element!
                        if (cells.at(rRow * width + rCol) >= 128 && randf() < 1.0 / 16) {
                            int x = cells.at(rRow * width + rCol) - 128;
                            grow(rRow + 1, rCol, 0, x);
                            grow(rRow + 1, rCol + 1, 0, x);
                            grow(rRow + 1, rCol - 1, 0, x);
                            grow(rRow - 1, rCol, 0, x);
                            grow(rRow - 1, rCol + 1, 0, x);
                            grow(rRow - 1, rCol - 1, 0, x);
                            grow(rRow, rCol, 0, x);
                            grow(rRow, rCol + 1, 0, x);
                            grow(rRow, rCol - 1, 0, x);
                        } else {
                            elements.at(get_cell(rRow, rCol))->process(this, rRow, rCol);
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
        // This should probably be inside the explosion element code, but this is more convenient
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
            if (c == 10 || c == 21 || c == 22 || c == 35 || c == 44 || c == 59 || c == 84) 
                return true;
        }
    } 
    return false; 
}

// Check if a cell is touching any flame producing elements
bool SandSimulation::is_on_fire(int row, int col) {
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (x == 0 && y == 0 || !in_bounds(row + y, col + x))
                continue;
            int c = get_cell(row + y, col + x);
            if (
                c == 24 || c == 5 || c == 9 || c == 20 || c == 26 || c == 34 || c == 37 || c == 38 || 
                c == 40 || c == 46 || c == 48 || c == 50 || c == 52 || c == 61 || c == 66 || c == 67 || c == 68 || c == 69) 
                return true;
        }
    } 
    return false;
}

// Check if a cell is touching any flame producing elements
bool SandSimulation::is_cold(int row, int col) {
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (x == 0 && y == 0 || !in_bounds(row + y, col + x))
                continue;
            int c = get_cell(row + y, col + x);
            if (c == 87 || c == 88 || c == 89 || c == 90 || c == 91 || c == 92 || c == 96) 
                return true;
        }
    } 
    return false;
}


bool SandSimulation::is_swappable(int row, int col, int row2, int col2) {
    if (!in_bounds(row, col) || !in_bounds(row2, col2)) 
        return false;

    if (elements.at(get_cell(row, col))->get_density() <= elements.at(get_cell(row2, col2))->get_density()) 
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

// Do nothing...
void SandSimulation::clean_up() {
    
}

void SandSimulation::_bind_methods() {
    ClassDB::bind_method(D_METHOD("step"), &SandSimulation::step);

    ClassDB::bind_method(D_METHOD("move_and_swap"), &SandSimulation::move_and_swap);
    ClassDB::bind_method(D_METHOD("is_swappable"), &SandSimulation::is_swappable);
    ClassDB::bind_method(D_METHOD("grow"), &SandSimulation::grow);
    ClassDB::bind_method(D_METHOD("touch_count"), &SandSimulation::touch_count);
    ClassDB::bind_method(D_METHOD("cardinal_touch_count"), &SandSimulation::cardinal_touch_count);
    ClassDB::bind_method(D_METHOD("in_bounds"), &SandSimulation::in_bounds);

    ClassDB::bind_method(D_METHOD("get_cell"), &SandSimulation::get_cell);
    ClassDB::bind_method(D_METHOD("set_cell"), &SandSimulation::set_cell);
    ClassDB::bind_method(D_METHOD("draw_cell"), &SandSimulation::draw_cell);
    ClassDB::bind_method(D_METHOD("get_chunk"), &SandSimulation::get_chunk);

    ClassDB::bind_method(D_METHOD("get_draw_data"), &SandSimulation::get_draw_data);

    ClassDB::bind_method(D_METHOD("get_width"), &SandSimulation::get_width);
    ClassDB::bind_method(D_METHOD("get_height"), &SandSimulation::get_height);
    ClassDB::bind_method(D_METHOD("resize"), &SandSimulation::resize);
    ClassDB::bind_method(D_METHOD("set_chunk_size"), &SandSimulation::set_chunk_size);
    
    ClassDB::bind_method(D_METHOD("clean_up"), &SandSimulation::clean_up);
}
