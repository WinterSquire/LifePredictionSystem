#include "Py.h"

#include <filesystem>
#include "../core/FileSystem.h"

Status Py::Initialize() {
    PyStatus status;
    PyConfig config;

    // Python Configuration
    PyConfig_InitIsolatedConfig(&config);

    // Enable import
    config.site_import = true;

    /* Python home directory.
     * Initialized from PYTHONHOME environment variable value by default.
     * */
    status = PyConfig_SetString(&config, &config.home,
                                std::filesystem::absolute("./python").c_str());
    if (PyStatus_Exception(status)) goto FAIL;

    /* Module search paths as a string separated by DELIM (os.path.pathsep).
     * Initialized from PYTHONPATH environment variable value by default.
     * */
    status = PyConfig_SetString(&config, &config.pythonpath_env,
                                std::filesystem::absolute("./python/python39.zip").c_str());
    if (PyStatus_Exception(status)) goto FAIL;

    /* sys.platlibdir: platform library directory name, set at configure time by --with-platlibdir,
     * overrideable by the PYTHONPLATLIBDIR environment variable.
     * New in version 3.9.
     * */
    status = PyConfig_SetString(&config, &config.platlibdir,
                                L"python39.zip");
    if (PyStatus_Exception(status)) goto FAIL;

    /* Program name. Used to initialize executable, and in early error messages. */
    status = PyConfig_SetString(&config, &config.program_name,
                                FileSystem::GetProgramName());
    if (PyStatus_Exception(status)) goto FAIL;

    /* sys.executable */
    status = PyConfig_SetString(&config, &config.executable,
                                std::filesystem::absolute("./python/python.exe").c_str());
    if (PyStatus_Exception(status)) goto FAIL;

    // Initialize
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
