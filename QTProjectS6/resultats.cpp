#include "resultats.h"
#include "ui_resultats.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connexion.h"
#include "qcustomplot.h"

#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>

Resultats::Resultats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Resultats)
{
    p = (MainWindow*) parent;
    ui->setupUi(this);

    QSqlQuery query;
    if(p->db.open())
    {
        query.prepare("select distinct NomG from Gout order by NomG");
        if(query.exec())
        {
            if(query.size() > 0)
            {
                while(query.next())
                {
                    ui->cmb_Gout->addItem(query.value("NomG").toString());
                }
            }
            else
            {
                qDebug() << "no data";
            }
        }
        else
        {
            qDebug() << "Something goes wrong1";
            p->db.close();
            exit(0);
        }

        query.prepare("select distinct NomT from Type order by NomT");
        if(query.exec())
        {
            if(query.size() > 0)
            {
                while(query.next())
                {
                    ui->cmb_Type->addItem(query.value("NomT").toString());
                }
            }
            else
            {
                qDebug() << "no data";
            }
        }
        else
        {
            qDebug() << "Something goes wrong2";
            p->db.close();
            exit(0);
        }

        query.prepare("select distinct Marque from Yaourt order by Marque");
        if(query.exec())
        {
            if(query.size() > 0)
            {
                while(query.next())
                {
                    ui->cmb_Marque->addItem(query.value("Marque").toString());
                }
            }
            else
            {
                qDebug() << "no data";
            }
        }
        else
        {
            qDebug() << "Something goes wrong1";
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



Resultats::~Resultats()
{
    delete ui;
}

void Resultats::on_buttonBox_accepted()
{
    Connexion *co = new Connexion(p);
    p->setCentralWidget(co);

    int x = co->width();
    int y = co->height()+50;

    p->resize(x,y);
}

void Resultats::on_pushButton_clicked()
{
    if(p->db.open())
    {
        QSqlQuery query;
//        QString freq = "Fréquence d'achat";

//        QString repartition = "Répartition dans le foyer";

//        if(ui->cmb_graph->currentText().compare(freq))
//        {
//            query.prepare();
//            query.bindValue();
//        }
        qDebug() << ui->cmb_graph->currentIndex();
        if(ui->cmb_graph->currentIndex() == 1)
        {
            ui->Titre_Graph->setText("Moyenne d'age consommant des yaourt :" + ui->cmb_Marque->currentText() + " " +
                                     ui->cmb_Nom->currentText() + " " + ui->cmb_Type->currentText() + " " + ui->cmb_Gout->currentText() );
            //qDebug() << "hello";
            QCustomPlot * customPlot = new QCustomPlot(this);
            QVector<double> ticks;
            ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11;
            QVector<QString> labels;
            labels << "0-9" << "10-19" << "20-29" << "30-39" << "40-49" << "50-59" << "50-59" << "60-69" << "70-79" << "80-89" << "90-99";
            int array[] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 };
            QVector<double> data;

            int age = 0, max = 0;
            if(p->db.open())
            {
                query.prepare("select DateNaiss from Sondage s, Personne p where s.Id = p.Id and s.IdY = (select IdY from Yaourt where Marque = :str1 and Nom = :str2 and Type = :str3 and Gout = :str4) order by DateNaiss DESC");
                query.bindValue(":str1",ui->cmb_Marque->currentText());
                query.bindValue(":str2",ui->cmb_Nom->currentText());
                query.bindValue(":str3",ui->cmb_Type->currentText());
                query.bindValue(":str4",ui->cmb_Gout->currentText());

                QDate date;
                if(query.exec())
                {
                    if(query.size() > 0)
                    {
                        while(query.next())
                        {
                           date = query.value("DateNaiss").toDate();
                           age = QDate::currentDate().year() - date.year();
                           if(age < 9)
                           {
                               array[0]++;
                           }
                           else if(age < 19)
                           {
                               array[1];
                           }
                           else if(age < 29)
                           {
                               array[2]++;
                           }
                           else if(age < 39)
                           {
                               array[3]++;
                           }
                           else if(age < 49)
                           {
                               array[4]++;
                           }
                           else if(age < 59)
                           {
                               array[5]++;
                           }
                           else if(age < 69)
                           {
                               array[6]++;
                           }
                           else if(age < 79)
                           {
                               array[7]++;
                           }
                           else if(age < 89)
                           {
                               array[8]++;
                           }
                           else
                           {
                               array[9]++;
                           }
                        }
                        for (int var = 0; var < 10; ++var)
                        {
                            max += array[var];

                        }
                        data << (double)array[0] << (double)array[1] << (double)array[2] << (double)array[3] << (double)array[4] << (double)array[5] << (double)array[6] << (double)array[7] << (double)array[8] << (double)array[9] << (double)array[10];
                    }
                    else
                    {
                        qDebug() << "no data";
                    }
                }
                else
                {
                   qDebug() << "Something goes wrong" << p->db.lastError().text();
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
            qDebug() << ticks;
            qDebug() << data;
            // create empty bar chart objects:
            QCPBars *trancheAge = new QCPBars(customPlot->xAxis, customPlot->yAxis);
            customPlot->addPlottable(trancheAge);

            // set names and colors:
            QPen pen;
            pen.setWidthF(1.2);

            trancheAge->setName("Tranche d'Age");
            pen.setColor(QColor(1, 92, 191));
            trancheAge->setPen(pen);
            trancheAge->setBrush(QColor(1, 92, 191, 50));


            // prepare x axis with country labels:

            customPlot->xAxis->setAutoTicks(false);
            customPlot->xAxis->setAutoTickLabels(false);
            customPlot->xAxis->setTickVector(ticks);
            customPlot->xAxis->setTickVectorLabels(labels);
            customPlot->xAxis->setTickLabelRotation(60);
            customPlot->xAxis->setSubTickCount(0);
            customPlot->xAxis->setTickLength(0, 4);
            customPlot->xAxis->grid()->setVisible(true);
            customPlot->xAxis->setRange(0, 8);

            // prepare y axis:
            customPlot->yAxis->setRange(0, max);
            customPlot->yAxis->setPadding(5); // a bit more space to the left border
            customPlot->yAxis->setLabel("Nombre de Personne");
            customPlot->yAxis->grid()->setSubGridVisible(true);
            QPen gridPen;
            gridPen.setStyle(Qt::SolidLine);
            gridPen.setColor(QColor(0, 0, 0, 25));
            customPlot->yAxis->grid()->setPen(gridPen);
            gridPen.setStyle(Qt::DotLine);
            customPlot->yAxis->grid()->setSubGridPen(gridPen);

            // Add data:

            trancheAge->setData(ticks, data);


            // setup legend:
            customPlot->legend->setVisible(true);
            customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);
            customPlot->legend->setBrush(QColor(255, 255, 255, 200));
            QPen legendPen;
            legendPen.setColor(QColor(130, 130, 130, 200));
            customPlot->legend->setBorderPen(legendPen);
            QFont legendFont = font();
            legendFont.setPointSize(10);
            customPlot->legend->setFont(legendFont);
            customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

            ui->verticalLayout->addWidget(customPlot);
        }
//        else if(ui->cmb_graph->currentText().compare(repartition))
//        {
//            query.prepare();
//            query.bindValue();
//        }
//        else
//        {
//            query.prepare();
//            query.bindValue();
//        }
    }
    else
    {
        qDebug() << "Something goes wrong";
        p->db.close();
        exit(0);
    }

}

void Resultats::on_cmb_Marque_currentIndexChanged(const QString &arg1)
{
    for (int i = 0; i < ui->cmb_Nom->count(); ++i)
    {
        ui->cmb_Nom->removeItem(i);
    }

    QSqlQuery query;
    if(p->db.open())
    {
        query.prepare("select distinct Nom from Yaourt where Marque = :m order by Nom");
        query.bindValue(":m",arg1);
        if(query.exec())
        {
            if(query.size() > 0)
            {
                while(query.next())
                {
                    ui->cmb_Nom->addItem(query.value("Nom").toString());
                }
            }
            else
            {
                qDebug() << "no data";
            }
        }
        else
        {
            qDebug() << "Something goes wrong3";
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
