#include "Application.h"

#include "./base.h"
#include "./main.h"

#include <QApplication>

QApplication *qApplication;

#include "../interface/window/test/window1/Window1.h"

void Application::Initialize() {
    qApplication = new QApplication(args.argc, args.argv);

#ifdef TEST1
    Window1* window1 = new Window1();
    window1->show();
#endif

}

int Application::Execute() {
    return qApplication->exec();
}
