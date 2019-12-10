#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include "gameengine.hh"
#include "pole.hh"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    GameEngine* game;

    QGraphicsScene* scene_;

    const int NUMBER_OF_POLES = 3;
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;
    const int left_margin = 10;
    const int top_margin = 270;

    std::vector <QString> moves;
};

#endif // MAINWINDOW_HH
