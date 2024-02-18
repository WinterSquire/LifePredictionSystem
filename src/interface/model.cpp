#include "model.h"
#include "ui_model.h"
#include <QPainter>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>

Model::Model(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Model)
{
    ui->setupUi(this);
    //设置标题
    setWindowTitle("模型预测");

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
        //告诉system场景 我返回了 system场景监听Model的返回按钮
        emit this->ModelBack();
    });
    //点击导入文件按钮，弹出文件对话框
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QString path = QFileDialog::getOpenFileName(this,"打开文件","C:\\Users");

        //将路径放入到lineEdit中
        ui->lineEdit->setText(path);

        //编码格式类
//        QTextCodec * codec = QTextCodec::codecForName("gbk");

        //读取内容 放入到 textEdit中
        //QFile 默认支持的格式是utf-8
        QFile file(path); //参数就是读取文件的路径
        //设置打开方式
        file.open(QIODevice::ReadWrite);
        //QByteArray array = file.readAll();

        QByteArray array;
        while(!file.atEnd())
        {
            array+=file.readLine();//按行读
        }
        //将读取到的数据 放到textEdit中
        ui->textEdit->setText(array);

        //对文件对象进行关闭
        file.close();
    });
}
void Model::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/bg_03.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}
Model::~Model()
{
    delete ui;
}
