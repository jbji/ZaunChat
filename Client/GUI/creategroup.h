#ifndef CREATEGROUP_H
#define CREATEGROUP_H

#include <QWidget>
#include "DataModel/datamodel.h"
#include "new_reg.h"
namespace Ui {
class createGroup;
}

class createGroup : public QWidget
{
    Q_OBJECT

public:
    explicit createGroup(QWidget *parent = nullptr);
    ~createGroup();
    static new_reg * GetNewGroupRegister();

private slots:
    void on_createButton_clicked();
    void showRegisterGroupSuccessful(GroupInfo info);
    void on_closeButton_clicked();

private:
    Ui::createGroup *ui;

    static new_reg * newGroupRegister;

};

#endif // CREATEGROUP_H
