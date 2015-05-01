#include "sondage_page2.h"
#include "ui_sondage_page2.h"
#include "sondage_page1.h"
#include "QDebug"

sondage_page2::sondage_page2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sondage_page2)
{
    p = (MainWindow*) parent;
    ui->setupUi(this);
}

sondage_page2::~sondage_page2()
{
    delete ui;
}

void sondage_page2::on_buttonBox_rejected()
{
    Sondage_page1* sond_1 = new Sondage_page1(p);
    p->setCentralWidget(sond_1);

    int x = sond_1->width();
    int y = sond_1->height()+50;

    p->resize(x,y);
}

void sondage_page2::on_buttonBox_accepted()
{
    qDebug()<<"accepted";
}
