#include <iostream>
#include <random>

#include <QApplication>

#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

#include "Python.h"

QWidget *mainWindow = nullptr;

void PythonSaySomething()
{
    PyObject *main_module, *main_dict, *randint;
    long result = 0;
    int method = rand() % 2;

    QDialog *dialogue;
    QLabel *label;

    /* Python Initialization */
    Py_Initialize();

    // import module("random")
    auto random_module = PyImport_ImportModule("random");

    if (!random_module)
    {
        std::cout << "Failed to import module(\"random\")" << std::endl;
        goto PYTHON_FINALIZATION;
    }

    /* Switch Statement */

    switch (method) {
        case 0:
            goto METHOD0;
        case 1:
            goto METHOD1;
        default:
            goto METHOD0;
    }

    /* Method 0: Run Script */
    METHOD0:
    std::cout << "Method 0: Run Script" << std::endl;

    // run script
    PyRun_SimpleString("import random");
    PyRun_SimpleString("result = random.randint(1, 100)");

    // get __main__ module
    main_module = PyImport_AddModule("__main__");
    // get __main__.__dict__
    main_dict = PyModule_GetDict(main_module);
    // get __main__.result
    result = PyLong_AsLong(PyDict_GetItemString(main_dict, "result"));

    goto SHOW_RESULT;

    /* Method 1: Call Function */
    METHOD1:
    std::cout << "Method 1: Call Function" << std::endl;

    // call random.randint(1, 100)
    randint = PyObject_CallMethod(random_module, "randint", "(ii)", 1, 100);

    if (!randint)
    {
        std::cout << "Failed to call random.randint(1, 100)" << std::endl;
        goto PYTHON_FINALIZATION;
    }
    
    // get return value
    result = PyLong_AsLong(randint);

    goto SHOW_RESULT;

    /* Show Result */
    SHOW_RESULT:

    std::cout << "Python says: " << result << std::endl;

    dialogue = new QDialog(mainWindow);
    dialogue->setWindowTitle(QString("Python says: %1").arg(result));
    dialogue->resize(200, 100);

    // prevent memory leak
    dialogue->connect(dialogue, &QDialog::finished, dialogue, &QDialog::deleteLater);

    label = new QLabel(dialogue);
    label->setText(QString("Python says: %1").arg(result));
    label->setAlignment(Qt::AlignCenter);
    dialogue->setLayout(new QVBoxLayout());
    dialogue->layout()->addWidget(label);
    dialogue->show();

    /* Python Finalization */
    PYTHON_FINALIZATION:
    Py_Finalize();
    return;
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QPushButton button("Hello World");

    mainWindow = &button;

    button.resize(200, 100);
    button.show();

    button.connect(&button, &QPushButton::clicked, &PythonSaySomething);

    return app.exec();
}