#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QWidget>
#include <player.h>

class Gameview
{
public:
    Gameview();
    void draw(Player *player, int posX, int posY);
signals:

public slots:
};

#endif // GAMEVIEW_H
