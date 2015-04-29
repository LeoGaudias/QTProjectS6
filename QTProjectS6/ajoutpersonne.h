#ifndef AJOUTPERSONNE_H
#define AJOUTPERSONNE_H

#include <QWidget>
#include <QAbstractButton>

namespace Ui {
class AjoutPersonne;
}

class AjoutPersonne : public QWidget
{
    Q_OBJECT

public:
    explicit AjoutPersonne(QWidget *parent = 0);
    ~AjoutPersonne();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AjoutPersonne *ui;
};

#endif // AJOUTPERSONNE_H
