#ifndef LIFEPREDICTIONSYSTEM_DEBUG_H
#define LIFEPREDICTIONSYSTEM_DEBUG_H

namespace Debug{
    void Log(const char* format, ...);
}

#define LOG(...) Debug::Log(__VA_ARGS__)

#endif //LIFEPREDICTIONSYSTEM_DEBUG_H
