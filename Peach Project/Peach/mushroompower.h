#ifndef MUSHROOMPOWER_H
#define MUSHROOMPOWER_H

#include <QObject>
#include <QGraphicsItem>

class MushroomPower: public QObject,public QGraphicsItem{
    Q_OBJECT
public:
    MushroomPower(int x, int y, QGraphicsItem * parent=0);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    void advance(int step);

private:
    QPixmap textureMushroomPower;

    int posY;
    int posYEnd;

    QList <QGraphicsItem *> colliding_items;

    const static int COLLISION_SIZE =60;

    const static int TEXTURE_WIDTH = 60;
    const static int TEXTURE_HEIGHT = 60;

};

#endif // MUSHROOMPOWER_H
