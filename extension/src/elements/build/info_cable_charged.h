#ifndef INFO_CABLE_CHARGED_H
#define INFO_CABLE_CHARGED_H

class SandSimulation;

#include "../element.h"

class InfoCableCharged: public Element {
public:
    const double LOSE_CHARGE = 1.0 / 3;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < LOSE_CHARGE) {
            sim->set_cell(row, col, 102);
        }
    }

    double get_density() override {
        return 8.0;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.99;
    }

    int get_state() override {
        return 0;
    }
};

#endif // INFO_CABLE_CHARGED_H