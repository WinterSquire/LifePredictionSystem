#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMenuBar>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置标题
    setWindowTitle("首页");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //创建退出 菜单项
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出 实现退出
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //移动登录按钮位置
    ui->pushButton->move(this->width()*0.5-ui->pushButton->width()*0.5,this->height()*0.7);

    //进入登录页面
    loginmain = new Login;
    //监听登录页面的返回菜单的信号
    connect(loginmain,&Login::loginmainBack,this,[=](){
        loginmain->hide();//将登录场景隐藏掉
        this->show();//重新显示主场景
    });
    connect(ui->pushButton,&QPushButton::clicked,[=](){
     //自身隐藏
     this->hide();
     //设置loginmain场景位置
     loginmain->setGeometry(this->geometry());
     //显示登录场景
     loginmain->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
