#ifndef USER_H
#define USER_H

#include <QObject>
class User
{
public:
    User();
    User(quint32, QString name, QString img);
    ~User();

    quint32 getid() const;
    QString getUsername() const;
    QString getImage() const;
    void Set(quint32 Id,QString Username = "",QString Img = "");

private:
    quint32 id;
    QString username;
    QString img;
};

#endif // USER_H
