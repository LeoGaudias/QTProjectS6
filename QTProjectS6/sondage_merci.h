#ifndef SONDAGE_MERCI_H
#define SONDAGE_MERCI_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class Sondage_merci;
}

class Sondage_merci : public QWidget
{
    Q_OBJECT

public:
    explicit Sondage_merci(QWidget *parent = 0);
    ~Sondage_merci();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Sondage_merci *ui;
    MainWindow* p;
};

#endif // SONDAGE_MERCI_H
