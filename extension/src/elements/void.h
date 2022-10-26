#ifndef VOID_H
#define VOID_H

class SandSimulation;

#include "element.h"

class Void: public Element {
public:
    void process(SandSimulation *sim, int row, int col) override {
        
    }

    double get_density() override {
        return 0.0;
    }
};

#endif // VOID_H