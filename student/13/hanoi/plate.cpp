#include "plate.hh"
#include <cstdlib>
#include <QColor>



Plate::Plate(int size, QPointF location, QSize pieceSize, QWidget *parent)
    : size_(size),
      x_(static_cast<int>(location.rx())),
      y_(static_cast<int>(location.ry())),
      width_(pieceSize.rwidth()),
      height_(pieceSize.rheight()),
      parent_(parent)

{
    frame = new QRectF(x_,y_,width_, height_);
    setFlag(ItemIsMovable);
}

int Plate::getWidth()
{
    return width_;
}

void Plate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    QColor randomColor(r, g, b);
    QRectF rect = boundingRect();
    QBrush brush(randomColor);

    painter->fillRect(rect, brush);
    painter->drawRect(rect);
}

QRectF Plate::boundingRect() const
{
    return *frame;
}

QWidget *Plate::getParent()
{
    return this->parent_;
}
