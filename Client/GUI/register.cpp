#include "register.h"
#include "ui_register.h"
#include "login.h"
#include "alarmwidget.h"
#include <QGraphicsDropShadowEffect>

#include "DataModel/datamodel.h"
#include "Controller/clientcontroller.h"

#include "Utilities/log.h"
#include "Network/handlerreg.h"

#include "new_reg.h"
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint|this->windowFlags());

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);//设置向哪个方向产生阴影效果，（0,0）表示向四周发散
    shadow->setColor(QColor(38, 78, 119,255));//阴影颜色
    shadow->setBlurRadius(25); //模糊度
    this->setGraphicsEffect(shadow);

    connect( (RegisterHandler *) HandlerReg::GetRegObj()->getHandler(MsgType::REGISTER_SUCCESS),
                &RegisterHandler::sigRegSuccessful,
                this,
                &Register::showRegisterSuccessful
            );

    connect( (RegisterHandler *) HandlerReg::GetRegObj()->getHandler(MsgType::REGISTER_ERROR),
                &RegisterHandler::sigRegFailed,
                this,
                &Register::showRegisterFailed
            );
}

Register::~Register()
{
    delete ui;
}


void Register::showRegisterSuccessful(UserInfo info){
    new_reg*newreg=new new_reg;
    newreg->Setid(QString::number(info.getID()));
    newreg->showid();
    newreg->show();
    this->close();
}

void Register::showRegisterFailed(){
    alarmWidget*w=new alarmWidget;
    w->setLabel("注册失败！");
    w->show();
}
//关闭窗口
void Register::on_closeButton_clicked()
{
    this->close();
}

//窗口最小化
void Register::on_minimizeButton_clicked()
{
    this->showMinimized();
}


void Register::on_loginButton_clicked()
{
    login *w = new login;
    w->show();
    this->close();
}


void Register::on_registerButton_clicked()
{
    alarmWidget* w = new alarmWidget;
    if(ui->pwd->text() != ui->pwd2->text())
    {
        QString str1 = "注册失败";
        QString str2 = "两次输入密码不同";
        w->setLabel(str1+"\n"+str2);
        w->show();
    }
    else if(ui->pwd->text() == "")
    {
        QString str1 = "注册失败";
        QString str2 = "密码不能为空";
        w->setLabel(str1+"\n"+str2);
        w->show();
    }
    else
    {
        //发送
        QString username=ui->account->text();
        QString pw=ui->pwd->text();
        ClientController::GetClientInstance()->requestRegister(username, pw);
    }
}


void Register::on_pwd_textEdited(const QString &arg1)
{
    ui->pwd->setEchoMode(QLineEdit::Password);
}


void Register::on_pwd2_textEdited(const QString &arg1)
{
    ui->pwd2->setEchoMode(QLineEdit::Password);
}
