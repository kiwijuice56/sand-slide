#ifndef CLOUD_H
#define CLOUD_H

#include "element.h"

class Cloud: public Element {
public:
    const double PROCESS = 1.0 / 16;
    const double DECAY = 1.0 / 18;
    const double STORM = 1.0 / 16;
    const double ICE = 1.0 / 512;

    void process(SandSimulation *sim, int row, int col) override {
        // Adding a limit slows the cloud down
        if (sim->randf() > PROCESS) {
            return;
        } else if (sim->randf() < ICE && sim->touch_count(row, col, 85)) {
            sim->set_cell(row, col, 88);
        } if (sim->randf() < DECAY || sim->touch_count(row, col, 58) > 2) {
            sim->set_cell(row, col, sim->randf() < STORM ? 41 : 58);
        } else {
            sim->grow(row + 1, col, 0, 87);
            sim->grow(row - 1, col, 0, 87);
            sim->grow(row, col + 1, 0, 87);
            sim->grow(row, col - 1, 0, 87);

            sim->grow(row + 1, col, 6, 87);
            sim->grow(row - 1, col, 6, 87);
            sim->grow(row, col + 1, 6, 87);
            sim->grow(row, col - 1, 6, 87);

            sim->grow(row + 1, col, 5, 87);
            sim->grow(row - 1, col, 5, 87);
            sim->grow(row, col + 1, 5, 87);
            sim->grow(row, col - 1, 5, 87);
        }
    }

    double get_density() override {
        return 0.25;
    }

    double get_explode_resistance() override {
        return 0.1;
    }

    double get_acid_resistance() override {
        return 0.1;
    }
};

#endif // CLOUD_H