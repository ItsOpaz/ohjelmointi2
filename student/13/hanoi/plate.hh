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
#include <memory>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class Plate:public QGraphicsItem
{
public:
    explicit Plate(int size,QPointF location, QSize plateSize, QWidget* parent = nullptr, QColor color = Qt::red);
    //deletes boundingRect related to plate
    ~Plate() override;
    int getSize();
    //self-descriptive getters and setters
    QRectF boundingRect() const override;
    void setColor(QColor color);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QRectF* frame;
    int size_;
    int x_;
    int y_;
    int width_;
    int height_;
    QWidget* parent_;
    QColor color_;

};

#endif // PLATE_HH
