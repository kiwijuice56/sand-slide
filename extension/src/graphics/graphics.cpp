#include "graphics.h"

using namespace godot;

Graphics::Graphics() {
}

void draw_image(PackedByteArray out, std::vector<int> cells, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            out.set((y * width + x) * 4, cells.at(y * width + x));
        }
    }
}