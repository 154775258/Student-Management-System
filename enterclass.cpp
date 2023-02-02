#pragma once
#include "enterclass.h"
#include "ui_enterclass.h"
#include "studentwindow.h"
#include <QDebug>
#include <string>
#include <iostream>
#include<iostream>
#include<fstream>
#include"student.h"
#include "QMessageBox"

void enterClass::pushStudentAll(string id){
    student tmp;
    tmp.pushData();
    ui->mainT->insertPlainText("学号:");
    ui->mainT->insertPlainText(QString::fromStdString(id));
    if (tmp.studentClass.count(id)) {
        ui->mainT->insertPlainText("   班级:");
        ui->mainT->insertPlainText(QString::fromStdString(tmp.studentClass[id]));
    }
    else {
        ui->mainT->insertPlainText("未加入班级");
    }
    ui->mainT->insertPlainText("   姓名：");
    ui->mainT->insertPlainText(QString::fromStdString(tmp.nameId[id]));
    ui->mainT->insertPlainText("科目：\n");
    for (int i = 0; i < tmp.studentScores[id].size(); i++) {
        ui->mainT->insertPlainText(QString::fromStdString(tmp.classDiscipline[tmp.studentClass[id]][i]));
         ui->mainT->insertPlainText("：");
         ui->mainT->insertPlainText(QString::fromStdString(tmp.studentScores[id][i]));
    }
    ui->mainT->insertPlainText("\n");
}


enterClass::enterClass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::enterClass)
{
    this->setFixedSize(1080,960);
    QPalette pa(this->palette());
    QImage img = QImage(":/picture/third.jpg");
    img = img.scaled(this->size());
    QBrush* pic = new QBrush(img);
    pa.setBrush(QPalette::Window,*pic);
    this->setPalette(pa);
    ui->setupUi(this);
    std::string className;
    std::ifstream putFile;
    putFile.open("className.dat");
    putFile >> className;
    putFile.close();
    student allStudent;
    allStudent.pushData();
    for(int i = 0 ; i < allStudent.classStudentId[className].size();i++){
        pushStudentAll(allStudent.classStudentId[className][i]);
    }
    connect(ui->back,&QPushButton::clicked,this,[=](){
        this->close();
        studentWindow* a = new studentWindow();
        a->show();
    });
    connect(ui->close,&QPushButton::clicked,this,[=](){
        this->close();
    });
    connect(ui->one,&QPushButton::clicked,this,[=](){
        student tmp;
        tmp.pushData();
        QString tmp1 = ui->one1->text();
        string a = tmp1.toStdString();
        if(tmp.findDiscipline(className, a) != -1)QMessageBox::information(this,"失败","该科目已存在");
        else{
            tmp.addDiscipline(className,a);
            QMessageBox::information(this,"成功","科目添加成功");
            tmp.writeData();
        }
    });
    connect(ui->two,&QPushButton::clicked,this,[=](){
        student tmp;
        tmp.pushData();
        QString tmp1 = ui->two1->text();
        string a = tmp1.toStdString();
        tmp1 = ui->two2->text();
        string b = tmp1.toStdString();
        tmp1 = ui->two3->text();
        string c = tmp1.toStdString();
        tmp1 = ui->two4->text();
        string d = tmp1.toStdString();
        if(!tmp.nameId.count(a))QMessageBox::information(this,"失败","未找到该学号");
        else if(tmp.findDiscipline(tmp.studentClass[a],b) == -1)QMessageBox::information(this,"失败","未找到该科目");
        else if(c != d)QMessageBox::information(this,"失败","两次分数不一致");
        else{
            tmp.reviseStudentScores(a,b,c);
            QMessageBox::information(this,"成功","分数修改成功");
            tmp.writeData();
        }
    });
    connect(ui->three,&QPushButton::clicked,this,[=](){
        student tmp;
        tmp.pushData();
        QString tmp1 = ui->three1->text();
        string a = tmp1.toStdString();
        if(!tmp.nameId.count(a) || tmp.findClassId(a,className) != -1)QMessageBox::information(this,"失败","未找到该学生或该学生已在班级中");
        else{
            tmp.addStudentInClass(className,a);
            tmp.writeData();
            QMessageBox::information(this,"成功","已添加学生进班级");
        }
    });
    connect(ui->four,&QPushButton::clicked,this,[=](){
        student tmp;
        tmp.pushData();
        QString tmp1 = ui->four1->text();
        string a = tmp1.toStdString();
        if(tmp.findClassId(a, className) == -1)QMessageBox::information(this,"失败","未找到该学生");
        else{
            tmp.eraseStudentInClass(className,a);
            tmp.writeData();
            QMessageBox::information(this,"成功","移除成功");
        }
    });
    connect(ui->five,&QPushButton::clicked,this,[=](){
        student tmp;
        tmp.pushData();
        QString tmp1 = ui->five1->text();
        string a = tmp1.toStdString();
        if(tmp.findDiscipline(className, a) == -1)QMessageBox::information(this,"失败","班级内无此科目");
        else{
            tmp.eraseClassDiscipline(className,a);
            tmp.writeData();
            QMessageBox::information(this,"成功","科目已删除");
        }
    });

}

enterClass::~enterClass()
{
    delete ui;
}

