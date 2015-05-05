#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include <QWidget>
#include "mainwindow.h"
#include <QRadioButton>

namespace Ui {
class Statistique;
}

class Statistique : public QWidget
{
    Q_OBJECT

public:
    explicit Statistique(QWidget *parent = 0);
    ~Statistique();

private slots:
    void marque_clicked(bool toggled);
    void type_clicked(bool toggled);

private:
    Ui::Statistique *ui;
    void type();
    void marque();
    void revenu();
    MainWindow* p;
    QRadioButton *r;

};

#endif // STATISTIQUE_H
