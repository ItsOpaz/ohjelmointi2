#include "gameengine.hh"
#include <QGraphicsItem>

GameEngine::GameEngine(int amoutOfPlates, int amountOfPoles, QWidget *widget)
    :amountOfPlates(amoutOfPlates), amountOfPoles(amountOfPoles), parent(widget)
{
    int spacing = parent->width()/amountOfPoles;
    int offset = spacing/2;

    for (int i = 0; i < amountOfPoles; ++i) {
        QPoint polePoint(i*spacing-offset, static_cast<int>(-parent->geometry().height()));
        Pole* pole = new Pole(amountOfPlates, polePoint, parent);

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

bool GameEngine::makeMove(int sender, int receiver)
{

}
