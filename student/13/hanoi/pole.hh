#ifndef POLE_HH
#define POLE_HH

#include <QWidget>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QPoint>
#include <memory>
#include <vector>
#include "plate.hh"

class Pole: public QGraphicsItem
{
public:
    explicit Pole(int maxPlates, QPoint location, QWidget* parent=nullptr);
    bool addPlate(Plate* addedPlate);
    void drawPlates(QGraphicsScene* scene);
    bool moveToPlate(Pole* target);
    Plate* getTopPlate();
    std::vector <Plate*> getPlates();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    const int POLE_WIDTH = 5;
    std::vector <Plate*> plates;
    QRectF* stick;
    int maxPlates_;
    QPoint location_;
    QWidget* parent;
    int maxPieceWidth;
};

#endif // POLE_HH
