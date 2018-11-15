#ifndef VIEWER_H
#define VIEWER_H

#include <QDialog>

namespace Ui {
class Viewer;
}

class Viewer : public QDialog
{
    Q_OBJECT

public:
    explicit Viewer(QWidget *parent = 0);
    ~Viewer();

private:
    Ui::Viewer *ui;
};

#endif // VIEWER_H
