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
    // s'inscire ou se déconnecter
}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    // gérer les exceptions
    if(db.open())
    {
        query.prepare("SELECT Id FROM Personne WHERE Id = :id");
        //query.bindValue(":id",ui->spinBox->value());

         if(query.exec())
         {
             if(query.size()>0)
             {
                 query.next();
                 connected=true;
                 last_id=query.value(0).toLongLong();
                 ui->actionConnextion->setText("Se déconnecter");

                 Sondage_page1* sond_1 = new Sondage_page1();
                 setCentralWidget(sond_1);

                 int x = sond_1->width();
                 int y = sond_1->height();

                 this->resize(x,y);
                 setWindowTitle(windowTitle()+" id: "+QString::number(last_id));
             }
             else
             {
                qDebug() << "Mauvais id";
             }
         }
         else
         {
             qDebug() << "Something goes wrong in select" << db.lastError().text();
             db.close();
             exit(0);
         }
    }
    else
    {
       qDebug() <<" not ok";
       exit(0);
    }
}

void MainWindow::on_pushButton_2_clicked()
{

}
