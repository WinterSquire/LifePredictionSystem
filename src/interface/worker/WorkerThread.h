#ifndef LIFEPREDICTIONSYSTEM_WORKERTHREAD_H
#define LIFEPREDICTIONSYSTEM_WORKERTHREAD_H

#include <QThread>

#include "../../python/PyWorker.h"

class WorkerThread : public QThread {
Q_OBJECT
public:
    WorkerThread(QObject *parent, const PyTask& task) : QThread(parent), m_task(task) {}

signals:
    void updateSignal(const QString &message);

protected:
    void run() override;

private:
    PyTask m_task;
};

#endif //LIFEPREDICTIONSYSTEM_WORKERTHREAD_H
