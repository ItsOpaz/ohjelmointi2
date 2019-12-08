#include "gameengine.hh"

GameEngine::GameEngine(int platesPerRod, int amountOfRods, QWidget *widget)
    :platesPerRod(platesPerRod), amountOfRods(amountOfRods), parent(widget)
{
    int spacing = parent ->width()/amountOfRods;
    int offset = spacing/2;

    for(int i = 0;i<amountOfRods;++i){
        QPoint rodPlace(i*spacing+offset, static_cast<int>(-parent->geometry().height()));
        Rod* rod = new Rod(platesPerRod, rodPlace, parent);
        if (i == 0) {
                for (int j = platesPerRod; j > 0; j--) {
                    int blockSize = 40;
                    int grid = j*blockSize;
                    QPoint blockOffset(
                           rodPlace.x() - grid/2
                               + static_cast<int>(rod->boundingRect().width()/2)
                               , rodPlace.y() + rod->boundingRect().height() -(platesPerRod+1)*blockSize + grid);


                   Plate* newPlate = new Plate(j, blockOffset, QSize(grid, blockSize), parent);
                   rod->addPlate(newPlate);
                   }
               }
    }

}

void GameEngine::drawTowers(QGraphicsScene *scene)
{

}

bool GameEngine::makeMove(int senderID, int receiverID)
{

}
