#include "statistique.h"
#include "ui_statistique.h"
#include <QSqlQuery>
#include <QDebug>
#include <QtSql>

Statistique::Statistique(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistique)
{
    ui->setupUi(this);
    p = (MainWindow*) parent;
    r=NULL;

    type();

    marque();

    revenu();
}

void Statistique::type()
{
    QSqlQuery query;
    if(p->db.open())
    {
        query.prepare("SELECT * FROM Type");
        if(query.exec())
        {
            int i=0;
            while(query.next())
            {
                QRadioButton* type=new QRadioButton(query.value("NomT").toString());
                if(i>query.size()/2)
                {
                    ui->grid_type->addWidget(type,i-query.size()/2,1);
                }
                else
                {
                    ui->grid_type->addWidget(type,i,0);
                }
                type->setMinimumHeight(15);
                i++;

                QObject::connect(type,SIGNAL(toggled(bool)),this,SLOT(type_clicked(bool)));
            }
        }
        else
        {
            qDebug() << "Something goes wrong with the query select type" << p->db.lastError().text();
            p->db.close();
            exit(0);
        }
    }
}

void Statistique::marque()
{
    QSqlQuery query;
    if(p->db.open())
    {
        query.prepare("SELECT DISTINCT Marque FROM Yaourt");
        if(query.exec())
        {
            QButtonGroup* gr=new QButtonGroup(ui->groupe_marque);
            while(query.next())
            {
                QRadioButton* marque=new QRadioButton(query.value("Marque").toString());
                ui->grid_marque->addWidget(marque);
                gr->addButton(marque);
                //marque->setMinimumHeight(15);

                QObject::connect(marque,SIGNAL(toggled(bool)),this,SLOT(marque_clicked(bool)));
            }

            //ui->grid_marque->setVerticalSpacing(10);
        }
        else
        {
            qDebug() << "Something goes wrong with the query select type" << p->db.lastError().text();
            p->db.close();
            exit(0);
        }
    }
}

void Statistique::revenu()
{
    QSqlQuery query;
    if(p->db.open())
    {
        query.prepare("SELECT SUM(frequence) AS 'total', (select SUM(frequence) from Personne p,Sondage s WHERE Revenu=0 AND p.Id=s.Id) AS 'rev0',(select SUM(frequence) from Personne p,Sondage s WHERE Revenu=1 AND p.Id=s.Id) AS 'rev1',(select SUM(frequence) from Personne p,Sondage s WHERE Revenu=2 AND p.Id=s.Id) AS 'rev2',(select SUM(frequence) from Personne p,Sondage s WHERE Revenu=3 AND p.Id=s.Id) AS 'rev3',(select SUM(frequence) from Personne p,Sondage s WHERE Revenu=4 AND p.Id=s.Id) AS 'rev4' FROM Personne pe, Sondage so WHERE pe.Id=so.Id");
        if(query.exec())
        {
            query.next();
            if(query.value("total").isNull())
            {
                ui->line_rev1->setText("0");
                ui->line_rev2->setText("0");
                ui->line_rev3->setText("0");
                ui->line_rev4->setText("0");
                ui->line_rev5->setText("0");
                qDebug()<<"no Sondage";
            }
            else
            {
                int value=0;
                if(!query.value("rev0").isNull())
                {
                    value=query.value("rev0").toInt()/query.value("total").toInt();
                }
                ui->line_rev1->setText(QString::number(value));
                value=0;

                if(!query.value("rev1").isNull())
                {
                    value=query.value("rev1").toInt()/query.value("total").toInt();
                }
                ui->line_rev2->setText(QString::number(value));
                value=0;

                if(!query.value("rev2").isNull())
                {
                    value=query.value("rev2").toInt()/query.value("total").toInt();
                }
                ui->line_rev3->setText(QString::number(value));
                value=0;

                if(!query.value("rev3").isNull())
                {
                    value=query.value("rev3").toInt()/query.value("total").toInt();
                }
                ui->line_rev4->setText(QString::number(value));
                value=0;

                if(!query.value("rev4").isNull())
                {
                    value=query.value("rev4").toInt()/query.value("total").toInt();
                }
                ui->line_rev5->setText(QString::number(value));
            }
        }
        else
        {
            qDebug() << "Something goes wrong with the query select big" << p->db.lastError().text();
            p->db.close();
            exit(0);
        }
    }
}

void Statistique::type_clicked(bool toggled)
{
    QRadioButton *radio = qobject_cast<QRadioButton *>(sender());
    r=radio;
    if(radio)
    {
        QSqlQuery query;
        if(p->db.open())
        {
            query.prepare("SELECT AVG(Nb_enfant) AS 'enfant', AVG(DATE_FORMAT(sysdate(),'%Y')-DATE_FORMAT(dateNaiss,'%Y')) AS 'date',count(*) AS 'ok',(SELECT count(*) FROM Sondage) AS 'total' FROM Sondage s, Yaourt y, Personne p WHERE y.IdY=s.IdY AND p.Id=s.Id AND Type= :type");
            query.bindValue(":type",radio->text());
            if(query.exec())
            {
                query.next();
                float val;
                if(query.value("total").toInt()!=0)
                {
                    val=(query.value("ok").toFloat()/query.value("total").toFloat())*100.0;
                }
                else
                {
                    val=0.;
                }

                ui->conso_type->setText(QString::number(val)+" %");
                ui->tranch_age->setText(query.value("date").toString());
                ui->nb_enfant->setText(query.value("enfant").toString());
            }
        }
    }
}

void Statistique::marque_clicked(bool toggled)
{
    QRadioButton *radio = qobject_cast<QRadioButton *>(sender());
    if(radio)
    {
        if(r!=NULL)
        {
            QSqlQuery query;
            if(p->db.open())
            {
                query.prepare("SELECT count(*) AS 'ok',(SELECT count(*) FROM Sondage, Yaourt WHERE Type= :type) AS 'total' FROM Sondage s, Yaourt y WHERE y.IdY=s.IdY AND Marque= :marque AND Type= :type");
                query.bindValue(":marque",radio->text());
                query.bindValue(":type",r->text()); // to change
                if(query.exec())
                {
                    query.next();
                    float val;
                    if(query.value("total").toInt()!=0)
                    {
                        val=(query.value("ok").toFloat()/query.value("total").toFloat())*100.0;
                    }
                    else
                    {
                        val=0.;
                    }

                    ui->conso_marque->setText(QString::number(val)+" %");
                }
            }
        }
    }
}

Statistique::~Statistique()
{
    delete ui;
}
