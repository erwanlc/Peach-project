#include "hud.h"
#include "game.h"

#include <QPainter>
#include <QStyleOption>

#include <stdio.h>
#include <iostream>

Hud::Hud(Game * game, int hearts, int coins)
{
    this->game = game;
    this->hearts = hearts;
    this->coins = coins;

    life = QPixmap(":/images/upV.png");
    coin = QPixmap(":/images/coin.png");

    setPos(0,0);
    setZValue(1000000);
}

QRectF Hud::boundingRect() const
{
    return QRectF(0,0,200, 128);
}

void Hud::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::NoBrush);


    //LIFES
    if(hearts >= 1)
    {
        painter->drawPixmap(100,10,life);
    }
    if(hearts >= 2)
    {
        painter->drawPixmap(164,10,life);
    }
    if(hearts >= 3)
    {
        painter->drawPixmap(228,10,life);
    }
    if(hearts >= 4)
    {
        painter->drawPixmap(292,10,life);
    }
    if(hearts >= 5)
    {
        painter->drawPixmap(356,10,life);
    }
    if(hearts >= 6)
    {
        painter->drawPixmap(420,10,life);
    }

    QFont* Text0 = new QFont("Serif",15,QFont::Bold);
    painter->setPen(Qt::white);
    painter->setFont(*Text0);

    //coins
    painter->drawPixmap(0,10,coin);
    QString s = QString::number(coins);
    painter->drawText(50,20,s);

    if(Player::gameOver){
        QFont* Text1 = new QFont("Serif",30,QFont::Bold);
        painter->setPen(Qt::red);
        painter->setFont(*Text1);

        QString gameOver = "GAME OVER";
        painter->drawText(400,450,gameOver);
    }
}

void Hud::advance(int step)
{
    if(!step) return;

    setPos(game->view.mapToScene(game->view.x()+15, game->view.y()+10));

    this->hearts = Player::heart;
    this->coins = Player::nbCoin;

    if (hearts > 6) hearts = 6;

    if (hearts <= 0)
    {
        Player::gameOver=true;
    }
    this->update(this->boundingRect());
}

