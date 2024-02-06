#ifndef LIFEPREDICTIONSYSTEM_PY_H
#define LIFEPREDICTIONSYSTEM_PY_H

#include <Python.h>
#include "../core/base.h"

namespace Py{
    Status Initialize();
    Status Finalize();

    Status RunString(const char* code);
}

#endif //LIFEPREDICTIONSYSTEM_PY_H
