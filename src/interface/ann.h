#ifndef ANN_H
#define ANN_H

#include <QMainWindow>

namespace Ui {
class ANN;
}

class ANN : public QMainWindow
{
    Q_OBJECT

public:
    explicit ANN(QWidget *parent = 0);
    ~ANN();
    //重写绘图事件
    void paintEvent(QPaintEvent *);
signals:
    //写一个自定义信号 告诉ANN预测场景 点击了返回
    void ANNBack();
private:
    Ui::ANN *ui;
};

#endif // ANN_H
