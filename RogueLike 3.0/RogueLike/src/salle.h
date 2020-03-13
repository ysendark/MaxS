#ifndef __SALLE__
#define __SALLE__


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "const.h"
#include "perso.h"

/**
 * \file salle.h
 * \brief Fichier contenant les prototypes des fonctions nous permettant de gérer la création et l'affichage des salles
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/

void AfficherSalle(SDL_Renderer * rendu, Salle salle, Player player, int levelActuel);
void initSalle(SDL_Window * screen, Salle salle[N][M], int mat[N][M], Player player, int level);


#endif