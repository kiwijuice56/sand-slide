#ifndef STEEL_H
#define STEEL_H

class SandSimulation;

#include "element.h"

class Steel: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {
        
    }

    double get_density() override {
        return 48.0;
    }

    double get_explode_resistance() override {
        return 0.95;
    }

    double get_acid_resistance() override {
        return 0.95;
    }
};

#endif // STEEL_H