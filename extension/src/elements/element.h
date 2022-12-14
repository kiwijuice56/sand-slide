#ifndef ELEMENT_H
#define ELEMENT_H

// Base class for all elements

class SandSimulation;

#include "../sand_simulation.h"

class Element {
public:
    virtual void process(SandSimulation *sim, int row, int col) = 0;
    // Needs to be a method as other elements may need this property for calculations
    virtual double get_density() = 0;
    virtual double get_explode_resistance() = 0;
    virtual double get_acid_resistance() = 0;
};

#endif // ELEMENT_H