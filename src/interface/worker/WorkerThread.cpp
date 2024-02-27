#include "WorkerThread.h"

void WorkerThread::run() {
    string result;

    PyWorker::RunPyScriptSync(m_task, result);

    emit updateSignal(QString::fromStdString(result));
}
