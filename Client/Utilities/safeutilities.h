#ifndef SAFEUTILITIES_H
#define SAFEUTILITIES_H

#include <QString>

//提供密码加密 端到端通信加密的实用工具

class SafeUtilities
{
public:
    SafeUtilities();
    static QString GetPasswordHash(QString password);
};

#endif // SAFEUTILITIES_H
