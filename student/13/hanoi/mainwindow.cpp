#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QString>
#include <QtCore>
#include <QtGui>
#include <QString>
#include <cmath>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene_ = new QGraphicsScene(this);
    ui->gameInterface->setGeometry(left_margin, top_margin,
                                   BORDER_RIGHT, BORDER_DOWN);
    ui->gameInterface->setScene(scene_);
    ui->lcdMin->setStyleSheet("background-color: lightcyan");
    ui->lcdSec->setStyleSheet("background-color: lightblue");
    QList<QAbstractButton *> list  = ui->buttonGroup->buttons();
    foreach ( QAbstractButton *pButton, list){
        pButton->setDisabled(true);
    }
}

MainWindow::~MainWindow()
{
    delete game;
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    QString plateValue = ui->amountOfPlates->text();
    if(!plateValue.toInt()){
        ui->textBrowser->setText("Amount of plates must be number!");
        return;
    }if(plateValue.toInt()<=1){
        ui->textBrowser->setText("Amount of plates must over 1!");
        return;
    }else{
        ui->startButton->setDisabled(true);
        QList<QAbstractButton *> list  = ui->buttonGroup->buttons();
        foreach ( QAbstractButton *pButton, list){
            pButton->setDisabled(false);
        }
        secs = 0;
        mins = 0;
        ui->textBrowser->clear();
        game = new GameEngine(plateValue.toInt(), NUMBER_OF_POLES, ui->gameInterface);
        minMoves = pow(2,plateValue.toInt())-1;
        game -> drawPoles(scene_);
        timer.start(1000);
        connect(&timer, &QTimer::timeout, this, &MainWindow::tick);
        connect(ui->buttonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            [=](int id){
            if(!game->makeMove(id)){
                ui->textBrowser->setText("Sorry, can't do that");
            }else{
                QString buttonName = ui->buttonGroup->button(id)->objectName();
                ++moveCounter;
                new QListWidgetItem(buttonName,ui->allMoves);
                ui->allMoves->scrollToBottom();
                ui->count->setText(QString::number(moveCounter));
                ui->min->setText(QString::number(minMoves-moveCounter));
                ui->textBrowser->clear();
                if(game->gameEnd()){
                    endGame();
                }
            }
        });
    }
}

void MainWindow::endGame()
{
    scene_->clear();
    timer.stop();
    QList<QAbstractButton *> list  = ui->buttonGroup->buttons();
    foreach ( QAbstractButton *pButton, list){
        pButton->setDisabled(true);
    }
    QMessageBox msgBox;
    msgBox.setText("You won!");
    msgBox.exec();
}

void MainWindow::tick()
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
