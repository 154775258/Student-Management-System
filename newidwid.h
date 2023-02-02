#ifndef NEWIDWID_H
#define NEWIDWID_H
#pragma once
#include <QWidget>

namespace Ui {
class newIdWid;
}

class newIdWid : public QWidget
{
    Q_OBJECT

public:
    explicit newIdWid(QWidget *parent = nullptr);
    ~newIdWid();

private:
    Ui::newIdWid *ui;
};

#endif // NEWIDWID_H
