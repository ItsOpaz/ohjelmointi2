#ifndef ROD_HH
#define ROD_HH

#include <QObject>
#include "plate.hh"
#include <QGraphicsScene>
#include <memory>

class Rod : public QGraphicsItem
{
public:
    explicit Rod(int maxPlates, QPoint location, QWidget *parent = nullptr);

    bool addPlate(Plate* plateToAdd);
    void drawPlates(QGraphicsScene* scene);

    void removePieceFromTop();
    bool moveTopPlateTo(Rod* target);

    Plate* getTopPlate();

    std::vector<Plate *> getPlates();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

private:

    const int ROD_WIDTH = 5;
    const int MAX_PIECE_COUNT = 21; // at the rate 1 move per second it takes over 3 months to finish 22 plate hanoi tower,so it's not practical
    std::vector< Plate* > plates;

    QRectF* stick;
    int maxPlates_;
    QPoint location_;
    QWidget* parent;

    int maxPlateWidth;



};
#endif // ROD_HH
