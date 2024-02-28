#ifndef LIFEPREDICTIONSYSTEM_MAINWINDOW_H
#define LIFEPREDICTIONSYSTEM_MAINWINDOW_H

#include <QMainWindow>

#include <QStackedWidget>
#include "page/ePage.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private:
    QStackedWidget *m_stackedWidget;

private slots:
    void switchToPage(ePage index);
};


#endif //LIFEPREDICTIONSYSTEM_MAINWINDOW_H
