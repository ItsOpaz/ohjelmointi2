#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QString>
#include <QtCore>
#include <QtGui>
#include <QString>
#include <cmath>
#include <QMessageBox>
#include <QDebug>

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
    QList<QAbstractButton *> buttonList  = ui->buttonGroup->buttons();
    foreach ( QAbstractButton *pButton, buttonList){
        pButton->setDisabled(true);
    }
}

MainWindow::~MainWindow()
{
    while(!game->poles.empty()){
        Pole* toDeletePole = game->poles.back();
        game->poles.pop_back();
        while(!toDeletePole->plates.empty()){
            Plate* toDeletePlate = toDeletePole->plates.back();
            toDeletePole->plates.pop_back();
            delete toDeletePlate;
        }
        delete toDeletePole;
    }
    delete game;
    delete ui;
}

void MainWindow::autoMove()
{
    if(autoCounter==0){
        if(game->poles[1]->plates.empty()){
            ui->AtoB->click();
        }else if(game->poles[0]->plates.empty()){
            ui->BtoA->click();
        }else if(game->isViable(0,1)){
            ui->AtoB->click();
        }else{
            ui->BtoA->click();
        }
        ++autoCounter;
    }else if(autoCounter==1){
        if(game->poles[2]->plates.empty()){
            ui->AtoC->click();
        }else if(game->poles[0]->plates.empty()){
            ui->CtoA->click();
        }else if(game->isViable(0,2)){
            ui->AtoC->click();
        }else{
            ui->CtoA->click();
        }
        ++autoCounter;
    }else{
        if(game->poles[2]->plates.empty()){
            ui->BtoC->click();
        }else if(game->poles[1]->plates.empty()){
            ui->CtoB->click();
        }else if(game->isViable(1,2)){
            ui->BtoC->click();
        }else{
            ui->CtoB->click();
        }
        autoCounter = 0;
    }
    
}

void MainWindow::on_startButton_clicked()
{
    QString plateValue = ui->amountOfPlates->text();
    if(!plateValue.toInt()){
        ui->textBrowser->setText("Amount of plates must be number!");
        return;
    }else if(plateValue.toInt()<=1){
        ui->textBrowser->setText("Amount of plates must over 1!");
        return;
    }else{
        ui->startButton->setDisabled(true);
        QList<QAbstractButton *> buttonList  = ui->buttonGroup->buttons();
        foreach ( QAbstractButton *pButton, buttonList){
            pButton->setDisabled(false);
        }
        secs = 0;
        mins = 0;
        ui->textBrowser->clear();
        game = new GameEngine(plateValue.toLong(), NUMBER_OF_POLES, ui->gameInterface);
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
    timer.stop();
    QList<QAbstractButton *> list  = ui->buttonGroup->buttons();
    foreach ( QAbstractButton *pButton, list){
        pButton->setDisabled(true);
    }
    QMessageBox msgBox;
    QString sMins = QString::number(mins);
    QString sSecs = QString::number(secs);
    msgBox.setToolTip("You won!");
    msgBox.setText("You won!\n Your time: " + sMins + " minutes " + sSecs + "seconds");
    QAbstractButton* answer = msgBox.addButton(tr("Quit"), QMessageBox::YesRole);
    msgBox.exec();
    if(answer == msgBox.clickedButton()){
        msgBox.close();
        ui->quitButton->click();
    }
}

void MainWindow::tick()
{
    if(ui->autoCheck->isChecked()){
        if(secs!=60){
            ++secs;
            ui->lcdSec->display(secs);
            autoMove();
        }else{
            secs = 0;
            ui->lcdSec->display(secs);
            ++mins;
            ui->lcdMin->display(mins);
            autoMove();
        }  
    }else{
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

}

void MainWindow::keyPressEvent(QKeyEvent *event){
    std::vector<Qt::Key>::iterator it = std::find(keys.begin(),keys.end(),event->key());
    int index = it-keys.begin();
    QList<QAbstractButton *> buttonList  = ui->buttonGroup->buttons();
    buttonList.at(index)->click();
}
