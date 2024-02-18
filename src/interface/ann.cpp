#include "ann.h"
#include "ui_ann.h"
#include <QPainter>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

ANN::ANN(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ANN)
{
    ui->setupUi(this);
    //设置标题
    setWindowTitle("ANN预测");

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
        //告诉system场景 我返回了 system场景监听ANN的返回按钮
        emit this->ANNBack();
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
        QFileInfo info(path);
        if(info.suffix() == "txt")
        {
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
        }
        if(info.suffix() == "csv")
        {
            // 设置打开方式
            file.open(QIODevice::ReadOnly);

            // 创建一个QTextStream对象来读取文件内容
            QTextStream in(&file);
            QString line;

            // 逐行读取文件内容
            while (!in.atEnd()) {
                line = in.readLine();
                // 将读取到的数据添加到textEdit中
                ui->textEdit->append(line);
            }

            // 关闭文件
            file.close();
        }
        if(info.suffix() != "csv"&& info.suffix()!= "txt")
        {
            ui->lineEdit->setText("导入文件格式非csv或txt");
        }


    });
}
void ANN::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/bg_03.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}
ANN::~ANN()
{
    delete ui;
}
