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

private slots:
    void on_buttonBox_accepted();

private:
    MainWindow * p;
};

#endif // RESULTATS_H
