#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsView>
#include "playerview.h"


class Player{
   //Q_OBJECT
public:
    Player(QGraphicsView *viewp);
    playerView pView;
    static int nbCoin;
    static int heart;
    static bool power;
    static bool gameOver;
};

#endif // PLAYER_H
