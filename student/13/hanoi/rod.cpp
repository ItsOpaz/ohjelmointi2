#include "rod.hh"
#include <QPointF>

Rod::Rod(int maxPlates, QPoint location, QWidget *parent) :
         maxPlates_(maxPlates), location_(location), parent(parent)
{
    maxPlateWidth = parent->width()/maxPlates_;
    stick = new QRectF(location, QSize(ROD_WIDTH, static_cast<int>(parent->height())*0.8));

}

bool Rod::addPlate(Plate *plateToAdd)
{
    plates.push_back(plateToAdd);
}

void Rod::drawPlates(QGraphicsScene *scene)
{
    for(auto plate : plates){
        scene->addItem(plate);
    }

}

void Rod::removePieceFromTop()
{

}

bool Rod::moveTopPlateTo(Rod *target)
{
    if (plates.size() == 0){
        return false;
    }
    Plate* plateToMove = plates.back();
    if (plateToMove->getWidth() > target->getTopPlate()->getWidth()){
        return false;
    }
    qreal dy = (this->plates.size()-1)*plateToMove->boundingRect().height() - (target->plates.size())*plateToMove->boundingRect().height();
        qreal dx = target->boundingRect().x() - boundingRect().x();
        plateToMove->moveBy(dx, dy);
        //pieceToMove->setPos(dx, dy);
        plateToMove->setParentItem(target);
        target->addPlate(plateToMove);
        this->plates.pop_back();
        return true;
}

Plate *Rod::getTopPlate()
{

}

std::vector<Plate *> Rod::getPlates()
{

}

void Rod::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

QRectF Rod::boundingRect() const
{
    return *stick;
}

