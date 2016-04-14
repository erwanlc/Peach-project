#include "blocklimit.h"

BlockLimit::BlockLimit(int x, int y):Brique(x,y)
{
    setTextureBlock(QPixmap());
    this->posX = x;
    this->posY = y;
}

void BlockLimit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
