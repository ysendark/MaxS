#ifndef __MENU__
#define __MENU__

#include "const.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


/**
 * \file menu.h
 * \brief Fichier contenant le prototype des fonctions nous permettant de gérer la création et l'affichage des différents menus ainsi que les constantes lié aux menus
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/


/** \brief Nous permet de savoir le nombre de bouton présent sur le menu principal*/
#define NB_BUTTON_MENU_PRINCIPAL 3
/** \brief Nous permet de savoir la taille d'un bouton horizontalement sur le menu principal*/
#define TAILLE_BUTTON_MENU_PRINCIPAL_X 600
/** \brief Nous permet de savoir la taille d'un bouton verticalement sur le menu principal*/
#define TAILLE_BUTTON_MENU_PRINCIPAL_Y 100

/** \brief Nous permet de savoir le nombre de bouton présent sur le menu en jeu*/
#define NB_BUTTON_MENU_IG 3
/** \brief Nous permet de savoir la taille d'un bouton horizontalement sur le menu principal*/
#define TAILLE_BUTTON_MENU_IG_X 450
/** \brief Nous permet de savoir la taille d'un bouton verticalement sur le menu en jeu*/
#define TAILLE_BUTTON_MENU_IG_Y 100

/** Nous permet de savoir dans quel menu nous nous trouvons, pour pouvoir ensuite afficher / gérer en conséquence*/
typedef enum {Aucun, Principal, New, Load, Quit, Save1, Save2, Save3, Setting, Volume, Touches} Menu;
typedef enum {Premier = 1, Resume, ReturnMenu, Quitter, Sauvegarde, Sauvegarde1, Sauvegarde2, Sauvegarde3} MenuIG;


MenuIG choixMenuIG (SDL_Renderer * rendu, TTF_Font * police, MenuIG menuActuel);
void AfficherMenuVolume (SDL_Renderer * rendu, TTF_Font * police);
void AfficherMenuIG(SDL_Renderer * rendu, TTF_Font * police);
void AfficherMenuSauvegardeIG (SDL_Renderer * rendu, TTF_Font * police);
void AfficherMenuPrincipal(SDL_Renderer * rendu, TTF_Font * police);
void AfficherMenuChargerPartie(SDL_Renderer * rendu, TTF_Font * police);
void AfficherMenuSetting(SDL_Renderer * rendu, TTF_Font * police);
void AfficherMenuTouches(SDL_Renderer * rendu, TTF_Font * police);
Menu choixMenu (Menu menuActuel);

#endif