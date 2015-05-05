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

                    ui->gridLayout->addWidget(check,row,0,Qt::AlignHCenter);
                    map[check]=NULL;
                    map2[check]=NULL;

                    if(query.value("Est_achete").toInt()==1)
                    {
                        check->setChecked(true);
                        QSpinBox* edit=new QSpinBox();
                        edit->setValue(query.value("frequence").toInt());
                        edit->setMinimum(1);
                        QComboBox* combo=new QComboBox();

                        combo->addItem("Homme");
                        combo->addItem("Femme");
                        combo->addItem("Enfant");
                        combo->addItem("Homme & Enfant");
                        combo->addItem("Femme & Enfant");
                        combo->addItem("Tous");

                        combo->setCurrentIndex(query.value("Type_pers").toInt());

                        map[check]=edit;
                        map2[check]=combo;
                        ui->gridLayout->addWidget(edit,row,1,Qt::AlignLeft);
                        ui->gridLayout->addWidget(combo,row,2,Qt::AlignLeft);
                    }

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
            QSpinBox* edit=new QSpinBox();
            edit->setValue(1);
            edit->setMinimum(1);
            QComboBox* combo=new QComboBox();

            combo->addItem("Homme");
            combo->addItem("Femme");
            combo->addItem("Enfant");
            combo->addItem("Homme & Enfant");
            combo->addItem("Femme & Enfant");
            combo->addItem("Tous");

            map[check]=edit;
            map2[check]=combo;

            vector<QCheckBox*>::iterator it;
            for(it=objets.begin();it!=objets.end();it++)
            {
                if((*it)==check)
                {
                    ui->gridLayout->addWidget(edit,it-objets.begin(),1,Qt::AlignLeft);
                    ui->gridLayout->addWidget(combo,it-objets.begin(),2,Qt::AlignLeft);
                }
            }
        }
        else
        {
            QSpinBox* edit=map[check];
            QComboBox* combo=map2[check];
            edit->deleteLater();
            combo->deleteLater();
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
                query.prepare("UPDATE Sondage SET Est_achete= :achete, frequence= :freq, Type_Pers= :type_p WHERE IdY= :idY");

                if((*it)->isChecked())
                {
                    qDebug()<< "checked";
                    query.bindValue(":achete",1);

                    int freq=map[(*it)]->text().toInt();
                    query.bindValue(":freq",freq);

                    int sexe=0;
                    if(map2[(*it)]->currentText().toStdString().compare("Femme")==0)
                    {
                        sexe=1;
                    }
                    else if(map2[(*it)]->currentText().toStdString().compare("Enfant")==0)
                    {
                        sexe=2;
                    }
                    else if(map2[(*it)]->currentText().toStdString().compare("Homme & Enfant")==0)
                    {
                        sexe=3;
                    }
                    else if(map2[(*it)]->currentText().toStdString().compare("Femme & Enfant")==0)
                    {
                        sexe=4;
                    }
                    else if(map2[(*it)]->currentText().toStdString().compare("Tous")==0)
                    {
                        sexe=5;
                    }

                    query.bindValue(":type_p",sexe);
                    qDebug()<<"type"<<map2[(*it)]->currentText()<<" "<<sexe;
                }
                else
                {
                    query.bindValue(":achete",0);
                    query.bindValue(":freq",0);
                    query.bindValue(":type_p",0);
                }

                query.bindValue(":idY",checks_id.at(it-objets.begin()));

                if(query.exec())
                {
                    qDebug()<< "Worked";
                }
                else
                {
                    qDebug() << "Something goes wrong with the query update" << p->db.lastError().text();
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
        Recap *re = new Recap(p,this);
        p->setCentralWidget(re);

        int x = re->width();
        int y = re->height()+50;

        p->resize(x,y);
    }
}
