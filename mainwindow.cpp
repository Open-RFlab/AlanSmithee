#include <complex>
#include <QFileDialog>
#include <QMessageBox>

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

void MainWindow::openSFile() {
    QString sfilename = QFileDialog::getOpenFileName(this, tr("Open Directory"), "/home");
    std::ifstream sfile;
    sfile.open(sfilename.toStdString(), std::ios_base::in);

    if(!sfile.is_open()) {
        QMessageBox mbox;
        mbox.setText("Can't open the file");
        mbox.exec();
    }

    TouchstoneParser myParser(sfile);
    S2P data;
    data.ts = &myParser;
    data.ref = 1;
    Sparam.push_back(data);

    for(uint16_t i = 0; i < myParser.Sparam.size()-1; i ++) { /* bug of last element */
        this->ui->smithGLWidget->addSPoint(myParser.Sparam[i].S[0]);
    }
    this->ui->smithGLWidget->repaint();
}
