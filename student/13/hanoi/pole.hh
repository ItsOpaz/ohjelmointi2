/* Module: Pole
 * ---------------
 * Pole holds record of all plates in one pole and determines locations and colors
 * for poles and plates.
 * ---------------
 * Olli Pettersson, olli.pettersson@tuni.fi, 283651
 * */
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
    //deletes boundingRect related to pole
    ~Pole() override;
    //adds plate to top of plates vector
    bool addPlate(Plate* addedPlate);
    //moves plate from plates vector to target poles plates vector if possible
    bool movePlate(Pole* target);
    std::vector <Plate*> getPlates();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    std::vector <Plate*> plates;
private:
    const int POLE_WIDTH = 5;
    std::vector <QColor> colors {Qt::red, Qt::green, Qt::blue};
    QRectF* stick;
    int maxPlates_;
    //id is used to set color for pole
    int id;
    QPoint location_;
    QWidget* parent;
};

#endif // POLE_HH
