#ifndef SONDAGE_PAGE1_H
#define SONDAGE_PAGE1_H

#include <QWidget>

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

private:
    Ui::Sondage_page1 *ui;
};

#endif // SONDAGE_PAGE1_H
