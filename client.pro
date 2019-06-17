#-------------------------------------------------
#
# Project created by QtCreator 2019-05-21T09:19:10
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += multimedia
QT       += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    protocol.cpp \
    clientsocket.cpp \
    chatroom.cpp \
    client.cpp \
    clientsocketmanager.cpp \
    registdialog.cpp \
    topupdialog.cpp \
    camerawidget.cpp \
    dialogtopup10.cpp \
    videosurface.cpp

HEADERS += \
        widget.h \
    protocol.h \
    clientsocket.h \
    chatroom.h \
    client.h \
    clientsocketmanager.h \
    registdialog.h \
    topupdialog.h \
    camerawidget.h \
    dialogtopup10.h \
    videosurface.h

FORMS += \
        widget.ui \
    chatroom.ui \
    registdialog.ui \
    topupdialog.ui \
    camerawidget.ui \
    dialogtopup10.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

SUBDIRS += \
    ../../JQZopfli-master/JQZopfli.pro

DISTFILES += \
    image/9b20c1d642018a3d7a49815b6b7180f40f7c7cfe1107a-JScM2o_fw658.png \
    image/9b20c1d642018a3d7a49815b6b7180f40f7c7cfe1107a-JScM2o_fw658.png \
    image/59310a10e1783.png
RC_ICONS = favicon.ico
