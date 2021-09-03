#include "addsuccess.h"
#include "ui_addsuccess.h"
#include "DataModel/Msg/msgtype.h"
#include <QGraphicsDropShadowEffect>

addsuccess::addsuccess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addsuccess)
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

addsuccess::~addsuccess()
{
    delete ui;
}

void addsuccess::on_ok_clicked()
{
    this->close();
    emit refreshFriendList();
}

void addsuccess::settype(MsgType x){
    type=x;
}

MsgType addsuccess::gettype(){
    return type;
}

void addsuccess::showflag(bool x){
    if(x==true){
        ui->textEdit->setText("添加成功！");
    }else{
        if(type==MsgType::REQUEST_ADD_FRIEND_DECLINED){
            ui->textEdit->setText("添加失败！对方已拒绝！");
        }else if(type==MsgType::REQUEST_ADD_FRIEND_ERROR_FRIEND_OFFLINE){
            ui->textEdit->setText("添加失败！对方不在线！");
        }else if(type==MsgType::REQUEST_ADD_FRIEND_ERROR){
            ui->textEdit->setText("添加失败！");
        }else if(type==MsgType::REQUEST_ADD_FRIEND_ERROR_FRIEND_NOT_EXIST){
            ui->textEdit->setText("添加失败！朋友不存在！");
        }else if(type==MsgType::REQUEST_ADD_FRIEND_ERROR_FRIENDSHIP_EXIST){
            ui->textEdit->setText("添加失败！对方已是您的好友！");
        }else if(type==MsgType::ADD_GROUP_ERROR_GROUPSHIP_EXIST){
            ui->textEdit->setText("添加失败！您已添加群聊！");
        }else if(type==MsgType::ADD_GROUP_ERROR_GROUP_NOT_EXIST){
            ui->textEdit->setText("添加失败！群聊不存在！");
        }
        //ui->textEdit->setText("添加失败！"+QString::number((int)type));
    }
}
