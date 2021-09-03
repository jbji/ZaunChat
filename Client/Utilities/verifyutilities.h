#ifndef VERIFYUTILITIES_H
#define VERIFYUTILITIES_H

#include <QObject>

//定义输入格式的验证工具

class VerifyUtilities
{
public:
    VerifyUtilities();

    static bool IsValidUsername(QString username);
    static bool IsValidPassword(QString password);

};

#endif // VERIFYUTILITIES_H
