#ifndef BLOCKHEART_H
#define BLOCKHEART_H

#include "brique.h"

class BlockHeart:public Brique
{
public:
    BlockHeart(int x, int y);

protected:
    void advance(int step);

private:
    int posX;
    int posY;
};

#endif // BLOCKHEART_H
