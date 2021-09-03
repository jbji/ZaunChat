#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>

//UserInfo can't be a QObject.

class UserInfo
{

public:
    explicit UserInfo(quint32 id = 0x0000,
            QString name = "",
            QString pwd = "",
            QString avatar_name = ""
        );
    //getters
    quint32 getID() const;
    QString getName() const;
    QString getPwd() const;
    QString getAvatarName() const;
    //static from method

signals:

protected:
    quint32 id;
    QString name;
    QString pwd;
    QString avatar_name;

public:

    //对于UserInfo的QByteArray编码方式
    // | quint32 id | quint32 name size | name | quint32 pwd size | pwd | quint32 avatar_name size | avatar |

    static UserInfo fromQByteArray(QByteArray chat_msg);
    QByteArray toQByteArray();
};

#endif // USERINFO_H
