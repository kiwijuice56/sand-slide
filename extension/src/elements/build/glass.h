#ifndef GLASS_H
#define GLASS_H

class SandSimulation;

#include "../element.h"

class Glass: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {
        
    }

    double get_density() override {
        return 3.0;
    }

    double get_explode_resistance() override {
        return 0.2;
    }

    double get_acid_resistance() override {
        return 0.95;
    }
};

#endif // GLASS_H