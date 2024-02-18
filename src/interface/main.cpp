//#include "mainwindow.h"
//#include <QApplication>
//#include <QDebug>
//#include <QSqlDatabase>
//#include <QSqlQuery>
//
//int main(int argc, char *argv[])
//{
//    //创建数据库
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    //设置数据库名
//    db.setDatabaseName("password.db");
//    //打开数据库
//    if(db.open())
//        qDebug()<<"open database suc";
//    else
//        qDebug()<<"open database fail";
//    //创建数据库表用来存储用户名密码
//    QString cmd = "create table if not exists userinfo (username varchar(64), password varchar(64))";
//    //执行sql语句
//    QSqlQuery query;
//    if(query.exec(cmd))
//    {
//        qDebug()<<"exec suc";
//    }
//
//
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//
//    return a.exec();
//}
