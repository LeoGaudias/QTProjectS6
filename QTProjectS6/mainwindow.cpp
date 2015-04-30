#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ajoutpersonne.h"
#include "sondage_page1.h"
#include <QDesktopWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    last_id=0;
    connected=false;
    //servername="127.0.0.1";
    //dbname="DB_Questionnaire";
    //QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    // gérer les exceptions
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("DB_Questionnaire");
    db.setUserName("root");
    db.setPassword("root");

    //db.setConnectOptions();
    //QString dsn=QString("DRIVER=(SQL Native Client);SERVER=%1;DATABASE=%2;UID=root;PWD=root;").arg(servername).arg(dbname);
    //db.setDatabaseName(dsn);

    if(db.open())
    {
        qDebug() << "OPened";
        db.close();
    }
    else
    {
        qDebug() << "Erreur = " << db.lastError().text();
    }
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
    // s'inscire ou se déconnecter
}

void MainWindow::on_pushButton_clicked()
{
    Sondage_page1* sond_1 = new Sondage_page1();
    setCentralWidget(sond_1);

    int x = sond_1->width();
    int y = sond_1->height();

    this->resize(x,y);
}

void MainWindow::on_pushButton_2_clicked()
{
    AjoutPersonne* aj_p = new AjoutPersonne(this);
    setCentralWidget(aj_p);

    int x = aj_p->width();
    int y = aj_p->height();

    this->resize(x,y);
}
