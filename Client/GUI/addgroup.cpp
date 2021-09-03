#include "addgroup.h"
#include "ui_addgroup.h"
#include "Controller/clientcontroller.h"
#include "Network/handlerreg.h"
#include "Network/Handlers/group_add_request_result.h"
#include <QGraphicsDropShadowEffect>

#include"addsuccess.h"
addsuccess * addgroup:: Addsuccess = nullptr;

addsuccess * addgroup::GetAddSuccess(){
    if(Addsuccess == nullptr){
        Addsuccess = new addsuccess;
    }
    return Addsuccess;
}
addgroup::addgroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addgroup)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);//设置向哪个方向产生阴影效果，（0,0）表示向四周发散
    shadow->setColor(QColor(38, 78, 119,255));//阴影颜色
    shadow->setBlurRadius(20); //模糊度
    ui->widget->setGraphicsEffect(shadow);

    connect((AddGroupResultHandler*)HandlerReg::GetRegObj()->
        getHandler(MsgType::ADD_GROUP_ERROR),
        &AddGroupResultHandler::sigAddGroupFailed,
        this,
        &addgroup::showAddGroupFailed);
    connect((AddGroupResultHandler*)HandlerReg::GetRegObj()->
        getHandler(MsgType::ADD_GROUP_SUCCESS),
        &AddGroupResultHandler::sigAddGroupSuccessful,
        this,
        &addgroup::showAddGroupSuccess);
}

addgroup::~addgroup()
{
    delete ui;
}

void addgroup::on_closeButton_clicked()
{
    this->close();
}


void addgroup::on_addgroupButton_clicked()
{
    quint32 id = ui->textEdit->toPlainText().toUInt();
    ClientController::GetClientInstance()->requestAddGroup(id);
}

void addgroup::showAddGroupSuccess()
{
    addsuccess * w = GetAddSuccess();
    w->showflag(true);
    w->show();
    this->close();
}

void addgroup::showAddGroupFailed(MsgType type){
    addsuccess * w = GetAddSuccess();
    w->settype(type);
    w->showflag(false);
    qDebug() << "before show w";
    w->show();
    qDebug() << "after show w";
    this->close();
}
