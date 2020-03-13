#ifndef __MONSTRE__
#define __MONSTRE__

#include "const.h"
#include "perso.h"


/**
 * \file monstre.h
 * \brief Fichier contenant le prototype des fonctions nous permettant de gérer les monstres
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/

void InitialisationBoss(SDL_Window * screen, Salle * salle, Salle s, Player player);
void AfficherMob(SDL_Renderer * rendu, Monstre mob);
void InitMob(SDL_Window * screen, Monstre * mob, Salle salle, Player player, int tailleX, int tailleY, int hp, int maxDamage, int minDamage, int boss);
int TimerMob(Monstre * mob);
void DeplacementMonstre(Monstre * mob, Player player);

#endif