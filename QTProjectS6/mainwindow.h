#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "ajoutpersonne.h"

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
    bool connected;

private slots:
    void on_actionQuitter_triggered();

    void on_actionD_connexion_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

    QString servername;
    QString dbname;
};

#endif // MAINWINDOW_H
