#ifndef RESULTATS_H
#define RESULTATS_H

#include <QWidget>

namespace Ui {
class Resultats;
}

class MainWindow;

class Resultats : public QWidget
{
    Q_OBJECT

public:
    explicit Resultats(QWidget *parent = 0);
    ~Resultats();
    Ui::Resultats *ui;
    MainWindow * p;
//    int ageMoyenTotal();
//    int ageMoyen();

private slots:
    void on_buttonBox_accepted();


    void on_pushButton_clicked();

    void on_cmb_Marque_currentIndexChanged(const QString &arg1);

private:

};

#endif // RESULTATS_H
