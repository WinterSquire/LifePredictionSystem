#include <iostream>
#include <random>

#include <QApplication>
#include <QMainWindow>

#include <QGroupBox>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

#include "Python.h"

void PythonSaySomething(QWidget *parent)
{
    PyObject *main_module, *main_dict, *randint;
    long result;
    int offsetX, offsetY;

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
    switch (rand() % 2) {
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

    dialogue = new QDialog(parent);
    dialogue->setWindowTitle(QString("Python says: %1").arg(result));
    dialogue->resize(200, 100);
    dialogue->setLayout(new QVBoxLayout());
    // prevent memory leak
    dialogue->connect(dialogue, &QDialog::finished, dialogue, &QDialog::deleteLater);

    label = new QLabel(dialogue);
    label->setText(QString("Python says: %1").arg(result));
    label->setAlignment(Qt::AlignCenter);
    dialogue->layout()->addWidget(label);

    dialogue->show();

    offsetX = static_cast<int>(parent->width() / 2 * (result / 100.0f));
    offsetY = static_cast<int>(parent->height() / 2 * (result / 100.0f));

    if (rand() % 2)
        offsetX = -offsetX;
    if (rand() % 2)
        offsetY = -offsetY;

    dialogue->move(
            parent->pos().x() + parent->width() / 2 + offsetX,
            parent->pos().y() + parent->width() / 2 + offsetY
            );

    /* Python Finalization */
    PYTHON_FINALIZATION:
    Py_Finalize();
    return;
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // use stack alloc to prevent memory leak
    QMainWindow window(nullptr, Qt::WindowFlags {Qt::MSWindowsFixedSizeDialogHint});
    window.setWindowTitle(QString("Python Embedding"));
    window.resize(640,480);

    {
        // set group box
        auto box = new QGroupBox(&window);
        auto layout = new QVBoxLayout(box);
        box->setLayout(layout);

        // set button
        auto button = new QPushButton("Let Python say something", &window);
        button->resize(200, 100);
        button->connect(button, &QPushButton::clicked, std::bind(PythonSaySomething, &window));

        // set label
        auto label = new QLabel("Python says something", &window);
        label->setAlignment(Qt::AlignCenter);

        // set layout
        layout->addWidget(label);
        layout->addWidget(button);

        // set central widget
        window.setCentralWidget(box);
    }

    // show window
    window.show();

    // enter main loop
    return app.exec();
}