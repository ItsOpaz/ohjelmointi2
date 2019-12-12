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

    //set gameInterface (window in which game is displayed) size and location
    ui->gameInterface->setGeometry(left_margin, top_margin,
                                   BORDER_RIGHT, BORDER_DOWN);
    /*Label to block PushButtons since automatic game is tied to buttons
     * and can't be disabled. Label is hidden until automatic game is started
     * */
    ui->autoGameLabel->setStyleSheet("background-color: rgb(50, 50, 50)");
    ui->autoGameLabel->hide();

    ui->gameInterface->setScene(scene_);
    ui->lcdMin->setStyleSheet("background-color: lightcyan");
    ui->lcdSec->setStyleSheet("background-color: lightblue");

    //disables all buttons that move plates, since gameinterface is empty
    QList<QAbstractButton *> buttonList  = ui->buttonGroup->buttons();
    foreach ( QAbstractButton *pButton, buttonList){
        pButton->setDisabled(true);
    }
}


MainWindow::~MainWindow()
{
    //check if game exists so there is no attempt to delete empty game
    if(game != nullptr){
        //delete all poles in game
        while(!game->poles.empty()){
            Pole* toDeletePole = game->poles.back();
            game->poles.pop_back();
            //delete all plates in pole
            while(!toDeletePole->plates.empty()){
                Plate* toDeletePlate = toDeletePole->plates.back();
                toDeletePole->plates.pop_back();
                delete toDeletePlate;
            }
            delete toDeletePole;
        }
        delete game;
    }
    delete ui;
}

//if automated game is started, autoMove makes one move when it's called
void MainWindow::autoMove()
{
    //makes move from A to B or B to A (only one is possible)
    if(autoCounter==0){
        if(game->isViable(0,1)){
            ui->AtoB->click();
        }else{
            ui->BtoA->click();
        }
        ++autoCounter;

    //makes move from A to C or C to A (only one is possible)
    }else if(autoCounter==1){
        if(game->isViable(0,2)){
            ui->AtoC->click();
        }else{
            ui->CtoA->click();
        }
        ++autoCounter;

    //makes move from B to C or C to B (only one is possible)
    }else{
        if(game->isViable(1,2)){
            ui->BtoC->click();
        }else{
            ui->CtoB->click();
        }
        autoCounter = 0;
    }
    
}

void MainWindow::on_startButton_clicked()
{
    //check if entered value is valid, errors displayed in text browser
    QString plateValue = ui->amountOfPlates->text();
    if(!plateValue.toInt()){
        ui->textBrowser->setText("Amount of plates must be number!");
        return;
    }else if(plateValue.toInt()<=1){
        ui->textBrowser->setText("Amount of plates must over 1!");
        return;
    }else{
        //if input si valid, some buttons are disabled
        ui->startButton->setDisabled(true);
        ui->autoGame->setDisabled(true);
        //all move buttons(in button group) are enabled
        QList<QAbstractButton *> buttonList  = ui->buttonGroup->buttons();
        foreach ( QAbstractButton *pButton, buttonList){
            pButton->setDisabled(false);
        }
        ui->textBrowser->clear();
        //game engine is created
        game = new GameEngine(plateValue.toLong(), NUMBER_OF_POLES, ui->gameInterface);
        //minimum moves needed is counter (2^n-1)
        minMoves = pow(2,plateValue.toLong())-1;
        game -> drawPoles(scene_);
        //timer tick speed can be changed here, timer is connected to tick slot
        timer.start(1000);
        connect(&timer, &QTimer::timeout, this, &MainWindow::tick);
        //all move buttons in buttongroup are connected by id
        connect(ui->buttonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            [=](int id){
            //if move is not possible error is displayed in text browser
            if(!game->makeMove(id)){
                ui->textBrowser->setText("Sorry, can't do that");
            }else{
                //made moves are saved to list item
                QString buttonName = ui->buttonGroup->button(id)->objectName();
                new QListWidgetItem(buttonName,ui->allMoves);
                ui->allMoves->scrollToBottom();
                //amount of moves and moves left for minimun are shown
                ++moveCounter;
                ui->count->setText(QString::number(moveCounter));
                ui->min->setText(QString::number(minMoves-moveCounter));
                ui->textBrowser->clear();
                //check for game end
                if(game->gameEnd()){
                    endGame();
                }
            }
        });
    }
}

void MainWindow::endGame()
{
    ui->lcdSec->display(secs);
    ui->lcdMin->display(mins);
    timer.stop();
    QList<QAbstractButton *> list  = ui->buttonGroup->buttons();
    foreach ( QAbstractButton *pButton, list){
        pButton->setDisabled(true);
    }
    QMessageBox msgBox;
    QString sMins = QString::number(mins);
    QString sSecs = QString::number(secs);
    msgBox.setWindowTitle("You won!");
    msgBox.setText("Your time: " + sMins + " minutes " + sSecs + "seconds");
    QAbstractButton* yButton = msgBox.addButton("Check moves made", QMessageBox::YesRole);
    msgBox.addButton("Quit?", QMessageBox::NoRole);
    msgBox.exec();
    if(msgBox.clickedButton() == yButton){
        msgBox.close();
    }else{
        msgBox.close();
        ui->quitButton->click();
    }
}

void MainWindow::tick()
{
    if(automated){
        autoMove();
    }
    if(secs!=60){
        ++secs;
    }else{
        secs = 0;
        ++mins;
    }
    ui->lcdSec->display(secs);
    ui->lcdMin->display(mins);
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(!automated){
        std::vector<Qt::Key>::iterator it = std::find(keys.begin(), keys.end(), event->key());
        if(it != keys.end()){
            int index = it-keys.begin();
            QList<QAbstractButton *> buttonList  = ui->buttonGroup->buttons();
            buttonList.at(index)->click();
        }
    }
}

void MainWindow::on_autoGame_clicked()
{
    automated = true;
    ui->autoGameLabel->show();
    on_startButton_clicked();
}
