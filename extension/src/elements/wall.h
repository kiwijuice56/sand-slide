#ifndef WALL_H
#define WALL_H

class SandSimulation;

#include "element.h"

class Wall: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {
        
    }

    double get_density() override {
        return 9001.0;
    }

    double get_explode_resistance() override {
        return 9001.0;
    }

    double get_acid_resistance() override {
        return 9001.0;
    }
};

#endif // WALL_H