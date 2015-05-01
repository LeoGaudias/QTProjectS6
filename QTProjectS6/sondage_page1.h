#ifndef SONDAGE_PAGE1_H
#define SONDAGE_PAGE1_H

#include <QWidget>
#include <QAbstractButton>
#include "mainwindow.h"
#include <vector>
#include "QCheckBox"

using std::vector;

namespace Ui {
class Sondage_page1;
}

class Sondage_page1 : public QWidget
{
    Q_OBJECT

public:
    explicit Sondage_page1(QWidget *parent = 0);
    ~Sondage_page1();
    void rajouter_valeur();
    vector<vector<QObject*> > objets;
    vector<QCheckBox*> checks;
    vector<int> checks_id;

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_pushButton_2_clicked();

    void on_plus_clicked();

    void del_clicked();

private:
    Ui::Sondage_page1 *ui;
    MainWindow* p;
    int row;
};

#endif // SONDAGE_PAGE1_H
