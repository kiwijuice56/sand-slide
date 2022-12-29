#ifndef WORM_HOLE_H
#define WORM_HOLE_H

class SandSimulation;

#include "element.h"

class WormHole: public Element {
public:
    const double GRAB = 1.0 / 32;
    const double PROCESS = 1.0 / 90;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < PROCESS) {
            return;
        }
        // Absorb anything in immediate proximity if not a worm hole
        for (int y = row - 1; y <= row + 1; y++) {
            for (int x = col - 1; x <= col + 1; x++) {
                int c = std::min(sim->get_width() - 1, (int) (sim->randf() * sim->get_width()));
                int r = std::min(sim->get_height() - 1, (int) (sim->randf() * sim->get_height()));
                if (!sim->in_bounds(r, c) || !sim->in_bounds(y, x) || sim->get_cell(r, c) == 81 || sim->get_cell(y, x) == 81 || sim->get_cell(r, c) == 81)
                    continue;
                sim->move_and_swap(y, x, r, c);
            }
        }

        // If the worm hole has no space around it after absorbing all 4 directions, 
        // it is in the middle of the worm hole and doesn't need to keep processing
        if (sim->cardinal_touch_count(row, col, 0) == 0) { 
            return;
        }

        // Keep moving particles closer into the worm hole
        for (int y = row - 8; y <= row + 8; y++) {
            for (int x = col - 8; x <= col + 8; x++) {
                if (sim->randf() >= GRAB || !sim->in_bounds(y, x) || sim->get_cell(y, x) == 81) 
                    continue;
                if (sim->get_cell(y, x) == 29)
                    sim->set_cell(y, x, 34);
                
                int dirRow = row - y < 0 ? -1 : 1;
                int dirCol = col - x < 0 ? -1 : 1;
                if (row == y) dirRow = 0;
                if (col == x) dirCol = 0;
                sim->move_and_swap(y, x, y + dirRow, x + dirCol);
            }
        }
    }

    double get_density() override {
        return 1000000.0;
    }

    double get_explode_resistance() override {
        return 10.0;
    }

    double get_acid_resistance() override {
        return 10.0;
    }
};

#endif // WORM_HOLE_H