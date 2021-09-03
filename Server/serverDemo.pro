QT       += core gui
QT       += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataBase/datadb.cpp \
    DataModel/Msg/msg.cpp \
    DataModel/chatmessage.cpp \
    DataModel/filemeta.cpp \
    DataModel/filepackage.cpp \
    DataModel/groupinfo.cpp \
    DataModel/userinfo.cpp \
    Network/Handlers/FriendshipHandler.cpp \
    Network/Handlers/LoginHandler.cpp \
    Network/Handlers/LogoutHandler.cpp \
    Network/Handlers/RegisterHandler.cpp \
    Network/Handlers/addGroupHandler.cpp \
    Network/Handlers/addfriendresulthandler.cpp \
    Network/Handlers/chatmsghandler.cpp \
    Network/Handlers/group_msg_handler.cpp \
    Network/Handlers/modifyUsernameHandler.cpp \
    Network/Handlers/modifyavatarhandler.cpp \
    Network/Handlers/offlinemsghandler.cpp \
    Network/Handlers/registerGroupHandler.cpp \
    Network/Handlers/requestAllGroupListHandler.cpp \
    Network/Handlers/requestUserInfoHandler.cpp \
    Network/Handlers/requestallfriendlisthandler.cpp \
    Network/ResAssist/localcache.cpp \
    Network/ResAssist/ressocket.cpp \
    Network/Server/resserver.cpp \
    Network/Server/server.cpp \
    Network/Server/tcpserver.cpp \
    Network/serverhandlerreg.cpp \
    Network/tcpclientsocket.cpp \
    Utilities/log.cpp \
    Utilities/qbytearraylistutility.cpp \
    main.cpp \
    servercontroller.cpp \
    widget.cpp

HEADERS += \
    DataBase/datadb.h \
    DataModel/Msg/msg.h \
    DataModel/Msg/msgtype.h \
    DataModel/chatmessage.h \
    DataModel/datamodel.h \
    DataModel/filemeta.h \
    DataModel/filepackage.h \
    DataModel/groupinfo.h \
    DataModel/userinfo.h \
    Network/Handlers/FriendshipHandler.h \
    Network/Handlers/LoginHandler.h \
    Network/Handlers/LogoutHandler.h \
    Network/Handlers/RegisterHandler.h \
    Network/Handlers/addGroupHandler.h \
    Network/Handlers/addfriendresulthandler.h \
    Network/Handlers/chatmsghandler.h \
    Network/Handlers/group_msg_handler.h \
    Network/Handlers/modifyUsernameHandler.h \
    Network/Handlers/modifyavatarhandler.h \
    Network/Handlers/msghandler.h \
    Network/Handlers/offlinemsghandler.h \
    Network/Handlers/registerGroupHandler.h \
    Network/Handlers/requestAllGroupListHandler.h \
    Network/Handlers/requestUserInfoHandler.h \
    Network/Handlers/requestallfriendlisthandler.h \
    Network/ResAssist/localcache.h \
    Network/ResAssist/res.h \
    Network/ResAssist/ressocket.h \
    Network/Server/resserver.h \
    Network/Server/server.h \
    Network/Server/tcpserver.h \
    Network/serverhandlerreg.h \
    Network/tcpclientsocket.h \
    Utilities/log.h \
    Utilities/qbytearraylistutility.h \
    Utilities/standarddatetimeutilities.h \
    Utilities/utilities.h \
    servercontroller.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
