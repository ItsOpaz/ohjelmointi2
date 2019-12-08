#include "pole.hh"
#include <QPointF>
#include <QWidget>

Pole::Pole(int maxPlates, QPoint location, QWidget *parent)
    :maxPlates_(maxPlates), location_(location), parent(parent)
{
    stick = new QRectF(location, QSize(POLE_WIDTH, static_cast<int>(parent->height()) * 0.9));
}

bool Pole::addPlate(Plate *addedPlate)
{
    plates.push_back(addedPlate);
    return true;
}

void Pole::drawPlates(QGraphicsScene* scene)
{
    for(auto plate : plates){
        scene->addItem(plate);
    }
}

bool Pole::movePlate(Pole* target)
{
    if (plates.size() == 0) {
        return false;
    }

    Plate* plateToMove = plates.back();

    if (plateToMove->getSize() > target->getTopPlate()->getSize()) {
        return false;
    }


    qreal dy = (this->plates.size()-1)*plateToMove->boundingRect().height() - (target->plates.size())*plateToMove->boundingRect().height();
    qreal dx = target->boundingRect().x() - boundingRect().x();

    plateToMove->moveBy(dx, dy);
    plateToMove->setParentItem(target);

    target->addPlate(plateToMove);
    this->plates.pop_back();
    return true;

}

Plate *Pole::getTopPlate()
{
    if (plates.size()==0){
        return new Plate(maxPlates_, 0,0,0,0, parent);
    }
    return plates.back();
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
    QRectF rect = boundingRect();
    QBrush brush(Qt::blue);

    painter->fillRect(rect, brush);
    painter->drawRect(rect);
}
