#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Normally this member should be in private part of the
    // class, but due to the automated tests it must be more
    // accessible.
    QTimer timer;
    void tickSimulator();

private slots:
    // Add your slots here

private:
    Ui::MainWindow *ui;
    int secs = 0;
    int mins = 0;
    // Add other necessary members here
};

#endif // MAINWINDOW_HH
