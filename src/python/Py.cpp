#include "Py.h"

#include <Windows.h>
#include <QString>
#include <filesystem>

Status Py::Initialize() {
    PyStatus status;
    PyConfig config;
    wchar_t buffer[MAX_PATH];
    const wchar_t* paths[] = {L"./python",L"./python/DLLs",L"./python/Lib",L"./python/Lib/site-packages"};

    // 获取路径
    GetModuleFileNameW(nullptr, buffer, MAX_PATH);

    std::filesystem::path executablePath(buffer);
    std::filesystem::path pythonFolder = executablePath.parent_path() / L"python";

    // Python Configuration
    PyConfig_InitIsolatedConfig(&config);

    status = PyConfig_SetString(&config, &config.home, pythonFolder.c_str());
    if (PyStatus_Exception(status)) goto FAIL;
    status = PyConfig_SetString(&config, &config.pythonpath_env, pythonFolder.c_str());
    if (PyStatus_Exception(status)) goto FAIL;
    status = PyConfig_SetString(&config, &config.program_name, L"LifePredictionSystem");
    if (PyStatus_Exception(status)) goto FAIL;
    status = PyConfig_SetWideStringList(&config, &config.module_search_paths, 4, const_cast<wchar_t **>(paths));
    if (PyStatus_Exception(status)) goto FAIL;
    status = PyConfig_SetString(&config, &config.executable, (pythonFolder  / L"python.exe").c_str());
    if (PyStatus_Exception(status)) goto FAIL;

    status = Py_InitializeFromConfig(&config);

    if (PyStatus_Exception(status)) goto FAIL;

    LOG("Python Initialized");
    LOG("Python Version: %s", Py_GetVersion());
    return Status::SUCCESS;

    FAIL:
    LOG("Python Failed To Initialize");
    return Status::FAILURE;
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
