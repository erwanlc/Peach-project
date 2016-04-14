#include "blockheart.h"

BlockHeart::BlockHeart(int x, int y):Brique(x,y)
{
    setTextureBlock(QPixmap(":/images/Block_or.png"));
    this->posX = x;
    this->posY = y;
}

void BlockHeart::advance(int step)
{
    if (!step) return;
}
