#include "gameengine.hh"
#include <QGraphicsItem>
#include <vector>
#include <iostream>
#include <QDebug>

GameEngine::GameEngine(int maxPlates, int amountOfPoles, QWidget *widget)
    :maxPlates(maxPlates), amountOfPoles(amountOfPoles), parent(widget)
{
    int spacing = parent->width()/amountOfPoles;
    for (int i = 0; i < amountOfPoles; ++i) {
        QPoint polePoint(i*spacing, -parent->geometry().height());
        Pole* pole = new Pole(maxPlates, i+1, polePoint, parent);
        if (i == 0) {
            for (int j = maxPlates; j > 0; j--) {
                int blockSize = 270/maxPlates*0.92;
                int grid = j*blockSize;
                QPoint blockOffset(
                        polePoint.x() - grid/2
                            + static_cast<int>(pole->boundingRect().width()/2)
                            , polePoint.y() + pole->boundingRect().height() -(maxPlates+1)*blockSize + grid);
                Plate* newPlate = new Plate(j, blockOffset, QSize(grid, blockSize), parent);
                pole->addPlate(newPlate);
            }

        }
        poles.push_back(pole);
    }

}

GameEngine::~GameEngine()
{
    for(auto pole : poles){
        delete pole;
    }
}

void GameEngine::drawPoles(QGraphicsScene *scene)
{
    for(auto pole:poles){
        scene->addItem(pole);
        pole->drawPlates(scene);
    }
}

bool GameEngine::makeMove(int id)
{
    switch (id) {
    case -2:
        return poles.at(0)->movePlate(poles.at(1));
    case -3:
        return poles.at(0)->movePlate(poles.at(2));
    case -4:
        return poles.at(1)->movePlate(poles.at(0));
    case -5:
        return poles.at(1)->movePlate(poles.at(2));
    case -6:
        return poles.at(2)->movePlate(poles.at(0));
    case -7:
        return poles.at(2)->movePlate(poles.at(1));
    default:
        return false;
    }
}

bool GameEngine::gameEnd()
{
    for(int i = 1; i<=2;++i){
        int tmp = poles.at(i)->getPlates().size();
        if(tmp==maxPlates){
            return true;
        }
    }return false;
}
