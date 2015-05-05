#ifndef SONDAGE_PAGE2_H
#define SONDAGE_PAGE2_H

#include <QWidget>
#include "mainwindow.h"
#include <vector>
#include <QCheckBox>
#include <QLineEdit>

using std::vector;

namespace Ui {
class sondage_page2;
}

class sondage_page2 : public QWidget
{
    Q_OBJECT

public:
    explicit sondage_page2(QWidget *parent = 0);
    ~sondage_page2();
    vector<QCheckBox*> objets;
    vector<int> checks_id;
    QMap<QCheckBox*,QLineEdit*> map;

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_buttonBox_clicked(QAbstractButton *button);

    void checked(int state);

private:
    Ui::sondage_page2 *ui;
    MainWindow* p;
    int row;
};

#endif // SONDAGE_PAGE2_H
