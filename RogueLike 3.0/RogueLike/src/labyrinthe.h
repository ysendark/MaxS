#ifndef __LABYRINTHE__
#define __LABYRINTHE__


#include <SDL2/SDL.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "salle.h"
#include "perso.h"
#include "const.h"

/**
 * \file labyrinthe.h
 * \brief Fichier contenant le prototype des fonctions nous permettant de gérer la création et l'affichage du labyrinthe
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/

/** \brief tableau d'entier, nous servant de pile. Sa taille max est défini en constante dans le fichier const.h*/
int pile[TMAX];
/** \brief entier nous servant à identifier le sommet de la pile*/
int sommet;


void CheminLePlusLong(Labyrinthe labyrinthe, int * labX, int * labY);
void AfficherMinimap(SDL_Renderer * rendu, Salle salle[N][M], Player player);
void initMat (int mat[N][M]);
void initLab(Labyrinthe * labyrinthe);
void ChargerLab(Labyrinthe * labyrinthe);
void initPile();
void empiler(int v);
void depiler(int *v);
int pileVide();

#endif
