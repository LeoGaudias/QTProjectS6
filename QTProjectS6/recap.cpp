#include "recap.h"
#include "ui_recap.h"
#include "sondage_page1.h"
#include "connexion.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QLabel>


Recap::Recap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Recap)
{
    p = (MainWindow *) parent;
    ui->setupUi(this);

    QSqlQuery query;

    if(p->db.open())
    {
        query.prepare("SELECT * FROM Sondage s, Yaourt y WHERE s.IdY = y.IdY AND s.Id = :id");
        query.bindValue(":id",p->last_id);
        if(query.exec())
        {
            if(query.size() > 0)
            {
                qDebug() << "get data ok";
                QLabel *yaourt,*achete,*frequence;
                int row = 1;
                while(query.next())
                {
                    yaourt = new QLabel(query.value("Marque").toString()+" "+query.value("Nom").toString()+", au goût "+query.value("Gout").toString());
                    if(query.value("Est_achete").toString() == "NULL")
                    {
                        achete = new QLabel("");
                    }
                    else if(query.value("Est_achete").toBool())
                    {
                        achete = new QLabel("Oui");
                    }
                    else
                    {
                        achete = new QLabel("Non");
                    }
                    frequence = new QLabel(query.value("frequence").toString() + "/mois");
                    ui->gridLayout->addWidget(yaourt,row,1,Qt::AlignHCenter);
                    ui->gridLayout->addWidget(achete,row,2,Qt::AlignHCenter);
                    ui->gridLayout->addWidget(frequence,row,3,Qt::AlignHCenter);

                    row++;
                }
            }
            else
            {
                qDebug() << "no data";
            }

        }
        else
        {
            qDebug() << "Something goes wrong with the query" << p->db.lastError().text();
            p->db.close();
            exit(0);
        }
    }
    else
    {
        qDebug() << "Something goes wrong";
        p->db.close();
        exit(0);
    }

    ui->buttonBox->button(QDialogButtonBox::Close)->setText("Se déconnecter");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Continuer");
    ui->buttonBox->button(QDialogButtonBox::Reset)->setText("Reset les données");
}

Recap::~Recap()
{
    delete ui;
}

void Recap::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Close)) // se déconnecte
    {
        p->ui->actionConnextion->setText("S'inscrire");
        p->connected = false;
        Connexion* co = new Connexion(p);
        p->setCentralWidget(co);

        int x = co->width();
        int y = co->height()+50;

        p->resize(x,y);
    }
    else if(button == ui->buttonBox->button(QDialogButtonBox::Cancel)) //retourne au sondage
    {
        Sondage_page1* sond_1 = new Sondage_page1(p);
        p->setCentralWidget(sond_1);

        int x = sond_1->width();
        int y = sond_1->height()+50;

        p->resize(x,y);
    }
    else // wipe tte les données
    {
        QSqlQuery query;
        if(p->db.open())
        {
            query.prepare("DELETE FROM Sondage WHERE Id = :id");
            query.bindValue(":id",p->last_id);
            if(query.exec())
            {
                qDebug() << "Wipe data ok";
                QMessageBox::about(p,"Réinitialisation","Vos données ont bien été réinitialisées");
            }
            else
            {
                qDebug() << "Something goes wrong";
                p->db.close();
                exit(0);
            }
        }
        else
        {
            qDebug() << "Something goes wrong";
            p->db.close();
            exit(0);
        }

    }
}

void Recap::on_buttonBox_accepted()
{

}

void Recap::on_buttonBox_rejected()
{

}
