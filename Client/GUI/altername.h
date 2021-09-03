#ifndef ALTERNAME_H
#define ALTERNAME_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class alterName;
}

class alterName : public QWidget
{
    Q_OBJECT

public:
    explicit alterName(QWidget *parent = nullptr);
    ~alterName();
    //bool flag;
    //QString newname;

private slots:
    void on_cancelButton_clicked();

    void on_submitButton_clicked();

protected:
    void mousePressEvent(QMouseEvent *event); //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event);  //鼠标移动事件

private:
    Ui::alterName *ui;
        QPoint m_point;
};

#endif // ALTERNAME_H
