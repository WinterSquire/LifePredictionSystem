#ifndef LIFEPREDICTIONSYSTEM_PYWORKER_H
#define LIFEPREDICTIONSYSTEM_PYWORKER_H

#include "../core/base.h"

#include "./PyTask.h"

#include <functional>

namespace PyWorker {
    Status RunPyScriptSync(const PyTask &task, string& content);
};


#endif //LIFEPREDICTIONSYSTEM_PYWORKER_H
