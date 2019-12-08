#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

#include <QGraphicsScene>

#include "rod.hh"
#include "plate.hh"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void StartGame();
    void Restart();

private slots:

private:
    Ui::MainWindow *ui_;
    QGraphicsScene* scene_;

    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;

    const int DEFAULT_PIECE_COUNT = 3;
    const int DEFAULT_TOWER_COUNT = 3;

    const int rod1Id = 1;
    const int rod2Id = 2;
    const int rod3Id = 3;


    int pieceCount = DEFAULT_PIECE_COUNT;

};

#endif // MAINWINDOW_HH
