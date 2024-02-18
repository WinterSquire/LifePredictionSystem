#include "system.h"
#include "ui_system.h"
#include <QPainter>
#include <QPushButton>
#include <QDebug>
#include "login.h"
System::System(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::System)
{
    ui->setupUi(this);
    //设置标题
    setWindowTitle("系统主体");

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
    //点击了返回
    connect(ui->backBtn,&QPushButton::clicked,[=](){
        //告诉Login场景 我返回了 Login场景监听system的返回按钮
        emit this->systemmainBack();
    });
    //点击了注销
    connect(ui->cancelBtn,&QPushButton::clicked,[=](){
        //告诉Login场景 我注销了 Login场景监听system的注销按钮
        emit this->systemmainCancel();

    });
    //实例化ann预测场景
    annmain = new ANN;
    //监听ann预测页面的返回菜单的信号
    connect(annmain,&ANN::ANNBack,this,[=](){
        annmain->hide();//将ann预测场景隐藏掉
        this->show();//重新显示系统场景
    });
    connect(ui->ANNBtn,&QPushButton::clicked,[=](){
        //进入到ann预测场景
        //自身隐藏
        this->hide();
        //设置annmain场景位置
        annmain->setGeometry(this->geometry());
        //显示ann预测场景
        annmain->show();
    });
    //实例化knn预测场景
    knnmain = new KNN;
    //监听knn预测页面的返回菜单的信号
    connect(knnmain,&KNN::KNNBack,this,[=](){
        knnmain->hide();//将knn预测场景隐藏掉
        this->show();//重新显示系统场景
    });
    connect(ui->KNNBtn,&QPushButton::clicked,[=](){
        //进入到knn预测场景
        //自身隐藏
        this->hide();
        //设置knnmain场景位置
        knnmain->setGeometry(this->geometry());
        //显示knn预测场景
        knnmain->show();
    });
    //实例化cnn预测场景
    cnnmain = new CNN;
    //监听cnn预测页面的返回菜单的信号
    connect(cnnmain,&CNN::CNNBack,this,[=](){
        cnnmain->hide();//将cnn预测场景隐藏掉
        this->show();//重新显示系统场景
    });
    connect(ui->CNNBtn,&QPushButton::clicked,[=](){
        //进入到cnn预测场景
        //自身隐藏
        this->hide();
        //设置cnnmain场景位置
        cnnmain->setGeometry(this->geometry());
        //显示cnn预测场景
        cnnmain->show();
    });
    //实例化cnn预测场景
    modelmain = new Model;
    //监听Model预测页面的返回菜单的信号
    connect(modelmain,&Model::ModelBack,this,[=](){
        modelmain->hide();//将Model预测场景隐藏掉
        this->show();//重新显示系统场景
    });
    connect(ui->ModelBtn,&QPushButton::clicked,[=](){
        //进入到cnn预测场景
        //自身隐藏
        this->hide();
        //设置modelmain场景位置
        modelmain->setGeometry(this->geometry());
        //显示model预测场景
        modelmain->show();
    });
}
void System::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/bg_03.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}
System::~System()
{
    delete ui;
}

