#ifndef UPLOADER_H
#define UPLOADER_H

#include <QObject>

#include "DataModel/filemeta.h"

class Uploader : public QObject
{
    Q_OBJECT
public:
    explicit Uploader(QObject *parent = nullptr);

    static Uploader * GetInstance();

    void uploadImg(FileMeta filemeta, QString AbsolutePath);
    void uploadImg(FileMeta filemeta, QString AbsolutePath, quint32 receiver);
    void uploadFile(FileMeta filemeta, QString AbsolutePath);
    void uploadFile(FileMeta filemeta, QString absolutePath, quint32 receiver);

signals:

private:
    static Uploader * obj;
};

#endif // UPLOADER_H
