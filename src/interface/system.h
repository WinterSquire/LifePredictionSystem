#ifndef SYSTEM_H
#define SYSTEM_H

#include <QMainWindow>
#include "ann.h"
#include "knn.h"
#include "cnn.h"
#include "model.h"
namespace Ui {
class System;
}

class System : public QMainWindow
{
    Q_OBJECT

public:
    explicit System(QWidget *parent = 0);
    ~System();
    //重写绘图事件
    void paintEvent(QPaintEvent *);

    ANN * annmain = NULL;
    KNN * knnmain = NULL;
    CNN * cnnmain = NULL;
    Model * modelmain = NULL;
signals:
    //写一个自定义信号 告诉系统场景 点击了返回
    void systemmainBack();
    //写一个自定义信号 告诉系统场景 点击了注销
    void systemmainCancel();



private:
    Ui::System *ui;
};

#endif // SYSTEM_H
