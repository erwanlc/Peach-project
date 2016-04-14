#ifndef BLOCKPOWER_H
#define BLOCKPOWER_H

#include "brique.h"

class BlockPower:public Brique
{
public:
    BlockPower(int x, int y);

protected:
    void advance(int step);

private:
    int posX;
    int posY;
};

#endif // BLOCKPOWER_H
