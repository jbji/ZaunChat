#include "chooseimage.h"
#include "ui_chooseimage.h"
#include "QFileDialog"
#include "QDebug"
#include <QGraphicsDropShadowEffect>
#include "mainwindow.h"
#include "Controller/clientcontroller.h"

void ChooseImage::setFriendInfo(User * Friend){
    friendInfo = Friend;
}
ChooseImage::ChooseImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseImage)
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

ChooseImage::~ChooseImage()
{
    delete ui;
}

void ChooseImage::on_chooseImg_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                 "/home"
                 );//tr("Images (*.png *.xpm *.jpg *.txt *.gz)")
    //fileName = QFileDialog::getOpenFileName(this);
    qDebug() << "fileName:" << fileName;
    ui->lineEdit->setText(fileName);
    ui->lineEdit->setCursorPosition(0);//把光标移到左侧
}


void ChooseImage::on_cancelButton_clicked()
{
    this->close();
}


void ChooseImage::on_sendImg_clicked()
{
    quint32 receiver = friendInfo->getid();
    QString path = ui->lineEdit->text();
    if(ClientController::GetClientInstance()->requestSendImg(receiver, path)){
        qDebug()<<"SEND IMG SUCCESS";
    }else{
        qDebug()<<"SEND IMG ERROR";
    }
    this->close();
    emit readyShowMyIMG(path,ClientController::GetClientInstance()->getMyInfo().getID());
}

