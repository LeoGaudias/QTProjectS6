#-------------------------------------------------
#
# Project created by QtCreator 2015-03-18T14:27:51
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTProjectS6
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ajoutpersonne.cpp \
    sondage_page1.cpp \
    connexion.cpp \
    resultats.cpp \
    qcustomplot.cpp \
    sondage_page2.cpp \
    sondage_merci.cpp \
    recap.cpp \
    recap2.cpp

HEADERS  += mainwindow.h \
    ajoutpersonne.h \
    sondage_page1.h \
    connexion.h \
    resultats.h \
    qcustomplot.h \
    sondage_page2.h \
    sondage_merci.h \
    recap.h \
    recap2.h

FORMS    += mainwindow.ui \
    sondage_page1.ui \
    ajoutpersonne.ui \
    connexion.ui \
    resultats.ui \
    sondage_page2.ui \
    sondage_merci.ui \
    recap.ui \
    recap2.ui
