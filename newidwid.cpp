#pragma once
#include "newidwid.h"
#include "ui_newidwid.h"
#include "mainwindow.h"
#include <string>
#include "QDebug"
#include "QMessageBox"
#include "ID.h"

bool ispasswordlawful(string Id) {
    if (Id.size() < 8 || Id.size() > 16) {
        return 0;
    }
    return 1;
}

newIdWid::newIdWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newIdWid)
{
    this->setFixedSize(1080,960);
    QPalette pa(this->palette());
    QImage img = QImage(":/picture/first.jpeg");
    img = img.scaled(this->size());
    QBrush* pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setPalette(pa);
    ui->setupUi(this);
    connect(ui->back,&QPushButton::clicked,this,[=](){
        this->close();
        MainWindow* first = new MainWindow();
        first->show();
    });
    connect(ui->enter,&QPushButton::clicked,this,[=](){
        ID a;
        QString tmp1,tmp2,tmp3;
        tmp1 = ui->putId->text();
        tmp2 = ui->putPassword1->text();
        tmp3 = ui->putPassword2->text();
        if(!ispasswordlawful(tmp1.toStdString()))QMessageBox::information(this,"失败","账号长度小于8或大于16");
        else if(a.usedId(tmp1.toStdString()))QMessageBox::information(this,"失败","该账号已存在");
        else if(!ispasswordlawful(tmp2.toStdString()))QMessageBox::information(this,"失败","密码长度小于8或大于16");
        else if(tmp2 != tmp3)QMessageBox::information(this,"失败","两次输入的密码不一致");
        else if(tmp2 == tmp3){
            a.NewId(tmp1.toStdString(),tmp2.toStdString());
            QMessageBox::information(this,"成功","注册成功");
        }
    });
}

newIdWid::~newIdWid()
{
    delete ui;
}

