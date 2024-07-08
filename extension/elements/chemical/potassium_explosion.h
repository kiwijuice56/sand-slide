#pragma once


#include "../element.h"

class PExplosion: public Element {
public:
    const double PROCESS = 1.0 / 1.5;
    const double DECAY = 1.0 / 2.5;
    const double HYDROGEN = 1.0 / 4;

    void process(SandSimulation *sim, int row, int col) override {
        // Adding a limit slows the explosion down
        if (sim->randf() > PROCESS) {
            return;
        // We eliminate explosions that reach the end, as they tend to linger for a long time if not checked
        } else if (sim->randf() < DECAY || sim->touch_count(row, col, 6) > 2 ||
            row == sim->get_height() - 1 || col == sim->get_width() - 1 || col == 0 || row == 0) {
            sim->set_cell(row, col, sim->randf() < HYDROGEN ? 47 : 6);
        } else {
            sim->grow(row - 1, col, -1, 46);
            sim->grow(row + 1, col, -1, 46);
            sim->grow(row, col + 1, -1, 46);
            sim->grow(row, col - 1, -1, 46);
        }
    }

    double get_density() override {
        return 32.0;
    }

    double get_explode_resistance() override {
        return 0.0;
    }

    double get_acid_resistance() override {
        return 0.0;
    }

    int get_state() override {
        return 2;
    }

    int get_temperature() override {
        return 1;
    }

    int get_toxicity() override {
        return 0;
    }
};

