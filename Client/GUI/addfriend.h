#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>
#include "DataModel/datamodel.h"
#include "GUI/addsuccess.h"
namespace Ui {
class addfriend;
}

class addfriend : public QWidget
{
    Q_OBJECT

public:
    explicit addfriend(QWidget *parent = nullptr);
    ~addfriend();
    static addsuccess * GetAddSuccess();
public slots:
    void addFriendSuccess();
    void showAddFriendFailed(MsgType type);
private slots:
    void on_toolButton_clicked();
    void on_addFriendButton_clicked();
private:
    Ui::addfriend *ui;
    static addsuccess * Addsuccess;
};

#endif // ADDFRIEND_H
