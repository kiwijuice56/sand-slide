#ifndef MARBLE_H
#define MARBLE_H

class SandSimulation;

#include "element.h"

class Marble: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {
        
    }

    double get_density() override {
        return 20.0;
    }

    double get_explode_resistance() override {
        return 0.55;
    }

    double get_acid_resistance() override {
        return 0.95;
    }
};

#endif // MARBLE_H