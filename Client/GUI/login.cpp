#include "login.h"
#include "ui_login.h"
#include <QMouseEvent>
#include "register.h"
#include "mainwindow.h"
#include "alarmwidget.h"
#include <QGraphicsDropShadowEffect>

#include "DataModel/datamodel.h"
#include "Controller/clientcontroller.h"

#include "Utilities/log.h"
#include "Network/handlerreg.h"

MainWindow * login:: mw = NULL;
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint|this->windowFlags());

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);//设置向哪个方向产生阴影效果，（0,0）表示向四周发散
    shadow->setColor(QColor(38, 78, 119,255));//阴影颜色
    shadow->setBlurRadius(25); //模糊度
    this->setGraphicsEffect(shadow);
    connect( (GroupListHandler *) HandlerReg::GetRegObj()->getHandler(MsgType::ALL_GROUP_LIST),
                    &GroupListHandler::sigGroupListGotcha,
                    this,
                    &login::showLoginSuccessful
                );
    connect( (LoginHandler *) HandlerReg::GetRegObj()->getHandler(MsgType::LOGIN_ERROR),
                &LoginHandler::sigLoginFailed,
                this,
                &login::showLoginFailed
            );
}

login::~login()
{
    delete ui;
    delete  mw;
}

void login::showLoginSuccessful(UserInfo info){

    MainWindow *mainw = GetMainWindowInstance();
    mainw->initUserInfo(info);
    mainw->setUserInfo();
    mainw->show();
    this->close();
}

void login::showLoginFailed(){
    alarmWidget* w =new alarmWidget;
    QString str1 = "登录失败";
    QString str2 = "账号或密码不正确";
    w->setLabel(str1+"\n"+str2);
    w->show();
}
//鼠标按下
void login::mousePressEvent(QMouseEvent *event)
{
   if(event->button() == Qt::LeftButton)
   {
       m_point = event->globalPos() - pos(); //计算移动量
       event->accept();
   }
}

//鼠标移动
void login::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_point);
        event->accept();
    }
}

//关闭窗口
void login::on_closeButton_clicked()
{
    this->close();
}

//窗口最小化
void login::on_minimizeButton_clicked()
{
    this->showMinimized();
}

//注册账号
void login::on_registerButton_clicked()
{
    Register *w = new Register;
    w->show();
    this->close();
}

//登录
void login::on_loginButton_clicked()
{
    //通信函数
    quint32 id = ui->account->text().toUInt();
    QString pw = ui->password->text();
    ClientController::GetClientInstance()
            ->requestLogin(id, pw);
}


void login::on_password_textEdited(const QString &arg1)
{
    ui->password->setEchoMode(QLineEdit::Password);
}
MainWindow * login::GetMainWindowInstance(){
    if(mw == nullptr){
        mw = new MainWindow;
    }
    return mw;
}
