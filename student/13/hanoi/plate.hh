/* Module: Plate
 * ---------------
 * Plate is one plate that holds plate's location, size and color.
 * ---------------
 * Olli Pettersson, olli.pettersson@tuni.fi, 283651
 * */
#ifndef PLATE_HH
#define PLATE_HH

#include <QWidget>
#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QColor>

class Plate:public QGraphicsItem
{
public:
    explicit Plate(int number, QPointF location, QSize plateSize, QWidget* parent = nullptr, QColor color = Qt::red);
    //deletes boundingRect related to plate
    ~Plate() override;
    int getNumber();
    //self-descriptive getters and setters
    QRectF boundingRect() const override;
    void setColor(QColor color);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QRectF* frame;
    //number is used to check if plate can be moved on top of other plate
    int number_;
    int x_;
    int y_;
    int width_;
    int height_;
    QWidget* parent_;
    QColor color_;

};

#endif // PLATE_HH
