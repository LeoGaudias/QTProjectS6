#include "sondage_page2.h"
#include "ui_sondage_page2.h"
#include "sondage_page1.h"
#include "QDebug"
#include <QPushButton>
#include <QSqlQuery>
#include <QLineEdit>
#include "sondage_merci.h"
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

                    checks_id.push_back(query.value("IdY").toLongLong());
                    QObject::connect(check,SIGNAL(stateChanged(int)),this,SLOT(checked(int)));
                    row++;

                    vector<QObject*> temp;
                    temp.push_back(check);
                    objets.push_back(temp);
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
    // très broken
    if(state==2) // checked
    {
        QLineEdit* edit=new QLineEdit();
        objets.at(objets.size()-1).push_back(edit);
        ui->gridLayout->addWidget(edit,row-1,1,Qt::AlignHCenter);
    }
    else
    {
        delete objets.at(row-1).at(1);
        objets.at(row-1).pop_back();
    }
}

sondage_page2::~sondage_page2()
{
    delete ui;
}

void sondage_page2::on_buttonBox_rejected()
{

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
            vector<vector<QObject*> >::iterator it;
            for(it=objets.begin();it!=objets.end();it++)
            {
                qDebug() << ((QCheckBox*)(*it).at(0))->text();
                query.prepare("UPDATE Sondage SET Est_achete= :achete, frequence= :freq WHERE IdY= :idY");


                if(((QCheckBox*)(*it).at(0))->isChecked())
                {
                    qDebug()<< "checked";
                    query.bindValue(":achete",1);
                }
                else
                {
                    query.bindValue(":achete",0);
                }

                query.bindValue(":freq",0); // not working
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
