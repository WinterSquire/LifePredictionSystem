#ifndef KNN_H
#define KNN_H

#include <QMainWindow>

namespace Ui {
class KNN;
}

class KNN : public QMainWindow
{
    Q_OBJECT

public:
    explicit KNN(QWidget *parent = 0);
    ~KNN();
    //重写绘图事件
    void paintEvent(QPaintEvent *);
signals:
    //写一个自定义信号 告诉KNN预测场景 点击了返回
    void KNNBack();
private:
    Ui::KNN *ui;
};

#endif // KNN_H
