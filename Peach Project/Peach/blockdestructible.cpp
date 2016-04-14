#include "blockdestructible.h"

BlockDestructible::BlockDestructible(int x, int y):Brique(x,y)
{
    setTextureBlock(QPixmap(":/images/Block_marron.png"));
    this->posX = x;
    this->posY = y;
}

void BlockDestructible::advance(int step)
{
    if (!step) return;
}

