#-------------------------------------------------
#
# Project created by QtCreator 2017-07-28T14:37:14
#
#-------------------------------------------------

QT       += core gui
QT       += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fumetti
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        login.cpp \
    adminuser.cpp \
    comicbook.cpp \
    container.cpp \
    formaddfumetto.cpp \
    fumetto.cpp \
    fumettomodelviewtable.cpp \
    manga.cpp \
    normaluser.cpp \
    richiesta.cpp \
    richiestamodelview.cpp \
    user.cpp \
    usermodelview.cpp \
    admin.cpp \
    formadduser.cpp \
    formuserinfo.cpp

HEADERS  += login.h \
    adminuser.h \
    comicbook.h \
    container.h \
    formaddfumetto.h \
    fumetto.h \
    fumettomodelviewtable.h \
    manga.h \
    normaluser.h \
    richiesta.h \
    richiestamodelview.h \
    user.h \
    usermodelview.h \
    admin.h \
    formadduser.h \
    formuserinfo.h

FORMS    += login.ui \
    admin.ui \
    formadduser.ui \
    formaddfumetto.ui \
    formuserinfo.ui

RESOURCES += \
    xml.qrc

DISTFILES +=

OTHER_FILES +=
