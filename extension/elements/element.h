#pragma once


// Base class for all elements

class SandSimulation;

#include "../sand_simulation.h"

class Element {
public:
    SandSimulation *my_sim;
    int custom_id = 0;

    virtual void process(SandSimulation *sim, int row, int col) = 0;

    // Needs to be a method as other elements may need this property for calculations
    virtual double get_density() = 0;
    virtual double get_explode_resistance() = 0;
    virtual double get_acid_resistance() = 0;
    virtual int get_temperature() = 0;
    virtual int get_toxicity() = 0;
    virtual int get_state() = 0;
};

