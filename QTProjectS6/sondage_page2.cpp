#include "sondage_page2.h"
#include "ui_sondage_page2.h"
#include "sondage_page1.h"
#include "recap.h"
#include "sondage_merci.h"

#include "QDebug"
#include <QPushButton>
#include <QSqlQuery>
#include <QtSql>

sondage_page2::sondage_page2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sondage_page2)
{
    p = (MainWindow*) parent;
    ui->setupUi(this);
    row = 0;
    ui->buttonBox->button(QDialogButtonBox::Abort)->setText("Annuler");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("<< Page précédente");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Page suivante >>");

    QSqlQuery query;
    // gérer les exceptions
    if(p->db.open())
    {
        query.prepare("SELECT * FROM Yaourt y,Sondage s WHERE y.idY=s.IdY");
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

                    if(query.value("Est_achete").toLongLong()==1)
                    {
                        check->setChecked(true);
                    }
                    ui->gridLayout->addWidget(check,row,0,Qt::AlignHCenter);
                    map[check]=NULL;

                    checks_id.push_back(query.value("IdY").toLongLong());
                    QObject::connect(check,SIGNAL(stateChanged(int)),this,SLOT(checked(int)));
                    row++;

                    objets.push_back(check);
                }
            }
            else
            {
                qDebug() << "Rien de selectionné sur la page précédente";
            }
        }
    }
    else
    {
       qDebug() <<" not ok";
       exit(0);
    }
}

void sondage_page2::checked(int state)
{
    QCheckBox *check = qobject_cast<QCheckBox *>(sender());
    if(check)
    {
        if(state==2) // checked
        {
            QLineEdit* edit=new QLineEdit();

            map[check]=edit;

            vector<QCheckBox*>::iterator it;
            for(it=objets.begin();it!=objets.end();it++)
            {
                if((*it)==check)
                {
                    ui->gridLayout->addWidget(edit,it-objets.begin(),1,Qt::AlignHCenter);
                }
            }
        }
        else
        {
            QLineEdit* edit=map[check];
            edit->deleteLater();
        }
    }
    else
    {
        qDebug()<<"Erreur";
    }

}

sondage_page2::~sondage_page2()
{
    delete ui;
}

void sondage_page2::on_buttonBox_rejected()
{
    Recap *re = new Recap(p);
    p->setCentralWidget(re);

    int x = re->width();
    int y = re->height()+50;

    p->resize(x,y);
}

void sondage_page2::on_buttonBox_accepted()
{

}

void sondage_page2::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button==ui->buttonBox->button(QDialogButtonBox::Cancel)) // précédent
    {
        Sondage_page1* sond_1 = new Sondage_page1(p);
        p->setCentralWidget(sond_1);

        int x = sond_1->width();
        int y = sond_1->height()+50;

        p->resize(x,y);
    }
    else if(button==ui->buttonBox->button(QDialogButtonBox::Ok)) // suivant
    {
        QSqlQuery query;
        // gérer les exceptions
        if(p->db.open())
        {
            vector<QCheckBox*>::iterator it;
            for(it=objets.begin();it!=objets.end();it++)
            {
                qDebug() << (*it)->text();
                query.prepare("UPDATE Sondage SET Est_achete= :achete, frequence= :freq WHERE IdY= :idY");


                if((*it)->isChecked())
                {
                    qDebug()<< "checked";
                    query.bindValue(":achete",1);

                    int freq=map[(*it)]->text().toInt();
                    query.bindValue(":freq",freq);
                }
                else
                {
                    query.bindValue(":achete",0);
                    query.bindValue(":freq",0);
                }

                query.bindValue(":idY",checks_id.at(it-objets.begin()));

                if(query.exec())
                {
                    qDebug()<< "Worked";
                }
                else
                {
                    qDebug() << "Something goes wrong with the query" << p->db.lastError().text();
                    p->db.close();
                    exit(0);
                }
            }
        }
        else
        {
           qDebug() <<" not ok";
           exit(0);
        }

        Sondage_merci* sond_m = new Sondage_merci(p);
        p->setCentralWidget(sond_m);

        int x = sond_m->width();
        int y = sond_m->height()+50;

        p->resize(x,y);
    }
    else // annuler
    {
        qDebug()<<"annuler";
    }
}
