#ifndef RECAP2_H
#define RECAP2_H

#include <QWidget>
#include <QAbstractButton>
#include "mainwindow.h"

namespace Ui {
class Recap2;
}

class Recap2 : public QWidget
{
    Q_OBJECT

public:
    explicit Recap2(QWidget *parent = 0);
    ~Recap2();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::Recap2 *ui;
    MainWindow* p;
    int row;
    vector<QObject*> objets;
};

#endif // RECAP2_H
