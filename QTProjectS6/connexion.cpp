#include "connexion.h"
#include "ui_connexion.h"

#include "iostream"

#include "mainwindow.h"
#include "sondage_page1.h"

#include <QDebug>
#include <QSqlError>
#include <QtSql>

Connexion::Connexion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connexion)
{
    p = (MainWindow*) parent;
    ui->setupUi(this);
}

Connexion::~Connexion()
{
    delete ui;
}

void Connexion::on_pushButton_clicked()
{
    QSqlQuery query;
    // gérer les exceptions
    if(p->db.open())
    {
        query.prepare("SELECT Id FROM Personne WHERE Id = :id");
        query.bindValue(":id",ui->spinBox->value());

         if(query.exec())
         {
             if(query.size()>0)
             {
                 query.next();
                 p->connected=true;
                 p->last_id=query.value(0).toLongLong();

                 Sondage_page1* sond_1 = new Sondage_page1();
                 p->setCentralWidget(sond_1);

                 int x = sond_1->width();
                 int y = sond_1->height();

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
