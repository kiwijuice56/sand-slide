#pragma once


#include "../element.h"

class PrimordialSoup: public Element {
public:
    const double SPAWN = 0.00001;
    const double MELT = 1.0 / 8;
    const double EVAPORATION = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        double random = sim->randf();

        // Spawning life
        if (random < SPAWN) {
            const int LIFE[] = {3, 4, 7, 12, 31, 32, 33, 49, 54, 55, 86, 101, 119, 126};
            sim->set_cell(row, col, LIFE[int(sim->randf() * 14)]);
            return;
        }

        // Evaporation when heated
        if (random < EVAPORATION && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 58);
            return;
        }

        // Conductivity
        if (random < MELT && (sim->cardinal_touch_count(row, col, 38) > 0 || sim->cardinal_touch_count(row, col, 40) > 0 || sim->cardinal_touch_count(row, col, 115) > 0)) {
            sim->grow(row + 1, col, 127, 38);
            sim->grow(row - 1, col, 127, 38);
            sim->grow(row, col - 1, 127, 38);
            sim->grow(row, col + 1, 127, 38);
            return;
        }

        sim->liquid_process(row, col, 2);
    }

    double get_density() override {
        return 1.05;
    }

    double get_explode_resistance() override {
        return 0.2;
    }

    double get_acid_resistance() override {
        return 0.9;
    }

    int get_state() override {
        return 1;
    }

    int get_temperature() override {
        return 0;
    }

    int get_toxicity() override {
        return -1;
    }
};

