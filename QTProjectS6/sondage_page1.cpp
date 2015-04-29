#include "sondage_page1.h"
#include "ui_sondage_page1.h"

Sondage_page1::Sondage_page1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sondage_page1)
{
    ui->setupUi(this);
    Sondage_page1::rajouter_valeur();
}

Sondage_page1::~Sondage_page1()
{
    delete ui;
}

void Sondage_page1::rajouter_valeur()
{

}
