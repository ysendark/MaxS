#ifndef __PERSO__
#define __PERSO__

#include "salle.h"
#include "menu.h"
#include "fevent.h"
#include "labyrinthe.h"
#include "sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * \file perso.h
 * \brief Fichier contenant des fonctions nous permettant de gérer la création, la modification et l'affichage du joueur
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.2
 * \date 04/02/2020
*/

/** \brief Permet de savoir la taille horizontalement de la bar de vie*/
#define HP_BAR_X 300
/** \brief Permet de savoir la taille verticalement de la bar de vie*/
#define HP_BAR_Y 30

/** \brief Permet de savoir le nombre de dégats que fait le joueur par défaut*/
#define PLAYER_DEFAULT_DAMAGE 30
/** \brief Permet de savoir le nombre de points de vies qu'a le joueur par défaut*/
#define PLAYER_DEFAULT_HEALTH 100


void initPlayer(Player * player, SDL_Window * screen, const char f[50], int labX, int labY, int salleX, int salleY);
int ActionSalle(Input * in, SDL_Renderer * rendu, TTF_Font * police, Player * player, Salle salle, int * inGame, int * inMenu, int * levelActuel, Menu * menuActuel, Salle salleSave[N][M], Labyrinthe labyrinthe);
void AfficherPlayerSalle(SDL_Renderer * rendu, Player player);
void AfficherPlayerMinimap(SDL_Renderer * rendu, int x, int y, int px, int py);
void AfficherHUD (SDL_Renderer * rendu, Salle salle[N][M], Player player);
void PassagePorte(Salle salle[N][M], Player * player);
int CollisionMob(int pX, int pY, int pTailleX, int pTailleY, int mX, int mY, int mTailleX, int mTailleY);
void AfficherInventaire(SDL_Renderer * rendu, Inventaire inventaire, TTF_Font * police);
void LibererPlayer(Player * player);


#endif