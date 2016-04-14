#ifndef MUSHROOMHEART_H
#define MUSHROOMHEART_H

#include <QObject>
#include <QGraphicsItem>

class MushroomHeart: public QObject,public QGraphicsItem{
    Q_OBJECT
public:
    MushroomHeart(int x, int y, QGraphicsItem * parent=0);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    void advance(int step);

private:
    QPixmap textureMushroomHeart;

    int posY;
    int posYEnd;

    QList <QGraphicsItem *> colliding_items;

    const static int COLLISION_SIZE =60;

    const static int TEXTURE_WIDTH = 60;
    const static int TEXTURE_HEIGHT = 60;

};

#endif // MUSHROOMHEART_H
