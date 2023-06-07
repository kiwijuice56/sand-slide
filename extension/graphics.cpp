#include "graphics.h"

using namespace godot;

Graphics::Graphics() {}

Graphics::~Graphics() {}

void Graphics::initialize_flat_color(Dictionary dict) {

}

int Graphics::get_color(int id) {
    if (id == 0) {
        return 0;
    }
    return 128;
}

void Graphics::_bind_methods() {
    ClassDB::bind_method(D_METHOD("initialize_flat_color"), &Graphics::initialize_flat_color);
}