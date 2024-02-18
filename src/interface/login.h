#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "system.h"
namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    System * systemmain = NULL;
    //重写绘图事件
    void paintEvent(QPaintEvent *);


private slots:
    void on_loginBtn_released();

    void on_registerBtn_released();
signals:
    //写一个自定义信号 告诉登录场景 点击了返回
    void loginmainBack();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
