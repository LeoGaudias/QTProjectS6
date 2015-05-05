#include "recap2.h"
#include "ui_recap2.h"
#include "sondage_page1.h"


#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QPushButton>

Recap2::Recap2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Recap2)
{
    p = (MainWindow*) parent;
    row = 1;
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
                QLabel *yaourt,*achete,*frequence,*conso;
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
                    frequence = new QLabel(query.value("frequence").toString() + "/6 mois");
                    switch (query.value("Type_Pers").toInt()) {
                        case 0:
                            conso = new QLabel("Homme");
                            break;
                        case 1:
                            conso = new QLabel("Femme");
                            break;
                        case 2:
                            conso = new QLabel("Enfant");
                            break;
                        case 3:
                            conso = new QLabel("Homme & Enfant");
                            break;
                        case 4:
                            conso = new QLabel("Femme & Enfant");
                            break;
                        case 5:
                            conso = new QLabel("Tous");
                            break;
                        default:
                            break;
                    }
                    ui->gridLayout->addWidget(yaourt,row,1,Qt::AlignHCenter);
                    ui->gridLayout->addWidget(achete,row,2,Qt::AlignHCenter);
                    ui->gridLayout->addWidget(frequence,row,3,Qt::AlignHCenter);
                    ui->gridLayout->addWidget(conso,row,4,Qt::AlignHCenter);

                    objets.push_back(yaourt);
                    objets.push_back(achete);
                    objets.push_back(frequence);
                    objets.push_back(conso);

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

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Quitter");
    ui->buttonBox->button(QDialogButtonBox::Retry)->setText("Recommencer");

}

Recap2::~Recap2()
{
    delete ui;
}

void Recap2::on_buttonBox_accepted()
{

}

void Recap2::on_buttonBox_rejected()
{

}

void Recap2::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok))
    {
        p->myfile.close();
        p->db.close();
        exit(0);
    }
    else
    {
        QSqlQuery query;
        if(p->db.open())
        {
            query.prepare("DELETE FROM Sondage WHERE Id = :id");
            query.bindValue(":id",p->last_id);
            if(query.exec())
            {
                qDebug() << "Wipe data ok";

                vector<QObject*>::iterator it;
                for(it=objets.begin();it!=objets.end();it++)
                {
                    delete (*it);
                }

                Sondage_page1* sond_1 = new Sondage_page1(p);
                p->setCentralWidget(sond_1);

                int x = sond_1->width();
                int y = sond_1->height() + 50;

                p->resize(x,y);
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
