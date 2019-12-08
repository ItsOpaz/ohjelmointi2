#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

#include <QWidget>
#include <QGraphicsScene>
#include <vector>
#include "rod.hh"
#include "plate.hh"

class GameEngine
{
public:
    GameEngine(int platesPerRod, int amountOfRods= 3, QWidget* widget = nullptr);
    ~GameEngine();
    void drawTowers(QGraphicsScene* scene);
    bool makeMove(int senderID, int receiverID);


private:
    std::vector <Rod*> rods;
    int platesPerRod;
    int amountOfRods;

    QWidget* parent;
};

#endif // GAMEENGINE_HH
