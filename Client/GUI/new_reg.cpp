#include "new_reg.h"
#include "ui_new_reg.h"
#include "QAction"
#include "login.h"
#include "QtDebug"
extern login * loginw;
new_reg::new_reg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::new_reg)
{
    ui->setupUi(this);
}

new_reg::~new_reg()
{
    delete ui;
}

void new_reg::showid(){
    ui->textEdit->setText("注册成功!您的id号为"+myid);
}

void new_reg::showgroupid(){
    ui->textEdit->setText("注册成功!\n您创建的群聊号为"+myid);
}
QString new_reg::myid="";

void new_reg::Setid(QString x){
    qDebug()<<x;
    myid=x;
}

QString new_reg::Getid(){
    return myid;
}



void new_reg::on_toolButton_clicked()
{
    if(myid.toUInt()<1000000) loginw->show();
    this->close();
}

