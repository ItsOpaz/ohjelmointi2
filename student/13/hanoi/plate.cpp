#include "plate.hh"
#include <QColor>
#include <QWidget>


Plate::Plate(int size, QPointF location, QSize plateSize, QWidget *parent, QColor color)
   :size_(size),
    x_(static_cast<int>(location.rx())),
    y_(static_cast<int>(location.ry())),
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

int Plate::getSize()
{
    return size_;
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
