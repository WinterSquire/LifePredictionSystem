#ifndef LIFEPREDICTIONSYSTEM_BUTTONEXECUTOR_H
#define LIFEPREDICTIONSYSTEM_BUTTONEXECUTOR_H

#include <QPushButton>
#include "../../python/PyWorker.h"

class ButtonExecutor : public QPushButton {
    Q_OBJECT
public:
    ButtonExecutor(QWidget *parent = nullptr);

public slots:
    void startTask(const PyTask& task);

signals:
    void updateUI(const QString& result);
};


#endif //LIFEPREDICTIONSYSTEM_BUTTONEXECUTOR_H
