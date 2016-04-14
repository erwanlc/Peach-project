#ifndef MARIO_H
#define MARIO_H

#include <QObject>
#include <QGraphicsItem>

class Mario: public QObject,public QGraphicsItem{
    Q_OBJECT
public:
    Mario();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    QPixmap textureMario;

    const static int COLLISION_SIZE =120;

    const static int TEXTURE_WIDTH = 120;
    const static int TEXTURE_HEIGHT = 188;

};


#endif // MARIO_H
