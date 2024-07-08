#pragma once


#include "../element.h"

class Dragon: public Element {
public:
    const double GROWTH = 0.000625;
    const double DISSOLVE = 1.0 / 64;
    const double FIRE = 1.0 / 64;
    const double POISON = 1.0 / 8;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->touch_count(row, col, 32) > 3) {
            sim->set_cell(row, col, 0);
        } else if (sim->randf() < POISON && (sim->is_poisoned(row, col) || sim->is_cold(row, col))) {
            sim->set_cell(row, col, 16);
            return;
        } else if (sim->touch_count(row, col, 23) > 0 || sim->randf() < DISSOLVE && sim->touch_count(row, col, 30) > 0) {
            sim->set_cell(row, col, 16);
        } else if (sim->randf() < GROWTH * (sim->is_on_fire(row, col) ? 12.0 : 1.0)) {
            if (sim->randf() < FIRE) {
                sim->grow(row - 2, col, 0, 66);
            }
            int dir = (int) (sim->randf() * 2);
            switch (dir) {
                case 0: sim->grow(row + 1, col, 0, 32); sim->grow(row - 1, col, 0, 32); break;
                case 1: sim->grow(row, col + 1, 0, 32); sim->grow(row, col - 1, 0, 32); break;
            }
        }

    }

    double get_density() override {
        return 1.25;
    }

    double get_explode_resistance() override {
        return 0.8;
    }

    double get_acid_resistance() override {
        return 0.8;
    }

    int get_state() override {
        return 0;
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return 0;
    }
};

