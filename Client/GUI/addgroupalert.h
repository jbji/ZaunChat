#ifndef ADDGROUPALERT_H
#define ADDGROUPALERT_H

#include <QWidget>

namespace Ui {
class addgroupalert;
}

class addgroupalert : public QWidget
{
    Q_OBJECT

public:
    explicit addgroupalert(QWidget *parent = nullptr);
    ~addgroupalert();

private:
    Ui::addgroupalert *ui;
};

#endif // ADDGROUPALERT_H
