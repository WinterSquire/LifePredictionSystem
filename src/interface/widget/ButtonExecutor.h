#ifndef LIFEPREDICTIONSYSTEM_BUTTONEXECUTOR_H
#define LIFEPREDICTIONSYSTEM_BUTTONEXECUTOR_H

#include <QPushButton>
#include "../../python/PyWorker.h"

class ButtonExecutor : public QPushButton {
    Q_OBJECT
public:
    ButtonExecutor(QWidget *parent = nullptr);

    bool isTaskRunning() const { return m_taskRunning; }

public slots:
    void startTask(const PyTask& task);
    void endTask(const QString& result);

signals:
    void updateUI(const QString& result);

private:
    bool m_taskRunning = false;
};


#endif //LIFEPREDICTIONSYSTEM_BUTTONEXECUTOR_H
