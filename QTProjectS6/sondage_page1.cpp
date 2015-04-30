#include "sondage_page1.h"
#include "ui_sondage_page1.h"
#include <QAbstractButton>
#include <QDebug>
#include <QSqlQuery>

Sondage_page1::Sondage_page1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sondage_page1)
{
    ui->setupUi(this);
    Sondage_page1::rajouter_valeur();

    QSqlQuery query;
    // gérer les exceptions
    /*if(p->db.open())
    {
        query.prepare("SELECT * FROM ");
    }*/
}

Sondage_page1::~Sondage_page1()
{
    delete ui;
}

void Sondage_page1::rajouter_valeur()
{

}

void Sondage_page1::on_buttonBox_clicked(QAbstractButton *button)
{

}

void Sondage_page1::on_buttonBox_rejected()
{
    qDebug()<<"rejected";
}

void Sondage_page1::on_buttonBox_accepted()
{
    qDebug()<<"accepted";
}
