#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMouseEvent>
#include "DataModel/datamodel.h"
#include "mainwindow.h"
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_closeButton_clicked();

    void on_minimizeButton_clicked();

    void on_registerButton_clicked();

    void on_loginButton_clicked();


    void on_password_textEdited(const QString &arg1);
    void showLoginSuccessful(UserInfo info);
    void showLoginFailed();
    static MainWindow * GetMainWindowInstance();
private:
    Ui::login* ui;
    QPoint m_point;
    static MainWindow * mw;
protected:
    void mousePressEvent(QMouseEvent *event); //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event);  //鼠标移动事件
};
#endif // LOGIN_H
