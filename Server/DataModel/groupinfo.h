#ifndef GROUPINFO_H
#define GROUPINFO_H
#include "DataModel/userinfo.h"
class GroupInfo:public UserInfo{
public:
    GroupInfo(quint32 id=0x0000,QString name="",QString pwd="",QString avatar_name="");
    GroupInfo(const UserInfo& Group);

};

#endif // GROUPINFO_H
