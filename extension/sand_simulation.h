#pragma once


#include <vector>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/image.hpp>

class Element;
class Graphics;

using namespace godot;

// Helper structures for graphics rendering

struct Gradient {
    uint32_t colors[5];
    double offsets[3];
    bool init = false;
};

struct Flat {
    uint32_t color;
    bool init = false;
};

struct CustomElement {
    uint32_t color_a;
    uint32_t color_b;
    uint32_t color_c;

    int state;
    float density;
    float viscosity;
    float conductivity;
    float temperature;
    float flammability;
    float reactivity;
    float durability;
    float power;

    bool explosive;
    bool evaporable;
    bool alive;
    bool toxic;
    bool attractive;
    bool infectious;
    bool soluble;

    bool init = false;

    int reactant_1;
    int reactant_2;
    int reactant_3;
    int product_1;
    int product_2;
    int product_3;
};

// Contains grid cells and methods to process them

class SandSimulation : public RefCounted {
    GDCLASS(SandSimulation, RefCounted);

protected:
    static void _bind_methods();

public:
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

    // Marks what cells are visited to not process them multiple times in one frame
    std::vector<bool> visited;

    // Contains the identity of the particles on the grid
    std::vector<int> cells;

    // Contains the count of active particles in each chunk
    std::vector<int> chunks;

    // Drawing state
    PackedByteArray draw_data;
    std::vector<Flat> flat_color;
    std::vector<Gradient> gradient_color;
    std::vector<Gradient> metal_color;
    std::vector<Gradient> fluid_color;

    std::vector<CustomElement> custom_elements;
    int current_id;

    long double time = 0;

    SandSimulation();
    ~SandSimulation();

    void step(int iterations);

    // Processing methods for elements
    void move_and_swap(int row, int col, int row2, int col2);
    void grow(int row, int col, int food, int replacer);
    void liquid_process(int row, int col, int fluidity);

    // State methods for elements
    int touch_count(int row, int col, int type);
    int cardinal_touch_count(int row, int col, int type);
    bool in_bounds(int row, int col);
    bool is_poisoned(int row, int col);
    bool is_on_fire(int row, int col);
    bool is_cold(int row, int col);
    bool is_swappable(int row, int col, int row2, int col2);

    // Optimized RNG
    float randf();
    float randf_loc(int row, int col);

    // Interface methods
    int get_cell(int row, int col);
    void set_cell(int row, int col, int type);
    void draw_cell(int row, int col, int type);
    int get_chunk(int c);
    int get_width();
    int get_height();
    void resize(int new_width, int new_height);
    void set_chunk_size(int new_size);
    PackedByteArray get_data();

    void initialize_custom_elements(Dictionary dict);

    // Graphics methods

    void initialize_flat_color(Dictionary dict);
    void initialize_gradient_color(Dictionary dict);
    void initialize_fluid_color(Dictionary dict);
    void initialize_metal_color(Dictionary dict);

    uint32_t lerp_color(uint32_t a, uint32_t b, double x);
    uint32_t add_color(uint32_t a, uint32_t b);
    double smooth_step(double edge0, double edge1, double x);

    uint32_t get_color(int row, int col, bool flat);
    PackedByteArray get_color_image(bool flat);
};

