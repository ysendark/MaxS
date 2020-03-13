#ifndef __ANIMATION__
#define __ANIMATION__

#include "const.h"


void AffichageAnimation(Animation* An, SDL_Renderer * rendu, int sens, int stat, int x, int y);
Animation * ChargerAnimation(SDL_Window * window, const char* fichier);
void LibererAnimation(Animation* An);

#endif