#ifndef SMITHWIDGET_H
#define SMITHWIDGET_H

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QPainter>

#include <complex>

const uint32_t scNbCircle = 6;

class SmithWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    SmithWidget(QWidget *parent);

    void setSize(uint16_t size);

    std::complex<double> *SList;
    QPointF *dispList;
    uint16_t Sp = 0;
    uint16_t size = 0;

    double ZDispList[scNbCircle] = {10.0, 25.0, 50.0, 100.0, 200.0, 500.0};

    double Z0 = 50;

    void addZPoint(std::complex<double> Zt);
    void addSPoint(std::complex<double> St);

private:
    void drawSmith(QPainter *painter);
    void calcCircle();

protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // SMITHWIDGET_H
