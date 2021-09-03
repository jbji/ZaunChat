#ifndef ALTERIMG_H
#define ALTERIMG_H

#include <QWidget>
#include <QTcpSocket>
#include <QMouseEvent>

namespace Ui {
class alterImg;
}

class alterImg : public QWidget
{
    Q_OBJECT

public:
    explicit alterImg(QWidget *parent = nullptr);
    ~alterImg();

private slots:
    void on_pushButton_clicked();
    void recvMsg();

    void on_pushButton_2_clicked();

    void on_cancelButton_clicked();

protected:
    void mousePressEvent(QMouseEvent *event); //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event);  //鼠标移动事件

private:
    Ui::alterImg *ui;
    QTcpSocket *clientsocket;
    QPoint m_point;
};

#endif // ALTERIMG_H
