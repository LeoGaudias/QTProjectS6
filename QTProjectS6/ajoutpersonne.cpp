#include "ajoutpersonne.h"
#include "ui_ajoutpersonne.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sondage_page1.h"
#include "ui_sondage_page1.h"

#include "connexion.h"
#include "ui_connexion.h"

#include "iostream"

#include <QPushButton>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include "ui_mainwindow.h"



using namespace std;

AjoutPersonne::AjoutPersonne(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AjoutPersonne)
{
    p = (MainWindow*) parent;

    ui->setupUi(this);
    ui->date_nais->setDate(QDate::currentDate());
    ui->etat_civ->addItem("Célibataire");
    ui->etat_civ->addItem("Marié");
    ui->etat_civ->addItem("Divorcé");
    ui->etat_civ->addItem("Veuf");

    ui->revenu->addItem("0 à 10000€");
    ui->revenu->addItem("10000 à 20000€");
    ui->revenu->addItem("20000 à 30000€");
    ui->revenu->addItem("30000 à 40000€");
    ui->revenu->addItem("40001€ et plus");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Annuler");

}

AjoutPersonne::~AjoutPersonne()
{
    delete ui;
}

void AjoutPersonne::on_buttonBox_clicked(QAbstractButton *button)
{

}

void AjoutPersonne::on_buttonBox_accepted()
{
    QSqlQuery query;
    // gérer les exceptions
    if(p->db.open())
    {
        query.prepare("INSERT INTO Personne (DateNaiss,Sexe,Etat_civil"
                      ",Nb_personne,Nb_enfant,Nb_Animaux,Revenu)"
                        "VALUES (:date_nais, :sexe, :etat_civil,"
                        ":nb_pers, :nb_enfant,:nb_anim,:revenu)");

        QDate date = QDate::fromString(ui->date_nais->text(), "dd/MM/yyyy");
        query.bindValue(":date_nais",date);
        if(ui->radio_homme->isChecked() && !ui->radio_femme->isChecked())
        {
            query.bindValue(":sexe",0);
        }
        else if(ui->radio_femme->isChecked() && !ui->radio_homme->isChecked())
        {
            query.bindValue(":sexe",1);
        }
        else
        {
            qDebug() << "Radio button isn't checked";
            p->db.close();
            exit(0);
        }
        query.bindValue(":etat_civil",ui->etat_civ->currentText().toUtf8().constData());
        query.bindValue(":nb_pers",ui->spin_nb_pers->text().toInt());
        query.bindValue(":nb_enfant",ui->spin_nb_enfant->text().toInt());
        query.bindValue(":nb_anim",ui->spin_nb_anim->text().toInt());

        if(ui->revenu->currentIndex()==0)
        {
            query.bindValue(":revenu",0);
        }
        else if(ui->revenu->currentIndex()==1)
        {
            query.bindValue(":revenu",1);
        }
        else if(ui->revenu->currentIndex()==2)
        {
            query.bindValue(":revenu",2);
        }
        else if(ui->revenu->currentIndex()==3)
        {
            query.bindValue(":revenu",3);
        }
        else if(ui->revenu->currentIndex()==4)
        {
            query.bindValue(":revenu",4);
        }
        else
        {
            qDebug() << "no revenu select";
            p->db.close();
            exit(0);
        }

        if(query.exec())
        {
            p->connected=true;
            query.prepare("SELECT LAST_INSERT_ID()");
            if(query.exec())
            {
                query.next();
                p->ui->actionConnextion->setText("Se déconnecter");
                p->last_id=query.value(0).toLongLong();
                connection_ok();

            }
            else
            {
                qDebug() << "Something goes wrong in select" << p->db.lastError().text();
                p->db.close();
                exit(0);
            }

            //qDebug() <<"Query successfully executed " << p->connected << " ID: "<<p->last_id;
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
       qDebug() <<" not ok";
       exit(0);
    }
}

void AjoutPersonne::on_buttonBox_rejected()
{
    Connexion *co = new Connexion(p);
    p->setCentralWidget(co);

    int x = co->width();
    int y = co->height()+50;

    p->resize(x,y);
}

void AjoutPersonne::connection_ok()
{
    Sondage_page1 *sond_1 = new Sondage_page1(p);
    p->setCentralWidget(sond_1);

    int x = sond_1->width();
    int y = sond_1->height()+50;

    p->resize(x,y);
    p->setWindowTitle(p->windowTitle()+" id: "+QString::number(p->last_id));
}
