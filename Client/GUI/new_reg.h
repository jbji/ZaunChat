#ifndef NEW_REG_H
#define NEW_REG_H

#include <QWidget>
namespace Ui {
class new_reg;
}

class new_reg : public QWidget
{
    Q_OBJECT

public:
    explicit new_reg(QWidget *parent = nullptr);
    ~new_reg();
    void Setid(QString x);
    QString Getid();
    void showid();
    void showgroupid();
private slots:
    void on_toolButton_clicked();

private:
    Ui::new_reg *ui;
    static QString myid;
};

#endif // NEW_REG_H
