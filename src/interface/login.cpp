#include "login.h"
#include "ui_login.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QPushButton>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    //设置标题
    setWindowTitle("系统登录");

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
        //告诉主场景 我返回了 主场景监听Login的返回按钮
        emit this->loginmainBack();
    });
}

Login::~Login()
{
    delete ui;
}
void Login::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/bg_02.webp");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}

void Login::on_loginBtn_released()
{
    auto username = ui->usernameEdit->text();
    auto password = ui->passwordEdit->text();
    qDebug()<<"登录"<<username<<password;

    //用户名不能为空
    if(username.isEmpty())
    {
        ui->tipLabel->setText("账号不能为空");
        return;
    }
    //密码不能为空
    if(password.isEmpty())
    {
        ui->tipLabel->setText("密码不能为空");
        return;
    }
    //验证用户名和密码是否正确
    //代码写死
    /*
    if(username == "wps" && password == "123")
    {
        ui->tipLabel->setText("ok");
    }
    else
    {
        ui->tipLabel->setText("账号或密码不正确");
    }
    */
    //数据库验证
    QSqlTableModel * model = new QSqlTableModel;
    model->setTable("userinfo");
    model->setFilter(QString("username='%1' and password='%2'").arg(username).arg(password));
    model->select();
    //检测是否查询到数据
    int row = model->rowCount();
    if(row>0)
    {
        qDebug()<<"login suc";

        //进入系统页面
        systemmain = new System;
        //监听系统页面的返回菜单的信号
        connect(systemmain,&System::systemmainBack,this,[=](){
            systemmain->hide();//将系统场景隐藏掉
            this->show();//重新显示登录场景
        });
        //监听系统页面的注销菜单的信号
        connect(systemmain,&System::systemmainCancel,this,[=](){
            systemmain->hide();//将系统场景隐藏掉
            this->show();//重新显示登录场景
            auto username = ui->usernameEdit->text();
            QString cmd = QString("DELETE FROM userinfo WHERE username = '%1'").arg(username);
            QSqlQuery query;
            if(query.exec(cmd))
            {
                qDebug()<<"cancel suc";
                ui->tipLabel->setText("账号注销成功");
                return;
            }
            else
            {
                qDebug()<<"cancel fail";
                ui->tipLabel->setText("账号注销失败");
            }

        });
        connect(ui->loginBtn,&QPushButton::clicked,[=](){
         //自身隐藏
         this->hide();
         //设置systemmain场景位置
         systemmain->setGeometry(this->geometry());
         //显示系统场景
         systemmain->show();
        });

    }
    else
    {
        qDebug()<<"login fail";
        ui->tipLabel->setText("账号或密码不正确");
    }

    delete model;

}



void Login::on_registerBtn_released()
{
    auto username = ui->usernameEdit->text();
    auto password = ui->passwordEdit->text();
    QString cmd = QString("insert into userinfo values('%1','%2')").arg(username).arg(password);
    QSqlQuery query;
    if(query.exec(cmd))
    {
        qDebug()<<"register suc";
        ui->tipLabel->setText("账号注册成功");
    }
    else
    {
        qDebug()<<"register fail";
        ui->tipLabel->setText("账号注册失败");
    }
}
