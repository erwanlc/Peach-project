#include "blocksurprise.h"

BlockSurprise::BlockSurprise(int x, int y):Brique(x,y)
{
    setTextureBlock(QPixmap(":/images/Block_or.png"));
    this->posX = x;
    this->posY = y;
}

void BlockSurprise::advance(int step)
{
    if (!step) return;
}
