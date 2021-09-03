#include "addfriendalert.h"
#include "ui_addfriendalert.h"
#include "Controller/clientcontroller.h"
#include "GUI/mainwindow.h"
#include <QGraphicsDropShadowEffect>

addfriendalert::addfriendalert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addfriendalert)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);//设置向哪个方向产生阴影效果，（0,0）表示向四周发散
    shadow->setColor(QColor(38, 78, 119,255));//阴影颜色
    shadow->setBlurRadius(20); //模糊度
    ui->widget->setGraphicsEffect(shadow);
}

addfriendalert::~addfriendalert()
{
    delete ui;
}

void addfriendalert::setSender(UserInfo sender)
{
    this->Sender = sender;
}

void addfriendalert::setReceiverId(quint32 receiverId)
{
    this->receiverId = receiverId;
}

void addfriendalert::setAlertText()
{
    //ui->senderId->setText(QString::number(senderId));
    QString s="用户"+QString::number(getSenderId())+"请求添加您为好友！";
    ui->textEdit->setText(s);
}

quint32 addfriendalert::getSenderId()
{
    return Sender.getID();
}

quint32 addfriendalert::getReceiverId()
{
    return receiverId;
}

void addfriendalert::on_agree_clicked()
{
    ClientController::GetClientInstance()->agreeFriendRequest(getSenderId(), receiverId);
    ClientController::GetClientInstance()->getFriendList()->append(Sender);
    QMap<quint32,QList<ChatMessage>*> * tmp = ClientController::GetClientInstance()->getChatMsgMap();
    (*tmp)[Sender.getID()] = new QList<ChatMessage>;
    qDebug()<<"Sender ID:"<<Sender.getID();
    emit refreshFriendList();
    this->close();
}


void addfriendalert::on_refuse_clicked()
{
    ClientController::GetClientInstance()->declineFriendRequest(getSenderId(), receiverId);
    this->close();
}


void addfriendalert::on_toolButton_clicked()
{
    this->close();
}
