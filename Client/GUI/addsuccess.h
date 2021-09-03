#ifndef ADDSUCCESS_H
#define ADDSUCCESS_H

#include <QWidget>
#include "DataModel/datamodel.h"

namespace Ui {
class addsuccess;
}

class addsuccess : public QWidget
{
    Q_OBJECT

public:
    explicit addsuccess(QWidget *parent = nullptr);
    ~addsuccess();
    void showflag(bool x);
    void settype(MsgType x);
    MsgType gettype();
signals:
    void refreshFriendList();
private slots:
    void on_ok_clicked();

private:
    Ui::addsuccess *ui;
    MsgType type;
};

#endif // ADDSUCCESS_H
