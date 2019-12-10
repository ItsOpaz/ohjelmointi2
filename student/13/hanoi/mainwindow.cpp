#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QString>
#include <QtCore>
#include <QtGui>
#include <QString>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene_ = new QGraphicsScene(this);
    ui->gameInterface->setGeometry(left_margin, top_margin,
                                   BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->gameInterface->setScene(scene_);
    QList<QAbstractButton *> list  = ui->buttonGroup->buttons();
    foreach ( QAbstractButton *pButton, list){
        pButton->setDisabled(true);
    }
}

MainWindow::~MainWindow()
{
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
        QList<QAbstractButton *> list  = ui->buttonGroup->buttons();
        foreach ( QAbstractButton *pButton, list){
            pButton->setDisabled(false);
        }
        scene_->clear();
        ui->textBrowser->clear();
        game = new GameEngine(plateValue.toInt(), NUMBER_OF_POLES, ui->gameInterface);
        minMoves = pow(2,plateValue.toInt())-1;
        game -> drawPoles(scene_);
        connect(ui->buttonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            [=](int id){
            if(!game->makeMove(id)){
                ui->textBrowser->setText("Sorry, can't do that");
            }else{
                QString buttonName = ui->buttonGroup->button(id)->objectName();
                moves.push_back(buttonName);
                new QListWidgetItem(buttonName,ui->allMoves);
                ui->allMoves->scrollToBottom();
                ui->count->setText(QString::number(moves.size()));
                ui->min->setText(QString::number(minMoves-moves.size()));
                ui->textBrowser->clear();
        }
        });
    }
}
