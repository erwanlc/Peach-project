#ifndef TURTLE_H
#define TURTLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QMediaPlayer>
#include "TurtleView.h"


class Turtle: public QObject,public QGraphicsItem{
    Q_OBJECT
public:

    Turtle(int xPos, int yPos);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

protected :
    void advance(int step) Q_DECL_OVERRIDE;

    void deplacement();
    void collision();

    void playerCollision(QPointF pos);

private:
    qreal speedx;
    QList <QGraphicsItem *> colliding_items;

    TurtleView *tView;

    bool left;
    bool right;
    bool collisionUpwithPlayer;
    bool shell;

    int animation;

    QVector <QPixmap> animTurtle;
    QPixmap textureTurtle;
    QPixmap textureShellR;
    QPixmap textureShellL;

    QMediaPlayer *turtleCrushed; //SOUND

    const static int COLLISION_TURTLE_SIZE =100;

    const static int TEXTURE_TURTLE_WIDTH = 100;
    const static int TEXTURE_TURTLE_HEIGHT = 80;
    const static int COLLISION_TURTLE_WIDTH = 100;
    const static int COLLISION_TURTLE_HEIGHT = 80;

    const static int HIT_TIME = 1500;
    qreal hitTime;
    bool hit;

public slots:
    void playerCollisionUp();
};

#endif // TURTLE_H
