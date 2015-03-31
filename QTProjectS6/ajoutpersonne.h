#ifndef AJOUTPERSONNE_H
#define AJOUTPERSONNE_H

#include <QWidget>

namespace Ui {
class AjoutPersonne;
}

class AjoutPersonne : public QWidget
{
    Q_OBJECT

public:
    explicit AjoutPersonne(QWidget *parent = 0);
    ~AjoutPersonne();

private:
    Ui::AjoutPersonne *ui;
};

#endif // AJOUTPERSONNE_H
