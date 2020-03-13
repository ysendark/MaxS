#ifndef __EVENT__
#define __EVENT__

#include <SDL2/SDL.h>


/**
 * \file fevent.h
 * \brief Fichier contenant la structure input, ainsi que les prototypes des fonctions nous permettant de gérer ces inputs
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/


/**
	\brief Permet d'avoir toutes les informations sur les touches utilisé par le joueur. Enregistre aussi le fait que le joueur choisi de quitter le jeux
*/
typedef struct {
	char key[SDL_NUM_SCANCODES];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[8];
	char quit;
} Input;


void UpdateEvents(Input* in);
void InitEvents(Input* in);

#endif
