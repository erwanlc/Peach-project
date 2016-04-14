#ifndef HUD_H
#define HUD_H

#include <QGraphicsItem>
#include <QObject>
#include <QDebug>

#include "game.h"

class Hud : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Hud(Game *game,int hearts, int coin);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

//General
    int hearts;
    int coins;
    Game *game;

protected:
    void advance(int step);

private:
//Visual
    QPixmap texture;
    QPixmap life;
    QPixmap coin;

};

#endif // HUD_H
