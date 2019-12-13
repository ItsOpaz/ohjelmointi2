#include "pole.hh"
#include "gameengine.hh"

Pole::Pole(int poleID, QPoint location, QWidget *parent)
    : id(poleID), location_(location), parent(parent)
{
    //height is multiplied by 0.8 for better visuals
    stick = new QRectF(location, QSize(POLE_WIDTH, parent->height()*0.8));
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
        if (plateToMove->getNumber() > target->plates.back()->getNumber()) {
            return false;
        }
    }
    plates.pop_back();
    //y difference is plate position minus target poles top plate position
    qreal dy = (plateToMove->boundingRect().height() * (plates.size())
                - plateToMove->boundingRect().height() * target->plates.size());
    //x difference is distance between poles
    qreal dx = target->location_.rx() - location_.rx();
    plateToMove->moveBy(dx, dy);
    plateToMove->setParentItem(target);
    target->addPlate(plateToMove);
    return true;
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
