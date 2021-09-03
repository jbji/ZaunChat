#include "choosefile.h"
#include "ui_choosefile.h"
#include "alarmwidget.h"
#include <QFileDialog>//核心
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include "Controller/clientcontroller.h"
void chooseFile::setFriendInfo(User * Friend){
    friendInfo = Friend;
}
chooseFile::chooseFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chooseFile)
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

chooseFile::~chooseFile()
{
    delete ui;
}

void chooseFile::recvMsg(){

}
void chooseFile::on_pushButton_clicked()//点击选择文件
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                 "/home"
                 );//tr("Images (*.png *.xpm *.jpg *.txt *.gz)")
    //fileName = QFileDialog::getOpenFileName(this);
    qDebug() << "fileName:" << fileName;
    ui->lineEdit->setText(fileName);
    ui->lineEdit->setCursorPosition(0);//把光标移到左侧
}


void chooseFile::on_pushButton_2_clicked()
{
    quint32 receiver = friendInfo->getid();
    QString path = ui->lineEdit->text();
    if(ClientController::GetClientInstance()->requestSendFile(receiver, path)){
        qDebug()<<"SEND IMG SUCCESS";
    }else{
        qDebug()<<"SEND IMG ERROR";
    }
    this->close();
}

void chooseFile::on_cancelButton_clicked()
{
    this->close();
}

void chooseFile::mousePressEvent(QMouseEvent *event)
{
   if(event->button() == Qt::LeftButton)
   {
       m_point = event->globalPos() - pos(); //计算移动量
       event->accept();
   }
}

//鼠标移动
void chooseFile::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_point);
        event->accept();
    }
}
