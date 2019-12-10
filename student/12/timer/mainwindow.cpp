#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdMin->setStyleSheet("background-color: red");
    ui->lcdSec->setStyleSheet("background-color: blue");
    timer.start(1000);
    connect(&timer, &QTimer::timeout, this, &MainWindow::tickSimulator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tickSimulator()
{
    if(secs!=60){
        ui->lcdSec->display(secs);
        ++secs;
    }else{
        secs = 0;
        ui->lcdSec->display(secs);
        ++mins;
        ui->lcdMin->display(mins);
    }
}
