#ifndef MODEL_H
#define MODEL_H

#include <QMainWindow>

namespace Ui {
class Model;
}

class Model : public QMainWindow
{
    Q_OBJECT

public:
    explicit Model(QWidget *parent = 0);
    ~Model();
    //重写绘图事件
    void paintEvent(QPaintEvent *);
signals:
    //写一个自定义信号 告诉Model预测场景 点击了返回
    void ModelBack();
private:
    Ui::Model *ui;
};

#endif // MODEL_H
