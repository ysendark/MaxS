#ifndef __SAVELOAD__
#define __SAVELOAD__

#include "const.h"

/**
 * \file saveload.h
 * \brief Fichier contenant les prototype des fontions nous permettant de gérer la sauvegarde et le chargement de partie
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 09/02/2020
*/

void SauvegarderPartie (const char name[30],Labyrinthe labyrinthe, Player player, Salle salle[N][M]);
void ChargerPartie (const char name[30], Labyrinthe * labyrinthe, Player * player, Salle salle[N][M]);
void ChargerSon();
void SauvegarderSon();

#endif