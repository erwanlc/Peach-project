#include "gameview.h"

Gameview::Gameview()
{

}

void Gameview::draw(Player *player, int posX, int posY){
    player->pView.setPos(posX, posY);
}
