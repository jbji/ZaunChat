#ifndef ADDGROUP_H
#define ADDGROUP_H

#include <QWidget>
#include "DataModel/datamodel.h"
#include "GUI/addsuccess.h"
namespace Ui {
class addgroup;
}

class addgroup : public QWidget
{
    Q_OBJECT

public:
    explicit addgroup(QWidget *parent = nullptr);
    ~addgroup();
    static addsuccess * GetAddSuccess();
public slots:
    void showAddGroupSuccess();
    void showAddGroupFailed(MsgType type);
private slots:
    void on_closeButton_clicked();
    void on_addgroupButton_clicked();
private:
    Ui::addgroup *ui;
    static addsuccess * Addsuccess;
};

#endif // ADDFRIEND_H
