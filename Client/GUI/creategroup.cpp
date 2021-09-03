#include "creategroup.h"
#include "ui_creategroup.h"
#include "new_reg.h"
#include <QGraphicsDropShadowEffect>
#include "Controller/clientcontroller.h"
#include "Network/handlerreg.h"
#include "new_reg.h"

new_reg * createGroup:: newGroupRegister = nullptr;

new_reg * createGroup::GetNewGroupRegister(){
    if(newGroupRegister == nullptr){
        newGroupRegister = new new_reg;
    }
    return newGroupRegister;
}


createGroup::createGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::createGroup)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);//设置向哪个方向产生阴影效果，（0,0）表示向四周发散
    shadow->setColor(QColor(38, 78, 119,255));//阴影颜色
    shadow->setBlurRadius(20); //模糊度
    ui->widget->setGraphicsEffect(shadow);
    connect((RegisterGroupHandler*)HandlerReg::GetRegObj()->
            getHandler(MsgType::REGISTER_GROUP_SUCCESS),
            &RegisterGroupHandler::sigRegGroupSuccessful,
            this,
            &createGroup::showRegisterGroupSuccessful);

}

createGroup::~createGroup()
{
    delete ui;
}

void createGroup::on_createButton_clicked()
{
    //向服务端发送创建申请，并返回一个id
    //quint32 id = 0;
    QString name=ui->account->text();
    //显示创建成功并显示我的id
   // QString Id = QString::number(id);
    ClientController::GetClientInstance()->registerGroup(name);
}
void createGroup::showRegisterGroupSuccessful(GroupInfo info){

    new_reg* w = GetNewGroupRegister();
    w->Setid(QString::number(info.getID()));
    w->showgroupid();
    w->show();

    //发送一个signal在群聊列表添加该群聊的item

    this->close();
}


void createGroup::on_closeButton_clicked()
{
    this->close();
}
