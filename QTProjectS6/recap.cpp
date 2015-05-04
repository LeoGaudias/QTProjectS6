#include "recap.h"
#include "ui_recap.h"
#include "sondage_page1.h"
#include "connexion.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>


Recap::Recap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Recap)
{
    p = (MainWindow *) parent;
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Close)->setText("Se déconnecter");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Continuer");
    ui->buttonBox->button(QDialogButtonBox::Reset)->setText("Reset les données");
}

Recap::~Recap()
{
    delete ui;
}

void Recap::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Close)) // se déconnecte
    {
        p->ui->actionConnextion->setText("S'inscrire");
        p->connected = false;
        Connexion* co = new Connexion(p);
        p->setCentralWidget(co);

        int x = co->width();
        int y = co->height()+50;

        p->resize(x,y);
    }
    else if(button == ui->buttonBox->button(QDialogButtonBox::Cancel)) //retourne au sondage
    {
        Sondage_page1* sond_1 = new Sondage_page1(p);
        p->setCentralWidget(sond_1);

        int x = sond_1->width();
        int y = sond_1->height()+50;

        p->resize(x,y);
    }
    else // wipe tte les données
    {
        QSqlQuery query;
        if(p->db.open())
        {
            query.prepare("DELETE FROM Sondage WHERE Id = :id");
            query.bindValue(":id",p->last_id);
            if(query.exec())
            {
                qDebug() << "Wipe data ok";
                QMessageBox::about(p,"Réinitialisation","Vos données ont bien été réinitialisées");
            }
            else
            {
                qDebug() << "Something goes wrong";
                p->db.close();
                close();
            }
        }
        else
        {
            qDebug() << "Something goes wrong";
            p->db.close();
            close();
        }

    }
}

void Recap::on_buttonBox_accepted()
{

}

void Recap::on_buttonBox_rejected()
{

}
