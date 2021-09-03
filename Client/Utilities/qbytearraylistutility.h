#ifndef QBYTEARRAYLISTUTILITY_H
#define QBYTEARRAYLISTUTILITY_H

#include <QObject>

class QByteArrayListUtility
{
public:
    QByteArrayListUtility();

    static QList<QByteArray> fromQByteArray(QByteArray block);
    static QByteArray toQByteArray(QList<QByteArray>);
};

#endif // QBYTEARRAYLISTUTILITY_H
