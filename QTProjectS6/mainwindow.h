#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "ajoutpersonne.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
    QSqlDatabase db;
    int last_id;
    int sexe;
    bool connected;
    QWidget *widget_base;
    fstream myfile;

private slots:
    void on_actionQuitter_triggered();

    void on_actionD_connexion_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionConnextion_triggered();

private:

    QString servername;
    QString dbname;
};

#endif // MAINWINDOW_H
