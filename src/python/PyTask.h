#ifndef LIFEPREDICTIONSYSTEM_PYTASK_H
#define LIFEPREDICTIONSYSTEM_PYTASK_H

#include "../core/base.h"

#include <functional>

struct PyTask {
    string module;
    string entryFunction;
    const vector<string> args;
};


#endif //LIFEPREDICTIONSYSTEM_PYTASK_H
