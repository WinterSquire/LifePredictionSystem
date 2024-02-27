#include "PyCore.h"

#include "Python.h"
#include "../core/FileSystem.h"

Status PyCore::Initialize() {
    PyStatus status;
    PyConfig config;

    if (Py_IsInitialized() == true) return Status::FAILURE;

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
                                L"./python/python39.zip;./script");
    if (PyStatus_Exception(status)) goto FAIL;

    /* sys.platlibdir: platform library directory name, set at configure time by --with-platlibdir,
     * overrideable by the PYTHONPLATLIBDIR environment variable.
     * New in version 3.9.
     * */
    status = PyConfig_SetString(&config, &config.platlibdir,
                                L"python39.zip");
    if (PyStatus_Exception(status)) goto FAIL;

    /* Program name. Used to initialize executable, and in early error messages.
     * CWD
     * */
    status = PyConfig_SetString(&config, &config.program_name,
                                FileSystem::GetProgramName());
    if (PyStatus_Exception(status)) goto FAIL;

    /* sys.executable */
    status = PyConfig_SetString(&config, &config.executable,
                                std::filesystem::absolute("./python/python.exe").c_str());
    if (PyStatus_Exception(status)) goto FAIL;

    // Initialize
    status = Py_InitializeFromConfig(&config);
    PyThread_init_thread();
    PyEval_ReleaseThread(PyThreadState_Get());

    if (PyStatus_Exception(status)) goto FAIL;

    LOG("Python Initialized");
    LOG("Python Version: %s", Py_GetVersion());
    return Status::SUCCESS;

    FAIL:
    if (Py_IsInitialized() == true) Py_Finalize();
    LOG("Python Failed To Initialize");
    return Status::FAILURE;
}

Status PyCore::Finalize() {
    if (Py_IsInitialized() == true) {
        PyGILState_Ensure();
        Py_Finalize();
    }
    LOG("Python Finalized");
    return Status::SUCCESS;
}

