#include "ButtonExecutor.h"

#include "../worker/WorkerThread.h"

ButtonExecutor::ButtonExecutor(QWidget *parent) : QPushButton(parent) {
    setIcon(QIcon(":/icon/run_icon.png"));
    setText("执行");
}

void ButtonExecutor::startTask(const PyTask &task) {
    m_taskRunning = true;

    auto thread = new WorkerThread(this, task);
    connect(thread, &WorkerThread::updateSignal, this, &ButtonExecutor::endTask);
    thread->start();
}

void ButtonExecutor::endTask(const QString &result) {
    m_taskRunning = false;

    emit updateUI(result);
}
