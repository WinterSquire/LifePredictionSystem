#ifndef LIFEPREDICTIONSYSTEM_PYWORKER_H
#define LIFEPREDICTIONSYSTEM_PYWORKER_H

#include "../core/base.h"

#include "./PyTask.h"

#include <functional>

namespace PyWorker {
    Status RunPyScriptSync(const PyTask& task, std::function<void(string)> invokeAfterComplete);
    Status RunPyScriptAsync(const PyTask& task, std::function<void(string)> invokeAfterComplete);
};


#endif //LIFEPREDICTIONSYSTEM_PYWORKER_H
