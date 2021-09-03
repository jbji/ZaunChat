#include "new_windows.h"
#include "ui_new_windows.h"
#include <QDebug>
#include "Controller/clientcontroller.h"

new_windows::new_windows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::new_windows)
{
    ui->setupUi(this);
}

new_windows::~new_windows()
{
    delete ui;
}

void new_windows::SetSend(quint32 x){
    send=x;
    ui->lineEdit->setText(QString::number(send)+"请求添加你为好友");
}
quint32 new_windows::GetSend(){
    return send;

}
void new_windows::SetReceive(quint32 x){
    receive=x;

}
quint32 new_windows::GetReceive(){
    return receive;
}

void new_windows::on_pushButton_clicked()
{
    ClientController::GetClientInstance()->
            agreeFriendRequest(send,receive,"");
    close();
}


void new_windows::on_pushButton_2_clicked()
{
    ClientController::GetClientInstance()->
            declineFriendRequest(send,receive,"");
    close();
}

