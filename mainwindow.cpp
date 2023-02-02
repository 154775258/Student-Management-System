#pragma once
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ID.h"
#include <string>
#include "QDebug"
#include "QMessageBox"
#include "newidwid.h"
#include "studentwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(1080,960);
    this->setWindowIcon(QPixmap(":/picture/second.jpg"));
    this->setWindowTitle("学生管理系统");
    //设置背景图片
    QPalette pa(this->palette());
    QImage img = QImage(":/picture/first.jpeg");
    img = img.scaled(this->size());
    QBrush* pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setPalette(pa);
    //设置结束
    ui->setupUi(this);
    //登录按钮按下后
    connect(ui->signIn,&QPushButton::clicked,this,[=](){
        ID a;
        QString tmp1,tmp2;
        tmp1 = ui->putInId->text();
        tmp2 = ui->putInPassword->text();
        if(a.check(tmp1.toStdString(),tmp2.toStdString())){
            QMessageBox::information(this,"成功","登陆成功");
            this->close();
            studentWindow * p = new studentWindow();
            p->show();
        }
        else QMessageBox::information(this,"失败","密码或账号有误");
    });
    connect(ui->newId,&QPushButton::clicked,this,[=](){
        this->close();
        newIdWid*second = new newIdWid();
        second->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

