#include "ajoutpersonne.h"
#include "ui_ajoutpersonne.h"
#include "iostream"

#include <QPushButton>
#include <QtSql>
#include <QSqlDatabase>

#include "mainwindow.h"

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
        cout<<"ok"<< endl;
        query.prepare("INSERT INTO Personne (DateNaiss,Sexe,Etat_civil"
                      ",Nb_personne,Nb_enfant,Nb_Animaux,Revenu)"
                        "VALUES (:date_nais, :sexe, :etat_civil,"
                        ":nb_pers, :nb_enfant,:nb_anim,:revenu)");

        QDate date = QDate::fromString(ui->date_nais->text(), "dd/MM/yyyy");
        query.bindValue(":date_nais",date);
        if(ui->radio_homme->isChecked() && !ui->radio_femme->isChecked())
        {
            query.bindValue(":sexe",ui->radio_homme->text().toUtf8().constData());
        }
        else if(ui->radio_femme->isChecked() && !ui->radio_homme->isChecked())
        {
            query.bindValue(":sexe",ui->radio_femme->text().toUtf8().constData());
        }
        else
        {
            cout<< "Radio button isn't checked" << endl;
            p->db.close();
            exit(0);
        }
        query.bindValue(":etat_civil",ui->etat_civ->currentText().toUtf8().constData());
        query.bindValue(":nb_pers",ui->spin_nb_pers->text().toInt());
        query.bindValue(":nb_enfant",ui->spin_nb_enfant->text().toInt());
        query.bindValue(":nb_anim",ui->spin_nb_anim->text().toInt());
        query.bindValue(":revenu",ui->revenu->currentText().toUtf8().constData());
        if(query.exec())
        {
            cout<<"Query successfully executed"<<endl;
        }
        else
        {
            cout<<"Something goes wrong with the query"<<endl;
            p->db.close();
            exit(0);
        }
    }
    else
    {
       cout<<"!ok"<<endl;
       exit(0);
    }
}

void AjoutPersonne::on_buttonBox_rejected()
{
    std::cout<<"rejected"<<std::endl;
}
