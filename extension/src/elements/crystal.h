#ifndef CRYSTAL_H
#define CRYSTAL_H

class SandSimulation;

#include "element.h"

class Crystal: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {
        
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
};

#endif // CRYSTAL_H