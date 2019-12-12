#ifndef PLATE_HH
#define PLATE_HH

#include <QWidget>
#include <QGraphicsItem>
#include <QRectF>
#include <memory>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class Plate:public QGraphicsItem
{
public:
    explicit Plate(int size, int x, int y, int width, int height, QWidget *parent = nullptr, QColor color = Qt::red);
    explicit Plate(int size,QPointF location, QSize plateSize, QWidget* parent = nullptr, QColor color = Qt::red);
    ~Plate() override;
    int getSize();
    QRectF boundingRect() const override;
    void setColor(QColor color);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QRectF* frame;
    int size_;
    int x_;
    int y_;
    int width_;
    int height_;
    QWidget* parent_;
    QColor color_;

};

#endif // PLATE_HH
