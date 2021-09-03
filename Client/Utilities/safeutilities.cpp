#include "safeutilities.h"
#include <QCryptographicHash>
SafeUtilities::SafeUtilities()
{

}

QString SafeUtilities::GetPasswordHash(QString password){
    QString md5Str = QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Md5).toHex();
    return md5Str;
}
