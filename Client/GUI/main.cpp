#include "login.h"

#include <QApplication>
login* loginw = NULL;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont f("微软雅黑",10);
    a.setFont(f);
    login w;
    w.show();
    loginw = &w;

    return a.exec();
}
