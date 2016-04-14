#ifndef BLOCKSURPRISE_H
#define BLOCKSURPRISE_H

#include "brique.h"

class BlockSurprise:public Brique
{
public:
    BlockSurprise(int x, int y);

protected:
    void advance(int step);

private:

    int posX;
    int posY;
};

#endif // BLOCKSURPRISE_H
