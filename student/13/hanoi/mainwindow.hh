/* Module: MainWindow
 * ---------------
 * MainWindow in which game engine, ui, timer and scene are initialize,
 * All buttons are connected and timer ticks are defined.
 * ---------------
 * Olli Pettersson, olli.pettersson@tuni.fi, 283651
 * */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QWidget>
#include <QTimer>
#include "gameengine.hh"
#include "pole.hh"
#include <QListWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    // Oerridden destructor for mainwindow, that is tied to all other classes destructors
    ~MainWindow() override;
    //key press event used to connect keyboard and QPushButtons
    void keyPressEvent(QKeyEvent* event) override;
    //performs automated move
    void autoMove();
    GameEngine *game = nullptr;

private slots:
    //starts normal game
    void on_startButton_clicked();
    //ends game and notices user
    void endGame();
    //counts ticks for timer and automated game
    void tick();
    //starts automated game
    void on_autoGame_clicked();

private:
    Ui::MainWindow *ui;
    QTimer timer;
    QGraphicsScene *scene_;
    //vector of keys wanted to link to pushbuttons
    std::vector<Qt::Key> keys = {Qt::Key_Q, Qt::Key_W, Qt::Key_E,
                                 Qt::Key_R, Qt::Key_T, Qt::Key_Y};
    const int NUMBER_OF_POLES = 3;
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;
    const int left_margin = 10;
    const int top_margin = 270;
    int autoCounter = 0;
    int secs = 0;
    int mins = 0;
    int minMoves;
    int moveCounter = 0;
    bool automated = false;
};

#endif // MAINWINDOW_HH
