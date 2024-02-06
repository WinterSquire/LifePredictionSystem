//
// Created by alex on 2024/1/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Window1.h" resolved

#include "Window1.h"
#include "ui_Window1.h"


Window1::Window1(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::Window1) {
    ui->setupUi(this);
}

Window1::~Window1() {
    delete ui;
}
