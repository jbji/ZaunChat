#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QMouseEvent>
#include "DataModel/datamodel.h"

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_closeButton_clicked();

    void on_minimizeButton_clicked();

    void on_loginButton_clicked();

    void on_registerButton_clicked();

    void on_pwd_textEdited(const QString &arg1);

    void on_pwd2_textEdited(const QString &arg1);

    void showRegisterSuccessful(UserInfo info);
    void showRegisterFailed();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
