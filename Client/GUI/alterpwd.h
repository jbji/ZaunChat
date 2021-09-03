#ifndef ALTERPWD_H
#define ALTERPWD_H

#include <QWidget>

namespace Ui {
class alterPwd;
}

class alterPwd : public QWidget
{
    Q_OBJECT

public:
    explicit alterPwd(QWidget *parent = nullptr);
    ~alterPwd();

private slots:
    void on_cancelButton_clicked();

    void on_submitButton_clicked();


private:
    Ui::alterPwd *ui;
};

#endif // ALTERPWD_H
