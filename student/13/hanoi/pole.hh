#ifndef POLE_HH
#define POLE_HH

#include <QWidget>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QBrush>
#include <QPoint>
#include <memory>
#include <vector>
#include "plate.hh"

class Pole: public QGraphicsItem
{
public:
    explicit Pole(int maxPlates, int poleID, QPoint location, QWidget* parent=nullptr);
    ~Pole() override;
    bool addPlate(Plate* addedPlate);
    void drawPlates(QGraphicsScene* scene);
    bool movePlate(Pole* target);
    std::vector <Plate*> getPlates();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    const int POLE_WIDTH = 5;
    std::vector <QColor> colors {Qt::red, Qt::green, Qt::blue};
    std::vector <Plate*> plates;
    QRectF* stick;
    int maxPlates_;
    int id;
    QPoint location_;
    QWidget* parent;
    QBrush* brush;
    int maxPieceWidth;
};

#endif // POLE_HH
