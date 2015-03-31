#include "ajoutpersonne.h"
#include "ui_ajoutpersonne.h"

AjoutPersonne::AjoutPersonne(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AjoutPersonne)
{
    ui->setupUi(this);
}

AjoutPersonne::~AjoutPersonne()
{
    delete ui;
}
