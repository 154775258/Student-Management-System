#pragma once
#include "studentwindow.h"
#include "ui_studentwindow.h"
#include "enterclass.h"
#include <vector>
#include "QDebug"
#include "QMessageBox"
#include "student.h"
#include <unordered_map>
#include<iostream>
#include<fstream>

void studentWindow::pushStudentAll(QString tmp1,string id){
    student tmp;
    tmp.pushData();
    ui->pushClass->insertPlainText("学号:");
    ui->pushClass->insertPlainText(QString::fromStdString(id));
    if (tmp.studentClass.count(id)) {
        ui->pushClass->insertPlainText("   班级:");
        ui->pushClass->insertPlainText(QString::fromStdString(tmp.studentClass[id]));
    }
    else {
        ui->pushClass->insertPlainText("未加入班级");
    }
    ui->pushClass->insertPlainText("   姓名：");
    ui->pushClass->insertPlainText(QString::fromStdString(tmp.nameId[id]));
    ui->pushClass->insertPlainText("科目：\n");
    for (int i = 0; i < tmp.studentScores[id].size(); i++) {
        ui->pushClass->insertPlainText(QString::fromStdString(tmp.classDiscipline[tmp.studentClass[id]][i]));
         ui->pushClass->insertPlainText("：");
         ui->pushClass->insertPlainText(QString::fromStdString(tmp.studentScores[id][i]));
    }
    ui->pushClass->insertPlainText("\n");
}

studentWindow::studentWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentWindow)
{
    this->setFixedSize(1080,960);
    QPalette pa(this->palette());
    QImage img = QImage(":/picture/third.jpg");
    img = img.scaled(this->size());
    QBrush* pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setPalette(pa);
    ui->setupUi(this);
    student tmp;
    tmp.pushData();
    ui->pushClass->clear();
    ui->pushClass->append("目前班级有:");
    for(int i = 0; i < tmp.classId.size();i++){
        ui->pushClass->append(QString::fromStdString(tmp.classId[i]));
    }

    connect(ui->one,&QPushButton::clicked,this,[=](){
        QString tmp1;
        student tmp;
        tmp.pushData();
        tmp1 = ui->one1->text();
        string a = tmp1.toStdString();
        if(!tmp.classStudentId.count(a))QMessageBox::information(this,"失败","该班级不存在");
        else{
            QMessageBox::information(this,"成功","正在进入班级");
            enterClass* other = new enterClass;
            ofstream writeFile;
            writeFile.open("className.dat");
            writeFile << a ;
            writeFile.close();
            this->close();
            other->show();
        }
    });
    connect(ui->tow,&QPushButton::clicked,this,[=](){
        student tmp;
        tmp.pushData();
        QString tmp1;
        tmp1 = ui->tow1->text();
        string id = tmp1.toStdString();
        if(!tmp.check(id))QMessageBox::information(this,"失败","该学号不存在");
        else{
            ui->pushClass->clear();
            pushStudentAll(tmp1,id);
        }
        tmp.writeData();
    });
    connect(ui->three,&QPushButton::clicked,this,[=](){
        student tmp;
        tmp.pushData();
        QString tmp1;
        tmp1 = ui->three1->text();
        string name = tmp1.toStdString();
        if(!tmp.studentName.count(name))QMessageBox::information(this,"失败","该姓名不存在");
        else QMessageBox::information(this,"成功","将依次输出姓名以及信息");
        ui->pushClass->clear();
        for(int i = 0;i < tmp.studentName[name].size();i++){
            pushStudentAll(tmp1,tmp.studentName[name][i]);
        }
        tmp.writeData();
    });
    connect(ui->four,&QPushButton::clicked,this,[=](){
        student tmp;
        tmp.pushData();
        QString tmp1;
        tmp1 = ui->four1->text();
        string a = tmp1.toStdString();
        if(!tmp.check(a))QMessageBox::information(this,"失败","该班级已存在");
        else{
            tmp.createClass(a);
            QMessageBox::information(this,"成功","班级已创建成功");
        }
        tmp.writeData();
    });
    connect(ui->five,&QPushButton::clicked,this,[=](){
        student tmp;
        tmp.pushData();
        QString tmp1;
        tmp1 = ui->five1->text();
        string id = tmp1.toStdString();
        if(!tmp.nameId.count(id))QMessageBox::information(this,"失败","未找到学生学号");
        else{
            tmp.eraseStudent(id);
            QMessageBox::information(this,"成功","已删除该学生");
        }
        tmp.writeData();
    });
    connect(ui->six,&QPushButton::clicked,this,[=](){
        student tmp;
        tmp.pushData();
        QString tmp1;
        tmp1 = ui->six1->text();
        string id = tmp1.toStdString();
        if(!tmp.classStudentId.count(id))QMessageBox::information(this,"失败","该班级不存在");
        else{
            tmp.eraseClass(id);
            QMessageBox::information(this,"成功","已删除该班级");
        }
        tmp.writeData();
    });
    connect(ui->seven,&QPushButton::clicked,this,[=](){
        QMessageBox::information(this,"成功","保存成功");
    });
    connect(ui->eight,&QPushButton::clicked,this,[=](){
        this->close();
    });
    connect(ui->nine,&QPushButton::clicked,this,[=](){
        student tmp;
        tmp.pushData();
        QString tmp1;
        tmp1 = ui->nine1->text();
        string id = tmp1.toStdString();
        tmp1 = ui->nine2->text();
        string name = tmp1.toStdString();
        if(tmp.nameId.count(id))QMessageBox::information(this,"失败","该学生已存在");
        else{
            tmp.addStudent(id,name);
            QMessageBox::information(this,"成功","已添加该学生");
        }
        tmp.writeData();
    });
}

studentWindow::~studentWindow()
{
    delete ui;
}
