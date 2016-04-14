#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QMediaPlayer>
#include "enemyview.h"


class Enemy: public QObject,public QGraphicsItem{
    Q_OBJECT
public:
    //enum ENEMY{GOOMBA=0,PLANTE_PIRANHA};
    Enemy(int xPos, int yPos,QString penemy,QList <Enemy *>* pgoombaList);
    ~Enemy();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

protected :
    void advance(int step) Q_DECL_OVERRIDE;
    QPixmap texture;

    void deplacement();
    void collision();

    void playerCollision(QPointF pos);

private:
    qreal speedx;
    QList <QGraphicsItem *> colliding_items;

    QList <Enemy *>* goombaListGoomba;
    EnemyView *eView;

    bool left;
    bool right;
    bool collisionUpwithPlayer;
    QString enemy;
    int animation;

    QVector <QPixmap> animGoomba;
    QMediaPlayer *enemyCrushed; //SOUND

    const static int COLLISION_GOOMBA_SIZE =80;

    const static int TEXTURE_GOOMBA_WIDTH = 80;
    const static int TEXTURE_GOOMBA_HEIGHT = 96;
    const static int COLLISION_GOOMBA_WIDTH = 80;
    const static int COLLISION_GOOMBA_HEIGHT = 96;
    const static int COLLISION_GOOMBA_POSX = 0;
    const static int COLLISION_GOOMBA_POSY = 0;

    const static int TEXTURE_PIRANHA_WIDTH = 132;
    const static int TEXTURE_PIRANHA_HEIGHT = 250;
    const static int COLLISION_PIRANHA_WIDTH = 132;
    const static int COLLISION_PIRANHA_HEIGHT = 250;
    const static int COLLISION_PIRANHA_POSX = 0;
    const static int COLLISION_PIRANHA_POSY = 0;

    void piranhaAttack();

public slots:
    void playerCollisionUp();
};

#endif // ENEMY_H
