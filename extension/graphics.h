#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <map>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class Graphics : public RefCounted {
    GDCLASS(Graphics, RefCounted);
    std::map<int, short> flat_color;

protected:
    static void _bind_methods();

public:
    Graphics();
    ~Graphics();

    void initialize_flat_color(Dictionary dict);
    int get_color(int id);

};

#endif // GRAPHICS_H