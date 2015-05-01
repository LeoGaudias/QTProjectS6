#include "resultats.h"
#include "ui_resultats.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Resultats::Resultats(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Resultats)
{
    p = (MainWindow*) parent;
    ui->setupUi(this);

    QQuickView *qmlView = new QQuickView;
    qmlView->setSource(QUrl::fromLocalFile("../QTProjectS6/graph.qml"));

    QWidget *container = QWidget::createWindowContainer(qmlView);

    ui->verticalLayout->addWidget(container);
}

Resultats::~Resultats()
{
    delete ui;
}
