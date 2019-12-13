#include "gameengine.hh"

GameEngine::GameEngine(int amountOfPlates, int amountOfPoles, QWidget *widget)
    :amountOfPlates_(amountOfPlates), amountOfPoles_(amountOfPoles), parent(widget)
{
    int spacing = parent->width()/amountOfPoles_;
    for (int i = 0; i < amountOfPoles_; ++i) {
        //set pole location in relation to game interface
        QPoint polePoint(i*spacing, 0);
        Pole* pole = new Pole(i, polePoint, parent);
        //all plates are added to first pole
        if (i == 0) {
            //plates are made from bottom to top
            for (int j = amountOfPlates_; j > 0; j--) {
                //plate height in relation to pole (ratio is used for better visuals)
                int plateHeight = pole->boundingRect().height()/amountOfPlates_;
                //plate width is set so top plate is square
                int plateWidth = j*plateHeight;
                //set plate to middle of pole and on top of previous plate
                QPoint plateLocation(
                        polePoint.x() - plateWidth/2
                            + pole->boundingRect().width() / 2
                            , pole->boundingRect().height() - (amountOfPlates - j + 1) * plateHeight);
                Plate* newPlate = new Plate(j, plateLocation, QSize(plateWidth, plateHeight), nullptr);
                pole->addPlate(newPlate);
            }
        }
        poles.push_back(pole);
    }
}

GameEngine::~GameEngine()
{

}

void GameEngine::drawPoles(QGraphicsScene *scene)
{
    for(auto pole:poles){
        scene->addItem(pole);
    }
}

bool GameEngine::makeMove(int buttonId)
{
    //switch function is used to connect correct button to corresponding movePlate method
    //ids are used because switch can't take string as parameter switch is better than 6 if statements
    switch (buttonId) {
    case -2:
        return poles[0]->movePlate(poles[1]);
    case -3:
        return poles[0]->movePlate(poles[2]);
    case -4:
        return poles[1]->movePlate(poles[0]);
    case -5:
        return poles[1]->movePlate(poles[2]);
    case -6:
        return poles[2]->movePlate(poles[0]);
    case -7:
        return poles[2]->movePlate(poles[1]);
    default:
        return false;
    }
}

bool GameEngine::gameEnd()
{
    for(int i = 1; i<=2;++i){
        int tmp = poles[i]->plates.size();
        if(tmp==amountOfPlates_){
            return true;
        }
    }return false;
}

bool GameEngine::isViable(int a, int b)
{
    if(poles[a]->plates.empty()){
        return false;
    }else if(poles[b]->plates.empty()){
        return true;
    }else{
        return(poles[a]->plates.back()->getNumber() < poles[b]->plates.back()->getNumber());
    }
}
