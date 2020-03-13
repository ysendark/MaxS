#include "fevent.h"
#include "stdlib.h"


/**
 * \file fevent.c
 * \brief Fichier contenant des fonctions qui vont nous permettre de gérer les évenements générer par l'utilisateur (clavier, souris...)
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/


/**
 * \brief Fonction permettant de remplir une structure Input en fonction des input détécter
 */
void UpdateEvents(Input* in) {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN: //Si appuie sur une touche alors on l'enregistre dans la struct Input 
			if (event.key.keysym.sym <= SDLK_z)
				in->key[event.key.keysym.sym]=1;
			break;
		case SDL_KEYUP: //Si on relache une touche alors sa valeur dans la struct Input redevient 0
			if (event.key.keysym.sym <= SDLK_z) 
				in->key[event.key.keysym.sym]=0;
			break;
		case SDL_MOUSEMOTION: //Enregistre les mouvements de souris dans la structure Input
			in->mousex=event.motion.x;
			in->mousey=event.motion.y;
			in->mousexrel=event.motion.xrel;
			in->mouseyrel=event.motion.yrel;
			break;
		case SDL_MOUSEBUTTONDOWN: //Enregistre l'appuie d'un clic souri
			in->mousebuttons[event.button.button]=1;
			break;
		case SDL_MOUSEBUTTONUP: //Enregistre le relachement d'un clic souri
			in->mousebuttons[event.button.button]=0;
			break;
		case SDL_QUIT: //Si l'on clique sur le bouton fermeture de fenetre
			in->quit = 1;
			break;
		default:
			break;
		}
	}
}


/**
	\brief Permet d'initialiser une structure input
*/
void InitEvents(Input* in) {
	// == malloc avec valeur initialisé à 0
	memset(in,0,sizeof(Input));
}

