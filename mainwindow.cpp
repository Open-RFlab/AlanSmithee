#include <complex>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "smithwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->smithGLWidget->setSize(15000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbSetZp_clicked()
{
    std::string sZt = this->ui->tZpoint->text().toStdString();
    std::istringstream is('(' + sZt + ')');

    std::complex<double> c;
    is >> c;

    this->ui->smithGLWidget->addZPoint(c);
    this->ui->smithGLWidget->repaint();
}
