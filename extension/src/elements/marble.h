#ifndef MARBLE_H
#define MARBLE_H

class SandSimulation;

#include "element.h"

class Marble: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {
        
    }

    double get_density() override {
        return 24.0;
    }
};

#endif // MARBLE_H