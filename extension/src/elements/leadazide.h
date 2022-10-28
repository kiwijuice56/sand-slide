#ifndef LEAD_AZIDE_H
#define LEAD_AZIDE_H

class SandSimulation;

#include "element.h"

class LeadAzide: public Element {
public:
    const double FLAME = 0.15;

    void process(SandSimulation *sim, int row, int col) override {
        // Explode
        if (randf() < FLAME && (sim->touch_count(row, col, 5) > 0 || sim->touch_count(row, col, 9) > 0)) {
            sim->set_cell(row, col, 9);
        }
    }

    double get_density() override {
        return 16.0;
    }
};

#endif // LEAD_AZIDE_H