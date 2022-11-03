#ifndef SAND_SIMULATION_CLASS_H
#define SAND_SIMULATION_CLASS_H

#include <vector>
#include <unordered_set>
#include <godot_cpp/classes/ref.hpp>

#include "elements/element.h"

using namespace godot;

// Contains grid cells and methods to process them

class SandSimulation : public RefCounted {
    GDCLASS(SandSimulation, RefCounted);

    unsigned int g_seed = 1234;

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
    int cardinal_touch_count(int row, int col, int type);
    bool in_bounds(int row, int col);
    bool is_poisoned(int row, int col);
    bool is_on_fire(int row, int col);
    float randf();

    int get_cell(int row, int col);
    void set_cell(int row, int col, int type);
    int get_chunk(int c);

    PackedByteArray get_draw_data();

    int get_width();
    int get_height();
    void resize(int new_width, int new_height);
    void set_chunk_size(int new_size);

    void clean_up();
};

#endif // SAND_SIMULATION_CLASS_H