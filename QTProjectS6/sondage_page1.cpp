#include "sondage_page1.h"
#include "ui_sondage_page1.h"
#include <QAbstractButton>
#include <QDebug>
#include <QSqlQuery>
#include <QCheckBox>

Sondage_page1::Sondage_page1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sondage_page1)
{
    p = (MainWindow*) parent;
    ui->setupUi(this);
    Sondage_page1::rajouter_valeur();

    QSqlQuery query;
    // gérer les exceptions
    if(p->db.open())
    {
        query.prepare("SELECT * FROM Yaourt");
        if(query.exec())
        {
            if(query.size()>0)
            {
                while(query.next())
                {
                    QCheckBox* check;
                    if(query.value("Type").toString()!=NULL)
                    {
                        check=new QCheckBox(query.value("Marque").toString()+" "+query.value("Nom").toString()+" "+query.value("Type").toString()+", au goût"+query.value("Gout").toString());

                    }
                    else
                    {
                        check=new QCheckBox(query.value("Marque").toString()+" "+query.value("Nom").toString()+", au goût "+query.value("Gout").toString());
                    }
                    ui->verticalLayout->addWidget(check);
                }
            }
            else
            {
               qDebug() << "Pas de yaourt dans la db";
            }
        }
    }
    else
    {
       qDebug() <<" not ok";
       exit(0);
    }
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

void Sondage_page1::on_pushButton_2_clicked()
{

}

void Sondage_page1::on_plus_clicked()
{
    qDebug()<<"Autres";
    QHBoxLayout* layout=new QHBoxLayout();
    QLineEdit* autre=new QLineEdit();
    QPushButton* del=new QPushButton("X");
    ui->layout_autres->addLayout(layout);
    layout->addWidget(autre);
    layout->addWidget(del);
}
