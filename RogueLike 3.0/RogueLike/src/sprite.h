#ifndef __SPRITE__
#define __SPRITE__

#include "animation.h"


Sprite * InitSprite(Animation * An, int x, int y);
void MouvementSpritePlayer(Sprite * sp, Player player, Status stat);
void MouvementSpriteMob(Sprite * sp, Monstre mob, Status stat);
void LibererSprite (Sprite * sp);

#endif