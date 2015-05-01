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
    qcustomplot/qcustomplot.cpp \
    sondage_page2.cpp

HEADERS  += mainwindow.h \
    ajoutpersonne.h \
    sondage_page1.h \
    connexion.h \
    resultats.h \
    qcustomplot/qcustomplot.h \
    sondage_page2.h

FORMS    += mainwindow.ui \
    sondage_page1.ui \
    ajoutpersonne.ui \
    connexion.ui \
    resultats.ui \
    sondage_page2.ui
