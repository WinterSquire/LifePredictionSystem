#ifndef CNN_H
#define CNN_H

#include <QMainWindow>

namespace Ui {
class CNN;
}

class CNN : public QMainWindow
{
    Q_OBJECT

public:
    explicit CNN(QWidget *parent = 0);
    ~CNN();
    //重写绘图事件
    void paintEvent(QPaintEvent *);
signals:
    //写一个自定义信号 告诉CNN预测场景 点击了返回
    void CNNBack();
private:
    Ui::CNN *ui;
};

#endif // CNN_H
