#include "alterpwd.h"
#include "ui_alterpwd.h"
#include "alarmwidget.h"
#include <QGraphicsDropShadowEffect>

alterPwd::alterPwd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alterPwd)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint|this->windowFlags());

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);//设置向哪个方向产生阴影效果，（0,0）表示向四周发散
    shadow->setColor(QColor(38, 78, 119,255));//阴影颜色
    shadow->setBlurRadius(25); //模糊度
    ui->widget->setGraphicsEffect(shadow);
}

alterPwd::~alterPwd()
{
    delete ui;
}

void alterPwd::on_cancelButton_clicked()
{
    this->close();
}


void alterPwd::on_submitButton_clicked()
{

    alarmWidget* w = new alarmWidget;
    if(1)
    {
        QString str1 = "修改失败";
        QString str2 = "旧密码不正确";
        w->setLabel(str1+"\n"+str2);
        w->show();
    }
    else if(ui->newpwd->text() != ui->newpwd2->text())
    {
        QString str1 = "修改失败";
        QString str2 = "两次输入密码不同";
        w->setLabel(str1+"\n"+str2);
        //w->setLabel("修改失败，两次输入密码不同");
        w->show();
    }
    else if(ui->newpwd->text() == "")
    {
        QString str1 = "修改失败";
        QString str2 = "密码不能为空";
        w->setLabel(str1+"\n"+str2);
        w->show();
    }
    else
    {
        w->setLabel("修改成功");
        w->show();
        //将修改的信息传入数据库
        this->close();
    }


}


