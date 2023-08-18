#ifndef CUSTOM_ELEMENT_H
#define CUSTOM_ELEMENT_H

#include "element.h"

class CustomElementParticle: public Element {
public:
    const double POWDER = 1 / 1.05;
    const double UP = 1.0 / 1.5;
    const double UP_BLOCK = 1.0 / 16;
    const double FIREWORK = 1.0 / 22;
    const double GROWTH = 1.0 / 512;

    void process(SandSimulation *sim, int row, int col) override {
        // electricity
        float conductivity = my_sim->custom_elements[custom_id].conductivity;
        if (sim->randf() < (conductivity * conductivity) && (sim->cardinal_touch_count(row, col, 38) > 0 || sim->cardinal_touch_count(row, col, 40) > 0 || sim->cardinal_touch_count(row, col, 115) > 0)) {
            sim->grow(row + 1, col, custom_id, 38);
            sim->grow(row - 1, col, custom_id, 38);
            sim->grow(row, col - 1, custom_id, 38);
            sim->grow(row, col + 1, custom_id, 38);
            return;
        }

        // fires
        float flammability = my_sim->custom_elements[custom_id].flammability;
        if (sim->randf() < (flammability * flammability * flammability) && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        }

        // explosive toggle
        if (my_sim->custom_elements[custom_id].explosive && sim->randf() < flammability + 0.1 && sim->is_on_fire(row, col)) {
            for (int y = -7; y <= 7; y++) {
                for (int x = -7; x <= 7; x++) {
                    if (y * y + x * x > 36) {
                        continue;
                    }
                    if (sim->in_bounds(row + y, col + x) ) {
                        sim->set_cell(row + y, col + x, sim->randf() < FIREWORK ? 66 : 9);
                    }
                }
            }
            return;
        }

        // evaporable toggle
        if (my_sim->custom_elements[custom_id].evaporable && sim->randf() < flammability + 0.1 && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 58);
            return;
        }

        // alive toggle
        if (my_sim->custom_elements[custom_id].alive && sim->randf() < GROWTH) {
            sim->grow(row + 1, col, 0, custom_id);
            sim->grow(row - 1, col, 0, custom_id);
            sim->grow(row, col - 1, 0, custom_id);
            sim->grow(row, col + 1, 0, custom_id);
            return;
        }

        // physics behavior
        int state = my_sim->custom_elements[custom_id].state;
        if (state == 0) {
            if (sim->randf() >= POWDER) {
                return;
            }
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
            // :p
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
        } else if (state == 4) {
            float power = my_sim->custom_elements[custom_id].power;

            if (sim->randf() < 1.0 / 4 && sim->in_bounds(row - 1, col) && sim->get_cell(row - 1, col) != custom_id) {
                sim->set_cell(row, col, 6);
                return;
            } else {
                if (power >= 0.0) sim->grow(row + 1, col, -1, custom_id);
                if (power >= 0.2) sim->grow(row + 2, col, -1, custom_id);
                if (power >= 0.5) sim->grow(row + 3, col, -1, custom_id);
                if (power >= 0.8) sim->grow(row + 4, col, -1, custom_id);
                if (power >= 0.9) sim->grow(row + 5, col, -1, custom_id);
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
        return (my_sim->custom_elements[custom_id].toxic ? 1 : 0);
    }
};

#endif // CUSTOM_ELEMENT_H