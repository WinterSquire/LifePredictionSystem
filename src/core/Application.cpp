#include "Application.h"

#include "./base.h"
#include "./main.h"

#include "../interface/mainwindow.h"

#include <QApplication>

QApplication *qApplication;
MainWindow *mainWindow;

void Application::Initialize() {
    qApplication = new QApplication(args.argc, args.argv);
    mainWindow = new MainWindow();
}

int Application::Execute() {
    mainWindow->show();

    return qApplication->exec();
}

void Application::Shutdown() {
    delete mainWindow;
    delete qApplication;
}

