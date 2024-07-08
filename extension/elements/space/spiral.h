#pragma once


#include "../element.h"

class Spiral: public Element {
public:
    const double DECAY = 1.0 / 256;
    const double PAUSE = 1.0 / 5.0;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 0);
            return;
        }

        if (sim->randf() < PAUSE) {
            return;
        }

        double time = sim->randf() * 0.2 + (512 * sim->time + 0.5 * (double(row) / sim->get_height()) + 0.5 * (double(col) / sim->get_width()));
        double section = time - int(time);
        if (section < 0.125) {
            sim->move_and_swap(row, col, row + 1, col + 1); return;
        }
        if (section < 0.25) {
            sim->move_and_swap(row, col, row + 1, col); return;
        }
        if (section < 0.375) {
            sim->move_and_swap(row, col, row + 1, col - 1); return;
        }
        if (section < 0.5) {
            sim->move_and_swap(row, col, row, col - 1); return;
        }
        if (section < 0.625) {
            sim->move_and_swap(row, col, row - 1, col - 1); return;
        }
        if (section < 0.75) {
            sim->move_and_swap(row, col, row - 1, col); return;
        }
        if (section < 0.875) {
            sim->move_and_swap(row, col, row - 1, col + 1); return;
        }
        sim->move_and_swap(row, col, row, col + 1);
    }

    double get_density() override {
        return 256.0;
    }

    double get_explode_resistance() override {
        return 1.0;
    }

    double get_acid_resistance() override {
        return 1.0;
    }

    int get_state() override {
        return 2;
    }

    int get_temperature() override {
        return 1;
    }

    int get_toxicity() override {
        return 1;
    }
};

