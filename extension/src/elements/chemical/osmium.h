#ifndef OSMIUM_H
#define OSMIUM_H

class SandSimulation;

#include "../element.h"

class Osmium: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {
        
    }

    double get_density() override {
        return 128;
    }

    double get_explode_resistance() override {
        return 0.97;
    }

    double get_acid_resistance() override {
        return 0.97;
    }
};

#endif // OSMIUM_H