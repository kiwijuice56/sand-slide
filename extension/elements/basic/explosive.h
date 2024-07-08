#pragma once




#include "../element.h"

class Explosive: public Element {
public:
    const double FLAME = 0.05;
    const double FIREWORK = 1.0 / 22;

    void process(SandSimulation *sim, int row, int col) override {
        // Explode
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            for (int y = -7; y <= 7; y++) {
                for (int x = -7; x <= 7; x++) {
                    if (y * y + x * x > 36) {
                        continue;
                    }
                    if (sim->in_bounds(row + y, col + x) ) {
                        sim->set_cell(row + y, col + x, sim->randf() < FIREWORK ? 66 : 9);
                    }
                }
            }
        }
    }

    double get_density() override {
        return 16.0;
    }

    double get_explode_resistance() override {
        return 0.08;
    }

    double get_acid_resistance() override {
        return 0.65;
    }

    int get_state() override {
        return 0;
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return 1;
    }
};

