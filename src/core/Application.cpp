#include "Application.h"

#include "./base.h"
#include "./main.h"

#include "../interface/MainWidget.h"

#include <QApplication>

QApplication *qApplication;
MainWidget *mainWidget;

void Application::Initialize() {
    qApplication = new QApplication(args.argc, args.argv);
    mainWidget = new MainWidget();
}

int Application::Execute() {
    mainWidget->show();

    return qApplication->exec();
}

void Application::Shutdown() {
    delete mainWidget;
    delete qApplication;
}

