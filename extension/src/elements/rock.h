#ifndef ROCK_H
#define ROCK_H

class SandSimulation;

#include "element.h"

class Rock: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {
        
    }

    double get_density() override {
        return 5.0;
    }
};

#endif // ROCK_H