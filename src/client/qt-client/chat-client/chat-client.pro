#-------------------------------------------------
#
# Project created by QtCreator 2015-11-14T20:30:55
#
#-------------------------------------------------

QT       += core gui widgets network

CONFIG   += C++11

TARGET = Simple-Chat
TEMPLATE = app

SOURCES +=  main.cpp\
            main_window.cpp \
            login_dialog.cpp \
            remote_server.cpp \
            worker.cpp

HEADERS  += main_window.hpp \
            login_dialog.hpp \
            remote_server.hpp \
    worker.hpp

FORMS    += main_window.ui \
            login_dialog.ui
