#ifndef WATER_H
#define WATER_H

#include "../element.h"

class Water: public Element {
public:
    const double ABSORB = 1.0 / 4098;
    const double EVAPORATION = 1.0 / 64;
    const double MELT = 1.0 / 128;
    const double MIX = 1.0 / 4;
    const double FREEZE = 1.0 / 4;

    void process(SandSimulation *sim, int row, int col) override {
        // Conductivity 
        if (sim->randf() < MELT && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0)) {
            sim->grow(row + 1, col, 3, 38);
            sim->grow(row - 1, col, 3, 38);
            sim->grow(row, col - 1, 3, 38);
            sim->grow(row, col + 1, 3, 38);
            return;
        }

        if (sim->randf() < FREEZE && sim->is_cold(row, col)) {
            sim->set_cell(row, col, sim->randf() < 0.5 ? 19 : 85);
        }

        // Mix with water to turn into acidic water
        if (sim->randf() < MIX && sim->touch_count(row, col, 21) > 0) {
            sim->set_cell(row, col, 59);
            return;
        }

        if (sim->randf() < MIX && sim->touch_count(row, col, 70) > 0) {
            sim->set_cell(row, col, 71);
            return;
        }

        // Evaporation when heated
        if (sim->randf() < EVAPORATION && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 58);
            return;
        }

        // Absorption into plants
        if (sim->randf() < ABSORB && sim->touch_count(row, col, 14) > 0) {
            sim->set_cell(row, col, 0);
            return;
        }

        sim->liquid_process(row, col, 3);    
    }

    double get_density() override {
        return 1.0;
    }

    double get_explode_resistance() override {
        return 0.2;
    }

    double get_acid_resistance() override {
        return 0.9;
    }
};

#endif // WATER_H