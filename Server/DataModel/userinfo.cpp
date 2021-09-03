#include "userinfo.h"

#include <QtNetwork>

UserInfo::UserInfo(quint32 id,
            QString name,
            QString pwd,
            QString avatar_name
        ): id(id), name(name), pwd(pwd), avatar_name(avatar_name)
{

}

// | quint32 id | quint32 name size | name | quint32 pwd size | pwd |

quint32 UserInfo::getID() const{
    return id;
}

QString UserInfo::getName() const{
    return name;
}

QString UserInfo::getPwd() const{
    return pwd;
}

QString UserInfo::getAvatarName() const{
    return avatar_name;
}


UserInfo UserInfo::fromQByteArray(QByteArray chat_msg){

    QDataStream in(chat_msg);
    in.setVersion(QDataStream::Qt_5_12);

    UserInfo tmp;
    //write id
    in >> tmp.id;

    //write name
    quint32 size;
    in >> size;
    QByteArray tmpName;
    tmpName.resize(size);
    in >> tmpName;
    tmp.name = QString(tmpName);

    //write pwd
    in >> size;
    QByteArray tmpPwd;
    tmpPwd.resize(size);
    in >> tmpPwd;
    tmp.pwd = QString(tmpPwd);

    //write avatar
    in >> size;
    QByteArray tmpAvatar;
    tmpAvatar.resize(size);
    in >> tmpAvatar;
    tmp.avatar_name = QString(tmpAvatar);

    return tmp;
}

// | quint32 id | quint32 name size | name | quint32 pwd size | pwd | quint32 avatar_name size | avatar |

QByteArray UserInfo::toQByteArray(){

    QByteArray block;

    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    //输出id
    out << quint32(id);

    //输出name
    out << quint32(0);//预留给name的大小
    out << name.toUtf8();
    out.device()->seek(4);
    out << (quint32)(block.size()-sizeof(quint32)*2);
    out.device()->seek(block.size());

    //输出pwd
    int size_index = block.size();
    out << quint32(0);
    out << pwd.toUtf8();

    out.device()->seek(size_index);
    out << (quint32)(block.size() - size_index - sizeof(quint32));
    out.device()->seek(block.size());

    //输出avatar
    size_index = block.size();
    out << quint32(0);
    out << avatar_name.toUtf8();

    out.device()->seek(size_index);
    out << (quint32)(block.size() - size_index - sizeof(quint32));
    out.device()->seek(block.size());

    return block;
}

