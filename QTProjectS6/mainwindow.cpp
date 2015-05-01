#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "connexion.h"
#include "sondage_page1.h"
#include "ui_connexion.h"

#include <QDesktopWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    widget_base=centralWidget();
    last_id=0;
    connected=false;

    // gérer les exceptions
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("DB_Questionnaire");
    db.setUserName("root");
    db.setPassword("root");

    if(db.open())
    {
        qDebug() << "OPened";
        db.close();
    }
    else
    {
        qDebug() << "Erreur = " << db.lastError().text();
    }

    Connexion* co = new Connexion(this);
    setCentralWidget(co);

    int x = co->width();
    int y = co->height();

    resize(x,y);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuitter_triggered()
{
    close();
}

void MainWindow::on_actionD_connexion_triggered()
{

}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_actionConnextion_triggered()
{
    if(ui->actionConnextion->text()=="Se déconnecter")
    {
        ui->actionConnextion->setText("S'inscrire");
        connected=false;
        Connexion *co = new Connexion(this);
        setCentralWidget(co);

        int x = co->width();
        int y = co->height();

        resize(x,y);
    }
    else
    {
        AjoutPersonne* aj_p = new AjoutPersonne(this);
        setCentralWidget(aj_p);

        int x = aj_p->width();
        int y = aj_p->height() + 50;

        resize(x,y);
    }
}
