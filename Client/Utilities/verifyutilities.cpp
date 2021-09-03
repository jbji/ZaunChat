#include "verifyutilities.h"
#include <QRegExp>
VerifyUtilities::VerifyUtilities()
{

}
//暂时没有写正则表达式验证是否有效的语句

bool VerifyUtilities::IsValidUsername(QString username){
    //不能含有、标点符号、或者是纯数字, 或者长度小于四位
    QRegExp rx_("[A-Za-z]");//判断是否含有字母
    QRegExp rx("^[A-Za-Z0-9]$");//判断是否有其他符号
    if(rx_.indexIn(username) == -1 || rx.indexIn(username) == -1 || username.length()<4) return false;
    return true;
}

bool VerifyUtilities::IsValidPassword(QString password){
    //长度要够 不能含有1234 必须含有大小写字母
    if(password.length()<6) return false;//长度至少为6位
    QRegExp rx("(1234)");
    if(rx.indexIn(password) == -1) return false;//含有1234
    QRegExp rx1("[A-Z]");
    QRegExp rx2("[a-z]");
    if(rx1.indexIn(password) == -1 || rx2.indexIn(password) == -1) return false;//含有大小写字母
    return true;
}
