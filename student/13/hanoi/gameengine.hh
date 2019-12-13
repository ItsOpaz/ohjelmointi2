/* Module: GameEngine
 * ---------------
 * GameEngine that holds record of all poles. Determines if game has ended
 * or not.
 * ---------------
 * Olli Pettersson, olli.pettersson@tuni.fi, 283651
 * */
#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

#include "plate.hh"
#include "pole.hh"

class GameEngine
{
public:
    explicit GameEngine(int amountOfPlates, int amountOfPoles, QWidget* widget = nullptr);
    ~GameEngine();
    //adds poles and plates to scene
    void drawPoles(QGraphicsScene* scene);
    //connects movebuttons by id value to corresponding Pole::movePlate method with switch
    bool makeMove(int buttonId);
    //checks if all plates are moved from starting pole to other pole
    bool gameEnd();
    //checks if move can be made, used for automated game
    bool isViable(int a, int b);
    std::vector<Pole *> poles;

private:
    int amountOfPlates_;
    int amountOfPoles_;
    QWidget* parent;
};

#endif // GAMEENGINE_HH
