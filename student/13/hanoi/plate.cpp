#include "plate.hh"

Plate::Plate(int number, QPointF location, QSize plateSize, QWidget *parent, QColor color)
   :number_(number),
    x_(location.rx()),
    y_(location.ry()),
    width_(plateSize.rwidth()),
    height_(plateSize.rheight()),
    parent_(parent),
    color_(color)
{
    frame = new QRectF (x_,y_,width_,height_);
}

Plate::~Plate()
{
    delete frame;
}

int Plate::getNumber()
{
    return number_;
}

QRectF Plate::boundingRect() const
{
    return *frame;
}

void Plate::setColor(QColor color)
{
    color_ = color;
}

void Plate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    parent_ = widget;
    QRectF rect = option->exposedRect;
    QBrush brush(color_);

    painter->fillRect(rect, brush);
    painter->drawRect(rect);
}
