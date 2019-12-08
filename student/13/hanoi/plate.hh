#ifndef PLATE_HH
#define PLATE_HH

#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>


class Plate:public QGraphicsItem
{
public:
    explicit Plate(int size, QPointF location, QSize pieceSize, QWidget* parent = nullptr);

    int getWidth();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
        QRectF boundingRect() const override;

        QWidget* getParent();

private:
    QRectF* frame;
    int size_;
    int x_;
    int y_;
    int width_;
    int height_;

    QWidget* parent_;
};

#endif // PLATE_HH
