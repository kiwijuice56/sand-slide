#include "sand_simulation.h"

#include "elements/sand.h"
#include "elements/rock.h"
#include "elements/void.h"
#include "elements/water.h"

#include <godot_cpp/core/class_db.hpp>
#include <random>

using namespace godot;

SandSimulation::SandSimulation() {
    elements.resize(4);
    Void* voidP = new Void();
    Sand* sand = new Sand();
    Rock* rock = new Rock();
    Water* water = new Water();
    
    elements.at(0) = voidP;
    elements.at(1) = sand;
    elements.at(2) = rock;
    elements.at(3) = water;
    
    modified_cells = Dictionary();
    cells.resize(width * height);
}

SandSimulation::~SandSimulation() {}

void SandSimulation::step(int iterations) {
    modified_cells.clear();

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distWidth(0, width - 1);
    std::uniform_int_distribution<std::mt19937::result_type> distHeight(0, height - 1);
    for (int i = 0; i < iterations; i++) {
        int row = distHeight(rng);
        int col = distWidth(rng);
        if (get_cell(row, col) == 0) {
            continue;
        }
        elements.at(get_cell(row, col))->process(this, row, col);
    }
}

void SandSimulation::randomize() {

}

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

bool SandSimulation::in_bounds(int row, int col) {
    return row >= 0 && col >= 0 && row < height && col < width;
}

Dictionary SandSimulation::get_modified_cells() {
    return modified_cells;
}

int SandSimulation::get_cell(int row, int col) {
    return cells.at(row * width + col);
}

void SandSimulation::set_cell(int row, int col, int type) {
    cells.at(row * width + col) = type;
    get_modified_cells()[row * get_width() + col] = true;
}

void SandSimulation::resize(int new_width, int new_height) {
    std::vector<int> temp(cells);
   
    cells.clear();
    cells.resize(new_width * new_height);

    for (int row = 0; row < std::min(new_height, height); row++) {
        for (int col = 0; col < std::min(new_width, width); col++){
            cells.at(row * new_width + col) = temp.at(row * width + col);
        }
    }

    width = new_width;
    height = new_height;   
}

int SandSimulation::get_width() {
    return width;
}

int SandSimulation::get_height() {
    return height;
}

void SandSimulation::_bind_methods() {
    ClassDB::bind_method(D_METHOD("in_bounds"), &SandSimulation::in_bounds);
    ClassDB::bind_method(D_METHOD("move_and_swap"), &SandSimulation::move_and_swap);
    ClassDB::bind_method(D_METHOD("randomize"), &SandSimulation::randomize);
    ClassDB::bind_method(D_METHOD("step"), &SandSimulation::step);
    ClassDB::bind_method(D_METHOD("get_modified_cells"), &SandSimulation::get_modified_cells);
    ClassDB::bind_method(D_METHOD("get_cell"), &SandSimulation::get_cell);
    ClassDB::bind_method(D_METHOD("set_cell"), &SandSimulation::set_cell);
    ClassDB::bind_method(D_METHOD("get_width"), &SandSimulation::get_width);
    ClassDB::bind_method(D_METHOD("get_height"), &SandSimulation::get_height);
    ClassDB::bind_method(D_METHOD("resize"), &SandSimulation::resize);
}