#ifndef BLOCKDESTRUCTIBLE_H
#define BLOCKDESTRUCTIBLE_H

#include "brique.h"

class BlockDestructible:public Brique
{
public:
    BlockDestructible(int x, int y);

protected:
    void advance(int step);

private:

    int posX;
    int posY;
};

#endif // BLOCKDESTRUCTIBLE_H
