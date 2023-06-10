#ifndef SAND_SIMULATION_CLASS_H
#define SAND_SIMULATION_CLASS_H

#include <vector>
#include <unordered_map>
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
};

struct Fluid {
    uint32_t colors[3];
    int texture;
};

struct GameTexture {
    int width;
    int height;

    std::vector<uint32_t> *pixels;
};

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

    // Marks what cells are visited to not process them multiple times in one frame
    std::vector<bool> visited;

    // Contains the identity of the particles on the grid
    std::vector<int> cells;

    // Contains the count of active particles in each chunk
    std::vector<int> chunks;

    // Drawing state
    PackedByteArray draw_data;
    std::unordered_map<int, uint32_t> flat_color;
    std::unordered_map<int, Gradient> gradient_color;
    std::unordered_map<int, Gradient> metal_color;
    std::unordered_map<int, Fluid> fluid_color;
    std::vector<GameTexture> textures;

    long double time;

protected:
    static void _bind_methods();

public:
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

    // Graphics methods
    
    void initialize_textures(Array images);
    void initialize_flat_color(Dictionary dict);
    void initialize_gradient_color(Dictionary dict);
    void initialize_fluid_color(Dictionary dict);
    void initialize_metal_color(Dictionary dict);

    uint32_t lerp_color(uint32_t a, uint32_t b, double x);
    uint32_t add_color(uint32_t a, uint32_t b);
    double smooth_step(double edge0, double edge1, double x);
    uint32_t sample_texture(GameTexture t, int x, int y, double offset_x, double offset_y);

    uint32_t get_color(int row, int col);
    PackedByteArray get_color_image();
};

#endif // SAND_SIMULATION_CLASS_H