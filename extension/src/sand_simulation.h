#ifndef SAND_SIMULATION_CLASS_H
#define SAND_SIMULATION_CLASS_H

#include <vector>
#include <unordered_set>
#include <godot_cpp/classes/ref.hpp>

#include "elements/element.h"

using namespace godot;

class SandSimulation : public RefCounted {
    GDCLASS(SandSimulation, RefCounted);

    int width = 256;
    int height = 256;
    int chunk_size = 16;

    int chunk_width = 4;
    int chunk_height = 4;

    std::vector<Element*> elements;

    std::vector<int> cells;
    std::vector<int> chunks;
    Dictionary modified_cells;
    PackedByteArray draw_data;

protected:
    static void _bind_methods();

public:
    SandSimulation();
    ~SandSimulation();

    void step(int iterations);

    void move_and_swap(int row, int col, int row2, int col2);
    bool in_bounds(int row, int col);

    Dictionary get_modified_cells();

    // Modifiers
    void set_cell(int row, int col, int type);
    int get_cell(int row, int col);

    int get_chunk(int c);
    PackedByteArray get_draw_data();

    int get_width();
    int get_height();
    void resize(int new_width, int new_height);
};

#endif // SAND_SIMULATION_CLASS_H