#include "resultats.h"
#include "ui_resultats.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connexion.h"

Resultats::Resultats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Resultats)
{
    p = (MainWindow*) parent;
    ui->setupUi(this);
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
