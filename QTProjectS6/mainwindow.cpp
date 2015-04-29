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
    servername="localhost";
    dbname="DB_Questionnaire";
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setConnectOptions();
    QString dsn=QString("DRIVER=(SQL Native Client);SERVER=%1;DATABASE=%2;UID=root;PWD=root;").arg(servername).arg(dbname);
    db.setDatabaseName(dsn);

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
    AjoutPersonne* aj_p=new AjoutPersonne();
    aj_p->show();

    Sondage_page1* sond_1=new Sondage_page1();
    sond_1->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    setCentralWidget(new AjoutPersonne(this));
    QDesktopWidget dw;
    int x=dw.width()*0.7;
    int y=dw.height()*0.7;
    this->setFixedSize(x,y);
}
