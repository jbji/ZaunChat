#include "user.h"
#include "QDebug"
User::User()
{
    id = 0;
    username = "";
    img = "";
}

User::User(quint32 Id, QString name, QString Img)
{
    id = Id;
    username = name;
    img = Img;
}

User::~User(){}

quint32 User::getid() const
{
    return id;
}

QString User::getUsername() const
{
    return username;
}

QString User::getImage() const
{
    return img;
}
void User::Set(quint32 Id,QString Username,QString Img){
    id = Id; username = Username; img = Img;
    qDebug()<<"YES"<<Id;
}
