#ifndef RECAP_H
#define RECAP_H

#include <QWidget>

#include "mainwindow.h"

namespace Ui {
class Recap;
}

class Recap : public QWidget
{
    Q_OBJECT

public:
    explicit Recap(QWidget *parent = 0);
    ~Recap();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::Recap *ui;
    MainWindow* p;
};

#endif // RECAP_H