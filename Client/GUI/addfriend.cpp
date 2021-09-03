#include "addfriend.h"
#include "ui_addfriend.h"
#include "Controller/clientcontroller.h"
#include "Network/handlerreg.h"
#include "Network/Handlers/friend_request_result_handler.h"
#include <QGraphicsDropShadowEffect>

#include"addsuccess.h"
addsuccess * addfriend:: Addsuccess = nullptr;

addsuccess * addfriend::GetAddSuccess(){
    if(Addsuccess == nullptr){
        Addsuccess = new addsuccess;
    }
    return Addsuccess;
}
addfriend::addfriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addfriend)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);//设置向哪个方向产生阴影效果，（0,0）表示向四周发散
    shadow->setColor(QColor(38, 78, 119,255));//阴影颜色
    shadow->setBlurRadius(20); //模糊度
    ui->widget->setGraphicsEffect(shadow);

    connect( (FriendRequestResultHandler *) HandlerReg::GetRegObj()->getHandler(MsgType::REQUEST_ADD_FRIEND_AGREED),
             &FriendRequestResultHandler::sigAddFriendSuccessful,
             this,
             &addfriend::addFriendSuccess);
    connect((FriendRequestResultHandler *) HandlerReg::GetRegObj()->
            getHandler(MsgType::REQUEST_ADD_FRIEND_DECLINED),
            &FriendRequestResultHandler::sigAddFriendFailed,
            this,
            &addfriend::showAddFriendFailed
            );
}

addfriend::~addfriend()
{
    delete ui;
}

void addfriend::on_toolButton_clicked()
{
    this->close();
}


void addfriend::on_addFriendButton_clicked()
{
    quint32 id = ui->textEdit->toPlainText().toUInt();
    ClientController::GetClientInstance()->requestAddFriend(id);
}

void addfriend::addFriendSuccess()
{
    addsuccess * w = GetAddSuccess();
    w->showflag(true);
    w->show();
    this->close();
}

void addfriend::showAddFriendFailed(MsgType type){
    addsuccess * w = GetAddSuccess();
    w->settype(type);
    w->showflag(false);
    qDebug() << "before show w";
    w->show();
    qDebug() << "after show w";
    this->close();
}
