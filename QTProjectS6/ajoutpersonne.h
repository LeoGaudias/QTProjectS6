#ifndef AJOUTPERSONNE_H
#define AJOUTPERSONNE_H

#include <QWidget>
#include <QAbstractButton>
#include <QSqlDatabase>
#include "mainwindow.h"

namespace Ui {
class AjoutPersonne;

}

class MainWindow;

class AjoutPersonne : public QWidget
{
    Q_OBJECT

public:
    explicit AjoutPersonne(QWidget *parent = 0);
    ~AjoutPersonne();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void connection_ok();

private:
    Ui::AjoutPersonne *ui;
    MainWindow* p;
};

#endif // AJOUTPERSONNE_H
