#include "Py.h"

#include <QString>


Status Py::Initialize() {
    Py_Initialize();

    if (Py_IsInitialized() == false)
    {
        LOG("Python Failed To Initialize");
        return Status::FAILURE;
    }

    LOG("Python Initialized");
    LOG("Python Version: %s", Py_GetVersion());
    return Status::SUCCESS;
}

Status Py::Finalize() {
    if (Py_IsInitialized() == true) Py_FinalizeEx();
    LOG("Python Finalized");
    return Status::SUCCESS;
}

Status Py::RunString(const char *code) {
    int status;

//    auto interpreter = Py_NewInterpreter();

    LOG("========= Python Run String Begin =========");

    status = PyRun_SimpleString(code);

    LOG("========= Python Run String End =========");

//    Py_EndInterpreter(interpreter);

    if (status != 0)
    {
        LOG("Python Failed To Run Code: %s", code);
        return Status::FAILURE;
    }

    return Status::SUCCESS;
}
