#ifndef PLATE_HH
#define PLATE_HH

#include <QWidget>
#include <QGraphicsItem>
#include <QRectF>
#include <memory>
#include <QPainter>

class Plate:public QGraphicsItem
{
public:
    explicit Plate(int size, int x, int y, int width, int height, QWidget *parent = nullptr);
    explicit Plate(int size,QPointF location, QSize plateSize, QWidget* parent = nullptr);
    ~Plate() override;
    int getSize();

    QRectF boundingRect() const override;

    QWidget* getParent();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QRectF* frame;
    int size_;
    int x_;
    int y_;
    int width_;
    int height_;
    QWidget* parent_;
    QBrush* brush;
};

#endif // PLATE_HH
