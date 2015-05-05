#include "connexion.h"
#include "ui_connexion.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sondage_page1.h"
#include "ui_sondage_page1.h"

#include "resultats.h"
#include "statistique.h"

#include "iostream"
#include <fstream>

#include <QDebug>
#include <QSqlError>
#include <QtSql>
#include <string>

using namespace std;

Connexion::Connexion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connexion)
{
    p = (MainWindow*) parent;
    ui->setupUi(this);

    p->myfile.close();
    p->myfile.open("../last");
    string line;
    getline(p->myfile,line);
    qDebug()<< QString(line.c_str());
    ui->spinBox->setValue(atoi(line.c_str()));
}

Connexion::~Connexion()
{
    delete ui;
}

void Connexion::on_pushButton_clicked()
{

}

void Connexion::on_inscrire_clicked()
{
    AjoutPersonne* aj_p = new AjoutPersonne(p);
    p->setCentralWidget(aj_p);

    int x = aj_p->width();
    int y = aj_p->height() + 50;

    p->resize(x,y);
}

void Connexion::on_connecter_clicked()
{
    QSqlQuery query;
    // gérer les exceptions
    if(p->db.open())
    {
        query.prepare("SELECT Id,Sexe FROM Personne WHERE Id = :id");
        query.bindValue(":id",ui->spinBox->value());

         if(query.exec())
         {
             if(query.size()>0)
             {
                 query.next();
                 p->connected=true;
                 p->ui->actionConnextion->setText("Se déconnecter");
                 p->last_id=query.value("Id").toLongLong();
                 p->sexe=query.value("Sexe").toInt();

                 p->myfile.close();
                 p->myfile.open("../last", std::fstream::out | std::fstream::trunc);
                 p->myfile.close();
                 p->myfile.open("../last");
                 p->myfile << p->last_id;

                 p->setWindowTitle(p->windowTitle()+" id: "+QString::number(p->last_id));

                 Sondage_page1* sond_1 = new Sondage_page1(p);
                 p->setCentralWidget(sond_1);

                 int x = sond_1->width();
                 int y = sond_1->height()+50;

                 p->resize(x,y);
             }
             else
             {
                qDebug() << "Mauvais id";
             }
         }
         else
         {
             qDebug() << "Something goes wrong in select" << p->db.lastError().text();
             p->db.close();
             exit(0);
         }
    }
    else
    {
       qDebug() <<" not ok";
       exit(0);
    }
}

void Connexion::on_pushButton_2_clicked()
{
    AjoutPersonne* aj_p = new AjoutPersonne(p);
    p->setCentralWidget(aj_p);

    int x = aj_p->width();
    int y = aj_p->height() + 50;

    p->resize(x,y);
}

void Connexion::on_Result_clicked()
{
    Resultats* result = new Resultats(p);
    p->setCentralWidget(result);

    int x = result->width();
    int y = result->height()+50;

    p->resize(x,y);
}

void Connexion::on_stat_clicked()
{
    Statistique* stat = new Statistique(p);
    p->setCentralWidget(stat);

    int x = stat->width();
    int y = stat->height()+50;

    p->resize(x,y);
}
