#include "addgroupalert.h"
#include "ui_addgroupalert.h"

addgroupalert::addgroupalert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addgroupalert)
{
    ui->setupUi(this);
}

addgroupalert::~addgroupalert()
{
    delete ui;
}
