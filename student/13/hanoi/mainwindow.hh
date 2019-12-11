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
    ~MainWindow() override;
    void keyPressEvent(QKeyEvent* event) override;
    void autoMove();
    GameEngine *game;

private slots:
    void on_startButton_clicked();
    void endGame();
    void tick();

private:
    Ui::MainWindow *ui;

    QTimer timer;
    QGraphicsScene *scene_;
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
};

#endif // MAINWINDOW_HH
