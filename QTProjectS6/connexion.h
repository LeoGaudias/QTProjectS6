#ifndef CONNEXION_H
#define CONNEXION_H

#include <QWidget>

namespace Ui {
class Connexion;
}

class MainWindow;

class Connexion : public QWidget
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent = 0);
    ~Connexion();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Result_clicked();

private:
    Ui::Connexion *ui;
    MainWindow* p;
};

#endif // CONNEXION_H
