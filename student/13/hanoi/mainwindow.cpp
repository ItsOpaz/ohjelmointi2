#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene_ = new QGraphicsScene(this);
    //set gameInterface (window in which game is displayed) size and location
    ui->gameInterface->setGeometry(left_margin, top_margin,
                                   BORDER_RIGHT, BORDER_DOWN);
    //Label to block PushButtons since automatic game is tied to buttons
    // and can't be disabled. Label is hidden until automatic game is started
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
    //a and b are used so automated game ends in last pole despite amount of plates

    if(ui->amountOfPlates->text().toInt() % 2 == 0){
        autoGameOrder1 = 0;
        autoGameOrder2 = 1;
    }
    //makes move from A to B or B to A (only one is possible)
    if(autoCounter == autoGameOrder1){
        if(game->isViable(pole1Id,pole2Id)){
            ui->AtoB->click();
        }else{
            ui->BtoA->click();
        }
        ++autoCounter;
    //makes move from A to C or C to A (only one is possible)
    }else if(autoCounter == autoGameOrder2){
        if(game->isViable(pole1Id,pole3Id)){
            ui->AtoC->click();
        }else{
            ui->CtoA->click();
        }
        ++autoCounter;
    //makes move from B to C or C to B (only one is possible)
    }else{
        if(game->isViable(pole2Id,pole3Id)){
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
        ui->min->setText(QString::number(minMoves));
        game -> drawPoles(scene_);
        //timer tick speed can be changed here, timer is connected to tick slot
        timer.start(TICK_SPEED);
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
    //disable move buttons
    QList<QAbstractButton *> list  = ui->buttonGroup->buttons();
    foreach ( QAbstractButton *pButton, list){
        pButton->setDisabled(true);
    }
    //display message box with time
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
    if(secs!=60){
        ++secs;
    }else{
        secs = 0;
        ++mins;
    }
    ui->lcdSec->display(secs);
    ui->lcdMin->display(mins);
    //if automated game is clicked, game will perform autmove on every tick
    if(automated){
        autoMove();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    //if automated game is in progress keyboard and move buttons are not connected
    if(!automated){
        //function get iterator from keys vector and uses it to point what move button
        //from button group needs to be clicked
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
    //sets automated game on, sets label blocking move buttons visible and starts game
    automated = true;
    ui->autoGameLabel->show();
    on_startButton_clicked();
}
