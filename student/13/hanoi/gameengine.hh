#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

#include <QWidget>
#include <QGraphicsScene>
#include <vector>
#include "plate.hh"
#include "pole.hh"

class GameEngine
{
public:
    explicit GameEngine(int maxPlates, int amountOfPoles, QWidget* widget = nullptr);
    ~GameEngine();
    void drawPoles(QGraphicsScene* scene);
    bool makeMove(int id);
    bool gameEnd();
private:

    std::vector<Pole *> poles;
    int maxPlates;
    int amountOfPoles;
    
    QWidget* parent;
};

#endif // GAMEENGINE_HH
