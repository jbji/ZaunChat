#include "groupinfo.h"
#include <QtNetwork>
GroupInfo::GroupInfo(quint32 id,
            QString name,
            QString pwd,
            QString avatar_name
        ):UserInfo(id,name,pwd,avatar_name)
{
}

GroupInfo::GroupInfo(const UserInfo &Group){
    this->id = Group.getID(); this->name = Group.getName();
    this->pwd = Group.getPwd(); this->avatar_name = Group.getAvatarName();
}
