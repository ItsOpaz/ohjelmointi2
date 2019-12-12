#include "pole.hh"
#include "gameengine.hh"
#include <QPointF>
#include <QWidget>
#include <QPainter>

Pole::Pole(int maxPlates,int poleID, QPoint location, QWidget *parent)
    :maxPlates_(maxPlates), id(poleID), location_(location), parent(parent)
{
    stick = new QRectF(location, QSize(POLE_WIDTH, static_cast<int>(parent->height()) * 0.9));
}

Pole::~Pole()
{
    delete stick;
}

bool Pole::addPlate(Plate *addedPlate)
{
    addedPlate->setColor(colors[id]);
    addedPlate->setParentItem(this);
    plates.push_back(addedPlate);
    return true;
}

bool Pole::movePlate(Pole* target)
{
    if (plates.size() == 0) {
        return false;
    }
    Plate* plateToMove = plates.back();
    if(!target->plates.empty()){
        if (plateToMove->getSize() > target->plates.back()->getSize()) {
            return false;
        }
    }
    qreal dy = (this->plates.size()-1)*plateToMove->boundingRect().height() - (target->plates.size())*plateToMove->boundingRect().height();
    qreal dx = target->boundingRect().x() - boundingRect().x();
    plateToMove->moveBy(dx, dy);
    plateToMove->setParentItem(target);
    target->addPlate(plateToMove);
    this->plates.pop_back();
    return true;
}

std::vector<Plate *> Pole::getPlates()
{
    return plates;
}

QRectF Pole::boundingRect() const
{
    return *stick;
}

void Pole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    parent = widget;
    QRectF rect = option->exposedRect;
    QBrush brush(colors[id]);
    painter->fillRect(rect, brush);
    painter->drawRect(rect);

}
