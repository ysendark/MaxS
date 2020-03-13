#include "sprite.h"
#include <stdlib.h>


void LibererSprite (Sprite * sp) {
    free (sp);
}


Sprite * InitSprite(Animation * An, int x, int y) {
    Sprite * sp = malloc(sizeof(Sprite));
    sp->sens = 1;
    sp->stat = arret;
    sp->anim = An;
    sp->x = x;
    sp->y = y;
    return sp;
}

void MouvementSpritePlayer(Sprite * sp, Player player, Status stat) {

    sp->stat = stat;

    if (player.salleY < sp->y) { 
        sp->sens = 0;
    }
    else if (player.salleX < sp->x) {
        sp->sens = 1;
    }
    else if (player.salleY > sp->y) {
        sp->sens = 2;
    }
    else if (player.salleX > sp->x) {
        sp->sens = 3;
    }
    else { 
        sp->stat = arret;
    }

    sp->x = player.salleX;
    sp->y = player.salleY;
}

void MouvementSpriteMob(Sprite * sp, Monstre mob, Status stat) {

    sp->stat = stat;

    if (mob.salleY < sp->y) { 
        sp->sens = 0;
    }
    else if (mob.salleX < sp->x) {
        sp->sens = 1;
    }
    else if (mob.salleY > sp->y) {
        sp->sens = 2;
    }
    else if (mob.salleX > sp->x) {
        sp->sens = 3;
    }
    else { 
        sp->stat = arret;
    }

    sp->x = mob.salleX;
    sp->y = mob.salleY;
}