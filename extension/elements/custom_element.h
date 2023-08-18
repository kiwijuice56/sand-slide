#ifndef CUSTOM_ELEMENT_H
#define CUSTOM_ELEMENT_H

#include "element.h"

class CustomElementParticle: public Element {
public:
    const double UP = 1.0 / 1.5;
    const double UP_BLOCK = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        int state = my_sim->custom_elements[custom_id].state;
        if (state == 0) {
            bool bot_left = sim->is_swappable(row, col, row + 1, col - 1);
            bool bot = sim->is_swappable(row, col, row + 1, col);
            bool bot_right = sim->is_swappable(row, col, row + 1, col + 1);
            if (bot) {
                sim->move_and_swap(row, col, row + 1, col);
            } else if (bot_left && bot_right) {
                sim->move_and_swap(row, col, row + 1, col + (sim->randf() < 0.5 ? 1 : -1));
            } else if (bot_left) {
                sim->move_and_swap(row, col, row + 1, col - 1);
            } else if (bot_right) {
                sim->move_and_swap(row, col, row + 1, col + 1);
            }
        } else if (state == 1) {

        } else if (state == 2) {
            float viscosity = my_sim->custom_elements[custom_id].viscosity;
            sim->liquid_process(row, col, int(4.0 - (viscosity * 3.0)));   
        } else if (state == 3) {
            bool blocked = !sim->in_bounds(row - 1, col) || sim->get_cell(row - 1, col) == 6;
            if (sim->randf() < (blocked ? UP_BLOCK : UP)) {
                sim->move_and_swap(row, col, row - 1, col);
            } else {
                sim->move_and_swap(row, col, row, col + (sim->randf() < 0.5 ? 1 : -1));
            }
        }
    }

    double get_density() override {
        return 256 * my_sim->custom_elements[custom_id].density;
    }

    double get_explode_resistance() override {
        return my_sim->custom_elements[custom_id].durability;
    }

    double get_acid_resistance() override {
        return 1.0 - my_sim->custom_elements[custom_id].reactivity;
    }

    int get_state() override {
        return my_sim->custom_elements[custom_id].state;
    }

    int get_temperature() override {
        if (my_sim->custom_elements[custom_id].temperature < 0.25) {
            return -1;
        } else if (my_sim->custom_elements[custom_id].temperature > 0.75) {
            return 1;
        }
        return 0;
    }

    int get_toxicity() override {
        return 0;
    }
};

#endif // CUSTOM_ELEMENT_H