#include "Debug.h"

#include <string>
#include <cstdarg>
#include <iostream>

void Debug::Log(const char *format, ...) {
    va_list args;
    char buffer[1024];

    va_start(args, format);
    vsprintf_s(buffer, 1024, format, args);
    va_end(args);

    std::cout << buffer << std::endl;
}
