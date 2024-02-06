//
// Created by alex on 2024/1/25.
//

#ifndef LIFEPREDICTIONSYSTEM_WINDOW1_H
#define LIFEPREDICTIONSYSTEM_WINDOW1_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class Window1; }
QT_END_NAMESPACE

class Window1 : public QMainWindow {
Q_OBJECT

public:
    explicit Window1(QWidget *parent = nullptr);

    ~Window1() override;

private:
    Ui::Window1 *ui;
};


#endif //LIFEPREDICTIONSYSTEM_WINDOW1_H
