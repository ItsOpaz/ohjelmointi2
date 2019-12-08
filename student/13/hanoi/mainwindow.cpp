#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QString>
#include <iostream>
#include <vector>

#include "rod.hh"
#include "plate.hh"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    scene_ = new QGraphicsScene();

    int left_margin = 10;
    int top_margin = 270;

    ui_->gameInterface->setGeometry(left_margin, top_margin,
                                   BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui_->gameInterface->setScene(scene_);
    ui_->gameInterface->setSceneRect(scene_->sceneRect());

}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::StartGame()
{

}

void MainWindow::Restart()
{

}



