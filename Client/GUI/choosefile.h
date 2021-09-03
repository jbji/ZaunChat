#ifndef CHOOSEFILE_H
#define CHOOSEFILE_H

#include <QWidget>
#include <QTcpSocket>
#include <QMouseEvent>
#include "user.h"
namespace Ui {
class chooseFile;
}

class chooseFile : public QWidget
{
    Q_OBJECT

public:
    explicit chooseFile(QWidget *parent = nullptr);
    ~chooseFile();
    void setFriendInfo(User * Friend);
private slots:
    void on_pushButton_clicked();
    void recvMsg();

    void on_pushButton_2_clicked();

    void on_cancelButton_clicked();

protected:
    void mousePressEvent(QMouseEvent *event); //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event);  //鼠标移动事件

private:
    Ui::chooseFile *ui;
    QTcpSocket *clientsocket;
    QPoint m_point;
    User* friendInfo;
};

#endif // CHOOSEFILE_H
