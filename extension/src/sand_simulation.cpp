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
    draw_data = PackedByteArray();


    draw_data.resize(width * height);
    draw_data.fill(0);
    cells.resize(width * height);
    chunks.resize(chunk_width * chunk_height);
}

SandSimulation::~SandSimulation() {}

void SandSimulation::step(int iterations) {
    modified_cells.clear();

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randCell(0, chunk_size - 1);


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
    if (cells.at(row * width + col) == 0 && type != 0) {
        chunks.at((row / chunk_size) * chunk_width + (col / chunk_size))++;
    } else if (cells.at(row * width + col) != 0 && type == 0) {
        chunks.at((row / chunk_size) * chunk_width + (col / chunk_size))--;
    }
    cells.at(row * width + col) = type;
    draw_data.set(row * width + col, type);
    get_modified_cells()[row * get_width() + col] = true;
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

    for (int row = 0; row < std::min(new_height, height); row++) {
        for (int col = 0; col < std::min(new_width, width); col++) {
            cells.at(row * new_width + col) = temp.at(row * width + col);
            if (temp.at(row * width + col) != 0) {
                chunks.at((row / chunk_size) * chunk_width + (col / chunk_size))++;
            }
        }
    }

    width = new_width;
    height = new_height;   
}

int SandSimulation::get_chunk(int c) {
    return chunks.at(c);
}

int SandSimulation::get_width() {
    return width;
}

int SandSimulation::get_height() {
    return height;
}

PackedByteArray SandSimulation::get_draw_data() {
    return draw_data;
}

void SandSimulation::_bind_methods() {
    ClassDB::bind_method(D_METHOD("in_bounds"), &SandSimulation::in_bounds);
    ClassDB::bind_method(D_METHOD("move_and_swap"), &SandSimulation::move_and_swap);
    ClassDB::bind_method(D_METHOD("step"), &SandSimulation::step);
    ClassDB::bind_method(D_METHOD("get_modified_cells"), &SandSimulation::get_modified_cells);
    ClassDB::bind_method(D_METHOD("get_cell"), &SandSimulation::get_cell);
    ClassDB::bind_method(D_METHOD("set_cell"), &SandSimulation::set_cell);
    ClassDB::bind_method(D_METHOD("get_width"), &SandSimulation::get_width);
    ClassDB::bind_method(D_METHOD("get_height"), &SandSimulation::get_height);
    ClassDB::bind_method(D_METHOD("resize"), &SandSimulation::resize);
    ClassDB::bind_method(D_METHOD("get_chunk"), &SandSimulation::get_chunk);
    ClassDB::bind_method(D_METHOD("get_draw_data"), &SandSimulation::get_draw_data);
}