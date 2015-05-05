#include "piechartwidget.h"
#include <QPainter>

PieChartWidget::PieChartWidget(QWidget *parent) :
    QWidget(parent)
{
}

void PieChartWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect size = QRect(10,10,this->width()-50,this->height()-50);
    painter.setBrush(Qt::red);
    painter.drawPie(size,0,90*16);
    painter.drawText((int)(this->width()/2) + 30,100,"plop");
    painter.setBrush(Qt::blue);
    painter.drawPie(size,90*16,270*16);
}

