#include "alterimg.h"
#include "ui_alterimg.h"
#include "alarmwidget.h"
#include <QFileDialog>//核心
#include <QDebug>
#include <QGraphicsDropShadowEffect>

#include "DataModel/datamodel.h"
#include "Controller/clientcontroller.h"

#include "Utilities/log.h"
#include "Network/handlerreg.h"
alterImg::alterImg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alterImg)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint|this->windowFlags());

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);//设置向哪个方向产生阴影效果，（0,0）表示向四周发散
    shadow->setColor(QColor(38, 78, 119,255));//阴影颜色
    shadow->setBlurRadius(25); //模糊度
    ui->widget->setGraphicsEffect(shadow);

    clientsocket = new QTcpSocket(this);
    clientsocket->connectToHost("127.0.0.1",6666);
    connect(clientsocket,SIGNAL(readyRead()),this,SLOT(recvMsg()));

}

alterImg::~alterImg()
{
    delete ui;
}


void alterImg::recvMsg(){

}
void alterImg::on_pushButton_clicked()//点击选择文件
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                 "/home"
                 );//tr("Images (*.png *.xpm *.jpg *.txt *.gz)")
    //fileName = QFileDialog::getOpenFileName(this);
    qDebug() << "fileName:" << fileName;
    ui->lineEdit->setText(fileName);
    ui->lineEdit->setCursorPosition(0);//把光标移到左侧
}


void alterImg::on_pushButton_2_clicked()
{
    QString fileName = ui->lineEdit->text();
    qDebug()<<fileName;

    alarmWidget* w = new alarmWidget;
    if(fileName != "")
    {
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        QByteArray t = file.readAll();
        clientsocket->write(t);
        file.close();

        w->setLabel("修改成功");
        w->show();
        //将修改的信息传入数据库
        ClientController::GetClientInstance()->requestModifyAvatar(fileName);
        this->close();
    }
    else
    {
        QString str1 = "修改失败";
        QString str2 = "未选择任何图片";
        w->setLabel(str1+"\n"+str2);
        w->show();
    }
}

void alterImg::on_cancelButton_clicked()
{
    this->close();
}

void alterImg::mousePressEvent(QMouseEvent *event)
{
   if(event->button() == Qt::LeftButton)
   {
       m_point = event->globalPos() - pos(); //计算移动量
       event->accept();
   }
}

//鼠标移动
void alterImg::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_point);
        event->accept();
    }
}
