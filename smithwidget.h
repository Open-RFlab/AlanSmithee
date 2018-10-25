#ifndef SMITHWIDGET_H
#define SMITHWIDGET_H

#include <QObject>
#include <QWidget>

class SmithWidget : public QObject
{
    Q_OBJECT
public:
    explicit SmithWidget(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SMITHWIDGET_H