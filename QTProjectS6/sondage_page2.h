#ifndef SONDAGE_PAGE2_H
#define SONDAGE_PAGE2_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class sondage_page2;
}

class sondage_page2 : public QWidget
{
    Q_OBJECT

public:
    explicit sondage_page2(QWidget *parent = 0);
    ~sondage_page2();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::sondage_page2 *ui;
    MainWindow* p;
};

#endif // SONDAGE_PAGE2_H
