#include "gameengine.hh"
#include <QGraphicsItem>
#include <vector>
#include <iostream>
#include <QDebug>

GameEngine::GameEngine(int amoutOfPlates, int amountOfPoles, QWidget *widget)
    :amountOfPlates(amoutOfPlates), amountOfPoles(amountOfPoles), parent(widget)
{
    int spacing = parent->width()/amountOfPoles;
    for (int i = 0; i < amountOfPoles; ++i) {
        QPoint polePoint(i*spacing, -parent->geometry().height());
        Pole* pole = new Pole(amountOfPlates, i+1, polePoint, parent);
        if (i == 0) {
            for (int j = amountOfPlates; j > 0; j--) {
                int blockSize = 270/amountOfPlates*0.92;
                int grid = j*blockSize;
                QPoint blockOffset(
                        polePoint.x() - grid/2
                            + static_cast<int>(pole->boundingRect().width()/2)
                            , polePoint.y() + pole->boundingRect().height() -(amountOfPlates+1)*blockSize + grid);
                Plate* newPlate = new Plate(j, blockOffset, QSize(grid, blockSize), parent);
                pole->addPlate(newPlate);
            }

        }
        poles.push_back(pole);
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
