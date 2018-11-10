#include "smithwidget.h"

SmithWidget::SmithWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setAutoFillBackground(false);
    setMouseTracking(true);
}

void SmithWidget::setSize(uint16_t asize) {
    if(size != 0) {
        delete []SList;
        delete []dispList;
    }
    size = asize;
    Sp = 0;
    SList = new std::complex<double>[size];
    dispList = new QPointF[size];
}

void SmithWidget::drawSmith(QPainter *painter) {
    double xsize = this->width();
    double ysize = this->height();

    double radius = (xsize < ysize) ? xsize/2.0 : ysize/2.0;
    double ycenter = ysize/2.0;
    double xcenter = xsize/2.0;

    painter->setPen(QPen(QColor(127,127,127)));

    // Y symmetry
    QMatrix m;
    m.translate(0, ysize);
    m.scale(1, -1);
    painter->setMatrix(m);

    painter->scale(scale, scale);

    // Real Line
    painter->drawLine(xsize/2.0-radius, ysize/2.0, xsize/2.0+radius, ysize/2.0);

    // Main circle
    QPointF *center = new QPointF(xsize/2, ysize/2);
    painter->drawEllipse(*center, radius, radius);

    for(uint32_t i = 0; i < scNbCircle; i++) {
        // Constant Resistance
        painter->setPen(QPen(QColor(127,63,63)));

        double val = ZDispList[i]/Z0;
        QPointF c((val/(val+1.0))*radius+xcenter,0.0+ycenter);
        double r = (1.0/(val+1.0)) * radius;
        painter->drawEllipse(c, r, r);

        // Constant Reactance
        painter->setPen(QPen(QColor(250,63,63)));
        QPointF cjp(1.0*radius+xcenter, (1.0/val)*radius+ycenter);
        double rjp = (1.0/val)*radius;
        painter->drawEllipse(cjp, rjp, rjp);

        QPointF cjn(1.0*radius+xcenter, (-1.0/val)*radius+ycenter);
        double rjn = (-1.0/val)*radius;
        painter->drawEllipse(cjn, rjn, rjn);
    }


    for(uint32_t i = 0; i < scNbCircle; i++) {
        // Constant Resistance
        painter->setPen(QPen(QColor(63,63,127)));

        double val = ZDispList[i]/Z0;
        QPointF c(xcenter-(val/(val+1.0))*radius,0.0+ycenter);
        double r = (1.0/(val+1.0)) * radius;
        painter->drawEllipse(c, r, r);

        // Constant Susceptance
        painter->setPen(QPen(QColor(63,63,250)));
        QPointF cjp(xcenter-1.0*radius, (1.0/val)*radius+ycenter);
        double rjp = (1.0/val)*radius;
        painter->drawEllipse(cjp, rjp, rjp);

        QPointF cjn(xcenter-1.0*radius, (-1.0/val)*radius+ycenter);
        double rjn = (-1.0/val)*radius;
        painter->drawEllipse(cjn, rjn, rjn);
    }

    for(uint16_t j = 0; j < Sp; j++) {
        dispList[j].setX(SList[j].real()*radius+xcenter);
        dispList[j].setY(SList[j].imag()*radius+ycenter);
    }
    painter->setPen(QPen(QColor(255,252,54)));
    painter->drawPolyline(dispList, (this->Sp));

}

void SmithWidget::addZPoint(std::complex<double> Zt) {
    double xsize = this->width();
    double ysize = this->height();

    // Convert S parameter to Impedance
    //std::complex<double> Zl = -1.0 * Z0 * (Sl+1.0)/(Sl-1.0);
    std::complex<double> S11 = (Zt - Z0)/(Zt + Z0);
    this->SList[Sp] = S11;
    Sp++;

}

void SmithWidget::addSPoint(std::complex<double> St) {
    this->SList[Sp] = St;
    Sp++;

}

void SmithWidget::paintEvent(QPaintEvent *event) {
    QPainter painter;

    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), QBrush(QColor(0, 0, 0)));

    drawSmith(&painter);

    painter.save();

    painter.end();
}

void SmithWidget::wheelEvent(QWheelEvent *event) {
    QPoint p = (event->angleDelta());
    scale += p.y()/1200.0;
    if(scale >= 5.0) scale = 5.0;
    else if(scale <= 0.1) scale = 0.1;
    this->repaint();
    event->accept();
}

void SmithWidget::mousePressEvent(QMouseEvent *event) {
    event->accept();
}

void SmithWidget::mouseReleaseEvent(QMouseEvent *event) {
    event->accept();
}
