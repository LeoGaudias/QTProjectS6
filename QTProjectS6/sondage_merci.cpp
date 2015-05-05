#include "sondage_merci.h"
#include "ui_sondage_merci.h"
#include "sondage_page2.h"
#include "recap2.h"
#include <QPushButton>


Sondage_merci::Sondage_merci(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sondage_merci)
{
    ui->setupUi(this);
    p = (MainWindow*) parent;
    ui->buttonBox->button(QDialogButtonBox::Abort)->setText("<< Page précédente");
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Quitter");

    ui->pushButton->setStyleSheet("color : #0000ff");
}

Sondage_merci::~Sondage_merci()
{
    delete ui;
}

void Sondage_merci::on_buttonBox_accepted()
{
    p->myfile.close();
    p->db.close();
    exit(0);
}

void Sondage_merci::on_buttonBox_rejected()
{
    sondage_page2* sond_2 = new sondage_page2(p);
    p->setCentralWidget(sond_2);

    int x = sond_2->width();
    int y = sond_2->height()+50;

    p->resize(x,y);
}

void Sondage_merci::on_label_2_linkActivated(const QString &link)
{

}

void Sondage_merci::on_pushButton_clicked()
{
    Recap2* re = new Recap2(p);
    p->setCentralWidget(re);

    int x = re->width();
    int y = re->height()+50;

    p->resize(x,y);
}
