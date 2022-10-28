#ifndef SAND_SIMULATION_CLASS_H
#define SAND_SIMULATION_CLASS_H

#include <vector>
#include <unordered_set>
#include <godot_cpp/classes/ref.hpp>

#include "elements/element.h"

using namespace godot;

class SandSimulation : public RefCounted {
    GDCLASS(SandSimulation, RefCounted);

    // Screen dimensions
    int width = 256;
    int height = 256;

    // Dimension of each chunk
    int chunk_size = 16;

    // Screen dimensions in chunks (automatically set when resized)
    int chunk_width = 4;
    int chunk_height = 4;

    // Pointers to an instance of each element to access class properties and methods
    std::vector<Element*> elements;

    // Contains the actual particles 
    std::vector<int> cells;

    // Contains the count of active particles in each chunk
    std::vector<int> chunks;

    // Godot structure that is synced to `cells` for rendering
    PackedByteArray draw_data;

protected:
    static void _bind_methods();

public:
    SandSimulation();
    ~SandSimulation();

    void step(int iterations);

    // Helper methods for elements
    void move_and_swap(int row, int col, int row2, int col2);
    void grow(int row, int col, int food, int replacer);
    int touch_count(int row, int col, int type);
    bool in_bounds(int row, int col);

    int get_cell(int row, int col);
    void set_cell(int row, int col, int type);
    int get_chunk(int c);

    PackedByteArray get_draw_data();

    int get_width();
    int get_height();
    void resize(int new_width, int new_height);

    void clean_up();
};

#endif // SAND_SIMULATION_CLASS_H