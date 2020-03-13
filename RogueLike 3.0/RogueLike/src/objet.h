#ifndef __OBJET__
#define __OBJET__

#include "const.h"

/**
 * \file objet.h
 * \brief Fichier contenant le prototype des fonctions nous permettant de gérer les objets
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/

void InitObjet (Objet * objet);
void InitObjet_Legendary (Objet * objet);
void InitCoffre(Coffre * coffre, Salle salle);
void AfficherCoffre(SDL_Renderer * rendu, Coffre coffre);
int CollisionCoffre(int pX, int pY, int cX, int cY);

#endif