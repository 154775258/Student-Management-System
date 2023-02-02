#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H
#pragma once
#include <QWidget>
#include <string>

namespace Ui {
class studentWindow;
}

class studentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit studentWindow(QWidget *parent = nullptr);
    ~studentWindow();
    void pushStudentAll(QString tmp1,std::string id);

private:
    Ui::studentWindow *ui;
};

#endif // STUDENTWINDOW_H
