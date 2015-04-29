#include "ajoutpersonne.h"
#include "ui_ajoutpersonne.h"

AjoutPersonne::AjoutPersonne(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AjoutPersonne)
{
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
}

AjoutPersonne::~AjoutPersonne()
{
    delete ui;
}
