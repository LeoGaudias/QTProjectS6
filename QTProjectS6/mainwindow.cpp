#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ajoutpersonne.h"
#include "sondage_page1.h"
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    aj_p=new AjoutPersonne();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuitter_triggered()
{
    close();
}

void MainWindow::on_actionD_connexion_triggered()
{
    // s'inscire ou se déconnecter
}

void MainWindow::on_pushButton_clicked()
{
    AjoutPersonne* aj_p=new AjoutPersonne();
    aj_p->show();

    Sondage_page1* sond_1=new Sondage_page1();
    sond_1->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->centralWidget->setVisible(false);
    layout()->addWidget(aj_p);
}
