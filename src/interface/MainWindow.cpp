#include "MainWindow.h"

#include "MainWidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("机器寿命预测系统");
    setFixedSize(800, 600);
    setCentralWidget(new MainWidget(this));
}