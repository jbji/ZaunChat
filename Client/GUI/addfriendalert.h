#ifndef ADDFRIENDALERT_H
#define ADDFRIENDALERT_H

#include <QWidget>
#include "DataModel/userinfo.h"
namespace Ui {
class addfriendalert;
}

class addfriendalert : public QWidget
{
    Q_OBJECT

public:
    explicit addfriendalert(QWidget *parent = nullptr);
    ~addfriendalert();
    void setSender(UserInfo sender);
    void setReceiverId(quint32 receiverId);
    void setAlertText();
    quint32 getSenderId();
    quint32 getReceiverId();

private slots:
    void on_agree_clicked();

    void on_refuse_clicked();

    void on_toolButton_clicked();
signals:
    void refreshFriendList();
private:
    Ui::addfriendalert *ui;
    UserInfo Sender;
    quint32 receiverId;
};

#endif // ADDFRIENDALERT_H
