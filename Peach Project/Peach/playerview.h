#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <QWidget>
#include <QImage>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QGraphicsView>
#include <QList>
#include <QMediaPlayer>
#include "power.h"

class playerView:public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    playerView();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    QGraphicsView *view;

public slots:
    void receiveTPsignal(int,int);//Ajout 15/11
signals:
    void collisionDownWithEnemy();

protected:
    void advance(int step) Q_DECL_OVERRIDE;

private:
    const static int TEXTURE_WIDTH = 100;
    const static int TEXTURE_HEIGHT = 187;
    const static int COLLISION_WIDTH = 100;
    const static int COLLISION_HEIGHT = 187;
    const static int COLLISION_POSX = 0;
    const static int COLLISION_POSY = 14;

    qreal speedx;
    qreal speedy;
    qreal gravity;
    qreal posXTmp;
    qreal hitTime;

    QPixmap texture;
    Power *flamme;
    QPointF posCenterOn;

    QList <QGraphicsItem *> colliding_items;

    QMediaPlayer * playerJump;//SOUND
    QMediaPlayer * playerDmg;//SOUND
    QMediaPlayer * win;//SOUND
    const static int HIT_TIME = 1500;

    bool right;
    bool left;
    bool up;
    bool onGround;
    bool onAirRight;
    bool onAirLeft;
    bool rightPossible;
    bool leftPossible;
    bool dress;
    bool fall;
    bool hardFall;
    bool hit;
    bool blockActivated;
    bool direction;
    bool collisionDownTuyau;
    bool tp;                     //Ajout 15/11
    int destinationXTP;          //Ajout 15/11
    int destinationYTP;          //Ajout 15/11

    void blockCollision(QPointF pos);
    void blockSurpriseCollision(QPointF pos);
    void enemyCollision(QPointF pos);
    void blockTPCollision(QPointF pos);         //Ajout 15/11
    void turtleCollision(QPointF pos);

    void deplacement();
    void collision();
    void groundTest();
    void leftTest();
    void rightTest();
    void setTexture();

    void isOnGround();
    QTimer *timerjump;
    int jumptimecounter, x0, y0;

    QPixmap setPlayerViewRight();
    QPixmap setPlayerViewLeft();
    QPixmap setPlayerViewRightDress();
    QPixmap setPlayerViewLeftDress();
    QPixmap setPlayerViewDress();
    QPixmap setPlayerHit();
    QPixmap setPlayerPeachOnFire();
};

#endif // PLAYERVIEW_H
