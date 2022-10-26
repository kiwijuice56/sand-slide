#ifndef SAND_SIMULATION_CLASS_H
#define SAND_SIMULATION_CLASS_H

#include <vector>
#include <godot_cpp/classes/ref.hpp>
#include "elements/element.h"

using namespace godot;

class SandSimulation : public RefCounted {
    GDCLASS(SandSimulation, RefCounted);

    int width = 256;
    int height = 256;

    std::vector<Element*> elements;
    std::vector<int> cells;
    Dictionary modified_cells;

protected:
    static void _bind_methods();

public:
    SandSimulation();
    ~SandSimulation();

    void step(int iterations);
    void randomize();

    void move_and_swap(int row, int col, int row2, int col2);
    bool in_bounds(int row, int col);

    Dictionary get_modified_cells();

    void set_cell(int row, int col, int type);
    int get_cell(int row, int col);

    int get_width();
    int get_height();
    void resize(int new_width, int new_height);
};

#endif // SAND_SIMULATION_CLASS_H