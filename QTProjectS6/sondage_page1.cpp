#include "sondage_page1.h"
#include "ui_sondage_page1.h"
#include <QAbstractButton>
#include <QDebug>
#include <QSqlQuery>
#include <QLineEdit>
#include "sondage_page2.h"
#include <QtSql>

Sondage_page1::Sondage_page1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sondage_page1)
{
    p = (MainWindow*) parent;
    inserted=false;
    row = 2;
    ui->setupUi(this);

    ui->Marque->hide();
    ui->autre_mq->hide();
    ui->Nom->hide();
    ui->autre_nm->hide();
    ui->Type->hide();
    ui->autre_type->hide();
    ui->Gout->hide();
    ui->autre_gout->hide();
    row--;

    ui->buttonBox->button(QDialogButtonBox::Abort)->setText("Annuler");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Page suivante >>");

    Sondage_page1::rajouter_valeur();
    checks.clear();

    QSqlQuery query;
    // gérer les exceptions
    if(p->db.open())
    {
        query.prepare("SELECT *, CASE WHEN EXISTS (SELECT * FROM Sondage s WHERE y.IdY=s.IdY) THEN 1 ELSE 0 END AS 'Present' FROM Yaourt y");
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

                    if(query.value("Present").toLongLong()==1)
                    {
                        check->setChecked(true);
                        inserted=true;
                    }
                    checks.push_back(check);
                    checks_id.push_back(query.value("IdY").toLongLong());
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
    QSqlQuery query;
    // gérer les exceptions
    if(p->db.open())
    {
        vector<QCheckBox*>::iterator it;
        bool select=false;

        if(inserted==false)
        {
            for(it=checks.begin();it!=checks.end();it++)
            {
                if((*it)->isChecked())
                {
                    select=true;
                    qDebug()<<"checked"<<(*it)->text();
                    query.prepare("INSERT INTO Sondage VALUES (NULL, 0, :id, :idY)");
                    query.bindValue(":id",p->last_id);
                    query.bindValue(":idY",checks_id.at(it-checks.begin()));

                    if(query.exec())
                    {
                        qDebug() << "It worked";
                    }
                    else
                    {
                        qDebug() << "Something goes wrong with the query" << p->db.lastError().text();
                        p->db.close();
                        exit(0);
                    }
                }
            }
        }
        else
        {
            query.prepare("DELETE FROM Sondage WHERE Id= :id");
            query.bindValue(":id",p->last_id);

            if(query.exec())
            {
                for(it=checks.begin();it!=checks.end();it++)
                {
                    if((*it)->isChecked())
                    {
                        select=true;
                        qDebug()<<"checked"<<(*it)->text();
                        query.prepare("INSERT INTO Sondage VALUES (NULL, 0, :id, :idY)");
                        query.bindValue(":id",p->last_id);
                        query.bindValue(":idY",checks_id.at(it-checks.begin()));

                        if(query.exec())
                        {
                            qDebug() << "It worked insert after delete";
                        }
                        else
                        {
                            qDebug() << "Something goes wrong with the query" << p->db.lastError().text();
                            p->db.close();
                            exit(0);
                        }
                    }
                }
            }
            else
            {
                qDebug() << "Something goes wrong with the delete query" << p->db.lastError().text();
                p->db.close();
                exit(0);
            }
        }

        if(select==false)
        {
            qDebug()<< "Nothing selected";
            // Gérer le fait de le redirect à la dernière page;
        }
    }
    else
    {
       qDebug() <<" not ok";
       exit(0);
    }

    sondage_page2* sond_2 = new sondage_page2(p);
    p->setCentralWidget(sond_2);

    int x = sond_2->width();
    int y = sond_2->height()+50;

    p->resize(x,y);
}

void Sondage_page1::on_pushButton_2_clicked()
{

}

void Sondage_page1::on_plus_clicked()
{
    if(row==1)
    {
        ui->Marque->show();
        ui->autre_mq->show();
        ui->Nom->show();
        ui->autre_nm->show();
        ui->Type->show();
        ui->autre_type->show();
        ui->Gout->show();
        ui->autre_gout->show();
        row++;
    }
    else
    {
        if(row>2)
        {
            ui->gridLayout->itemAt(ui->gridLayout->count()-1)->widget()->setVisible(false);
            ui->gridLayout->removeItem(ui->gridLayout->itemAt(ui->gridLayout->count()-1));
        }
        QLineEdit* autre_mq = new QLineEdit();
        QLineEdit* autre_nom = new QLineEdit();
        QLineEdit* autre_type = new QLineEdit();
        QLineEdit* autre_gout = new QLineEdit();
        QPushButton* del = new QPushButton("X");
        ui->gridLayout->addWidget(autre_mq,row,1,Qt::AlignHCenter);
        ui->gridLayout->addWidget(autre_nom,row,2,Qt::AlignHCenter);
        ui->gridLayout->addWidget(autre_type,row,3,Qt::AlignHCenter);
        ui->gridLayout->addWidget(autre_gout,row,4,Qt::AlignHCenter);
        ui->gridLayout->addWidget(del,row,5,Qt::AlignHCenter);
        row++;

        vector<QObject*> temp;
        temp.push_back(autre_mq);
        temp.push_back(autre_nom);
        temp.push_back(autre_type);
        temp.push_back(autre_gout);
        temp.push_back(del);
        objets.push_back(temp);

        QObject::connect(del,SIGNAL(clicked()),this,SLOT(del_clicked()));
    }
}

void Sondage_page1::del_clicked()
{
    delete objets.back().at(0);
    delete objets.back().at(1);
    delete objets.back().at(2);
    delete objets.back().at(3);
    delete objets.back().at(4);
    objets.pop_back();
    row--;

    if(row>2)
    {
        QPushButton* del = new QPushButton("X");
        objets.back().at(4)=del;
        ui->gridLayout->addWidget(del,row-1,5,Qt::AlignHCenter);
        QObject::connect(del,SIGNAL(clicked()),this,SLOT(del_clicked()));
    }
}
