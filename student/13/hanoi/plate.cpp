#include "plate.hh"
#include <QColor>
#include <QWidget>

Plate::Plate(int size, int x, int y, int width, int height, QWidget *parent)
: size_(size), x_(x), y_(y), width_(width), height_(height), parent_(parent)

{
  frame = new QRectF(x, y, width, height);
}

Plate::Plate(int size, QPointF location, QSize plateSize, QWidget *parent)
   :size_(size),
    x_(static_cast<int>(location.rx())),
    y_(static_cast<int>(location.ry())),
    width_(plateSize.rwidth()),
    height_(plateSize.rheight()),
    parent_(parent)
{
    frame = new QRectF (x_,y_,width_,height_);
}

int Plate::getSize()
{
    return size_;
}



QRectF Plate::boundingRect() const
{
    return *frame;
}

QWidget *Plate::getParent()
{
    return this->parent_;
}

void Plate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(Qt::red);

    painter->fillRect(rect, brush);
    painter->drawRect(rect);
}
