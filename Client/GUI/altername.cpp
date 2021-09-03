#include "altername.h"
#include "ui_altername.h"
#include "alarmwidget.h"
#include <QGraphicsDropShadowEffect>

#include "DataModel/datamodel.h"
#include "Controller/clientcontroller.h"

#include "Utilities/log.h"
#include "Network/handlerreg.h"

alterName::alterName(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alterName)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint|this->windowFlags());

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);//设置向哪个方向产生阴影效果，（0,0）表示向四周发散
    shadow->setColor(QColor(38, 78, 119,255));//阴影颜色
    shadow->setBlurRadius(25); //模糊度
    ui->widget->setGraphicsEffect(shadow);

    //flag = 0;
    //newname = "用户";

}

alterName::~alterName()
{
    delete ui;
}

void alterName::on_cancelButton_clicked()
{
    this->close();
}


void alterName::on_submitButton_clicked()
{
    alarmWidget* w = new alarmWidget;
    if(ui->newName->toPlainText() != "")
    {
        w->setLabel("修改成功");
        w->show();
        ClientController::GetClientInstance()->requestModifyUserName(ui->newName->toPlainText());
        //flag = 1;
        //newname = ui->newName->text();
        //将修改的信息传入数据库
        this->close();
    }
    else
    {
        QString str1 = "修改失败";
        QString str2 = "昵称不能为空";
        w->setLabel(str1+"\n"+str2);
        w->show();
    }
}

void alterName::mousePressEvent(QMouseEvent *event)
{
   if(event->button() == Qt::LeftButton)
   {
       m_point = event->globalPos() - pos(); //计算移动量
       event->accept();
   }
}

//鼠标移动
void alterName::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_point);
        event->accept();
    }
}
