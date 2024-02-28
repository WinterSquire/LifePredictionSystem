#include "ButtonExecutor.h"

#include "../worker/WorkerThread.h"

ButtonExecutor::ButtonExecutor(QWidget *parent) : QPushButton(parent) {
    setIcon(QIcon(":/icon/run_icon.png"));
    setText("执行");
}

void ButtonExecutor::startTask(const PyTask &task) {
    auto thread = new WorkerThread(this, task);
    connect(thread, &WorkerThread::updateSignal, this, &ButtonExecutor::updateUI);
    thread->start();
}
