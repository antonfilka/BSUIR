#-------------------------------------------------
#
# Project created by QtCreator 2011-09-15T14:39:50
#
#-------------------------------------------------

QT       += core gui
QT       += sql widgets
QT       += gui
TARGET = Diary
TEMPLATE = app


SOURCES += main.cpp\
        diary.cpp \
    login.cpp \
    register.cpp \
    dbcon.cpp \
    confirm.cpp \
    calculator.cpp \
    button.cpp \
    contacts.cpp \
    tetrixwindow.cpp \
    tetrixpiece.cpp \
    tetrixboard.cpp

HEADERS  += diary.h \
    login.h \
    register.h \
    dbcon.h \
    confirm.h \
    calculator.h \
    button.h \
    contacts.h \
    tetrixwindow.h \
    tetrixpiece.h \
    tetrixboard.h

FORMS    += diary.ui \
    login.ui \
    register.ui \
    confirm.ui \
    contacts.ui
RESOURCES += \
    Images.qrc
