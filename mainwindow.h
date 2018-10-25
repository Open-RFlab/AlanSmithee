#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "touchwater/inc/touchwater.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbSetZp_clicked();
    void openSFile();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
