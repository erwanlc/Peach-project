#include "Player.h"
#include <QObject>
#include <game.h>


extern Game * game;

int Player::nbCoin = 0;
int Player::heart = 1;
bool Player::power=false;
bool Player::gameOver=false;

Player::Player(QGraphicsView *viewp){
    this->pView.view=viewp;
}

