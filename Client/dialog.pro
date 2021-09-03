QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
RC_ICONS = logo.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GUI/addfriend.cpp \
    GUI/addgroup.cpp \
    GUI/addsuccess.cpp \
    GUI/addfriendalert.cpp \
    GUI/alarmwidget.cpp \
    GUI/alterimg.cpp \
    GUI/altername.cpp \
    GUI/alterpwd.cpp \
    GUI/choosefile.cpp \
    GUI/chooseimage.cpp \
    GUI/creategroup.cpp \
    GUI/itemwidget.cpp \
    GUI/login.cpp \
    GUI/main.cpp \
    GUI/mainwindow.cpp \
    GUI/new_reg.cpp \
    GUI/register.cpp \
    Controller/clientcontroller.cpp \
    Controller/clientcontroller_chat.cpp \
    Controller/clientcontroller_file.cpp \
    Controller/clientcontroller_friend.cpp \
    Controller/clientcontroller_group.cpp \
    Controller/clientcontroller_modify.cpp \
    Controller/clientcontroller_reg_login.cpp \
    DataModel/Msg/msg.cpp \
    DataModel/chatmessage.cpp \
    DataModel/filemeta.cpp \
    DataModel/filepackage.cpp \
    DataModel/group_chat_message.cpp \
    DataModel/groupinfo.cpp \
    DataModel/userinfo.cpp \
    Network/Handlers/chat_msg_handler.cpp \
    Network/Handlers/friend_request_handler.cpp \
    Network/Handlers/friend_request_result_handler.cpp \
    Network/Handlers/friendlist_handler.cpp \
    Network/Handlers/group_add_result_handler.cpp \
    Network/Handlers/group_msg_handler.cpp \
    Network/Handlers/grouplist_handler.cpp \
    Network/Handlers/login_handler.cpp \
    Network/Handlers/logout_handler.cpp \
    Network/Handlers/modify_username_result_handler.cpp \
    Network/Handlers/register_group_handler.cpp \
    Network/Handlers/register_handler.cpp \
    Network/Handlers/userinfo_handler.cpp \
    Network/ResAssist/downloader.cpp \
    Network/ResAssist/localcache.cpp \
    Network/ResAssist/ressocket.cpp \
    Network/ResAssist/uploader.cpp \
    Network/handlerreg.cpp \
    Network/tcpclientsocket.cpp \
    Utilities/log.cpp \
    Utilities/qbytearraylistutility.cpp \
    Utilities/safeutilities.cpp \
    Utilities/verifyutilities.cpp \
    Developer/new_windows.cpp\
    Developer/widget.cpp\
    user.cpp

HEADERS += \
    GUI/addfriend.h \
    GUI/addgroup.h \
    GUI/addsuccess.h \
    GUI/addfriendalert.h \
    GUI/alarmwidget.h \
    GUI/alterimg.h \
    GUI/altername.h \
    GUI/alterpwd.h \
    GUI/choosefile.h \
    GUI/chooseimage.h \
    GUI/creategroup.h \
    GUI/itemwidget.h \
    GUI/login.h \
    GUI/mainwindow.h \
    GUI/new_reg.h \
    GUI/register.h \
    Controller/clientcontroller.h \
    DataModel/Msg/msg.h \
    DataModel/Msg/msgtype.h \
    DataModel/chatmessage.h \
    DataModel/datamodel.h \
    DataModel/filemeta.h \
    DataModel/filepackage.h \
    DataModel/group_chat_message.h \
    DataModel/groupinfo.h \
    DataModel/userinfo.h \
    Network/Handlers/chat_msg_handler.h \
    Network/Handlers/friend_request_handler.h \
    Network/Handlers/friend_request_result_handler.h \
    Network/Handlers/friendlist_handler.h \
    Network/Handlers/group_add_request_result.h \
    Network/Handlers/group_msg_handler.h \
    Network/Handlers/grouplist_handler.h \
    Network/Handlers/modify_username_result_handler.h \
    Network/Handlers/register_group_handler.h \
    Network/Handlers/userinfo_handler.h \
    Network/ResAssist/downloader.h \
    Network/ResAssist/localcache.h \
    Network/ResAssist/res.h \
    Network/ResAssist/ressocket.h \
    Network/ResAssist/uploader.h \
    Network/handlers.h \
    Network/Handlers/login_handler.h \
    Network/Handlers/logout_handler.h \
    Network/Handlers/msghandler.h \
    Network/Handlers/register_handler.h \
    Network/handlerreg.h \
    Network/tcpclientsocket.h \
    Utilities/log.h \
    Utilities/qbytearraylistutility.h \
    Utilities/safeutilities.h \
    Utilities/standarddatetimeutilities.h \
    Utilities/utilities.h \
    Utilities/verifyutilities.h \
    Developer/new_windows.h\
    Developer/widget.h\
    user.h

FORMS += \
    GUI/addfriend.ui \
    GUI/addgroup.ui \
    GUI/addsuccess.ui \
    GUI/alarmwidget.ui \
    GUI/alterimg.ui \
    GUI/altername.ui \
    GUI/alterpwd.ui \
    GUI/choosefile.ui \
    GUI/chooseimage.ui \
    GUI/creategroup.ui \
    GUI/itemwidget.ui \
    GUI/login.ui \
    GUI/mainwindow.ui \
    GUI/new_reg.ui \
    GUI/register.ui \
    GUI/addfriendalert.ui\
    Developer/new_windows.ui\
    Developer/widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    GUI/resourse.qrc

DISTFILES += \
    logo.ico \
    logo.png
