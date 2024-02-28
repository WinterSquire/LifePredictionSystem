#ifndef LIFEPREDICTIONSYSTEM_WELCOMEPAGE_H
#define LIFEPREDICTIONSYSTEM_WELCOMEPAGE_H

#include <QWidget>
#include "ePage.h"

class WelcomePage : public QWidget {
    Q_OBJECT
public:
    WelcomePage(QWidget* parent = nullptr);

signals:
    void onBtnStartClicked(ePage index);
};


#endif //LIFEPREDICTIONSYSTEM_WELCOMEPAGE_H
