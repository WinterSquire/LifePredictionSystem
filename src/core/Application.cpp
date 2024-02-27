#include "Application.h"

#include "./base.h"
#include "./main.h"

#include "../interface/MainWindow.h"

#include <QApplication>

QApplication *qApplication;
MainWindow *mainWindow;

void Application::Initialize() {
    qApplication = new QApplication(args.argc, args.argv);
    mainWindow = new MainWindow();
}

int Application::Execute() {
    mainWindow->show();

    return QApplication::exec();
}

void Application::Shutdown() {
    delete mainWindow;
    delete qApplication;
}

