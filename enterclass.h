#ifndef ENTERCLASS_H
#define ENTERCLASS_H
#pragma once
#include <QWidget>
#include <string>

namespace Ui {
class enterClass;
}

class enterClass : public QWidget
{
    Q_OBJECT

public:
    explicit enterClass(QWidget *parent = nullptr);
    ~enterClass();
    void pushStudentAll(std::string id);

private:
    Ui::enterClass *ui;
};

#endif // ENTERCLASS_H
