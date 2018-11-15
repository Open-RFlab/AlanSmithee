#include "viewer.h"
#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Viewer)
{
    ui->setupUi(this);
}

Viewer::~Viewer()
{
    delete ui;
}
