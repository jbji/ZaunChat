#ifndef CHOOSEIMG_H
#define CHOOSEIMG_H

#include <QWidget>
#include <QTcpSocket>
#include <QMouseEvent>

namespace Ui {
class chooseImg;
}

class chooseImg : public QWidget
{
    Q_OBJECT

public:
    explicit chooseImg(QWidget *parent = nullptr);
    ~chooseImg();

private slots:
    void on_pushButton_clicked();
    void recvMsg();

    void on_pushButton_2_clicked();

    void on_cancelButton_clicked();

protected:
    void mousePressEvent(QMouseEvent *event); //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event);  //鼠标移动事件

private:
    Ui::chooseImg *ui;
    QTcpSocket *clientsocket;
    QPoint m_point;
};

#endif // CHOOSEIMG_H
