#include "BlockPower.h"

BlockPower::BlockPower(int x, int y):Brique(x,y)
{
    setTextureBlock(QPixmap(":/images/Block_or.png"));
    this->posX = x;
    this->posY = y;
}

void BlockPower::advance(int step)
{
    if (!step) return;
}
