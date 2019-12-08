#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QString>
#include <QtCore>
#include <QtGui>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene_ = new QGraphicsScene(this);
    GameEngine* game;

    int left_margin = 10;
    int top_margin = 270;
    ui->gameInterface->setGeometry(left_margin, top_margin,
                                   BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->gameInterface->setScene(scene_);

    ui->AtoB->setDisabled(true);
    ui->AtoC->setDisabled(true);
    ui->BtoA->setDisabled(true);
    ui->BtoC->setDisabled(true);
    ui->CtoA->setDisabled(true);
    ui->CtoB->setDisabled(true);

    connect(ui->AtoB,&QPushButton::clicked, this,[&](){
       game->makeMove(1,2);
    });
    connect(ui->AtoC,&QPushButton::clicked, this,[&](){
       game->makeMove(1,3);
    });
    connect(ui->BtoA,&QPushButton::clicked, this,[&](){
       game->makeMove(2,1);
    });
    connect(ui->BtoC,&QPushButton::clicked, this,[&](){
       game->makeMove(2,3);
    });
    connect(ui->CtoA,&QPushButton::clicked, this,[&](){
       game->makeMove(3,1);
    });
    connect(ui->CtoB,&QPushButton::clicked, this,[&](){
       game->makeMove(3,2);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    QString value = ui->amountOfPlates->text();
    if(!value.toInt()){
        ui->textBrowser->setText("Amount of plates must be number!");
        return;
    }if(value.toInt()<=1){
        ui->textBrowser->setText("Amount of plates must over 1!");
        return;
    }else{
        ui->AtoB->setDisabled(false);
        ui->AtoC->setDisabled(false);
        ui->BtoA->setDisabled(false);
        ui->BtoC->setDisabled(false);
        ui->CtoA->setDisabled(false);
        ui->CtoB->setDisabled(false);
        int amount = value.toInt();
        scene_->clear();
        ui->textBrowser->clear();
        GameEngine* game = new GameEngine(amount, NUMBER_OF_POLES, ui->gameInterface);
        game -> drawPoles(scene_);
    }
}


