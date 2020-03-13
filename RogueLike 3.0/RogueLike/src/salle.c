#include "salle.h"
#include "monstre.h"
#include "objet.h"

/**
 * \file salle.c
 * \brief Fichier contenant des fonctions nous permettant de gérer la création et l'affichage des salles
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/


/**
	\brief Permet d'initialiser la matrice de type Salle. Si le lieu est un couloir : On vas enregister où se trouve les couloirs à proximité puis indiquer les directions des portes. Si le lieu est un mur : On initialise tout à 0
*/
void initSalle(SDL_Window * screen, Salle salle[N][M], int mat[N][M], Player player, int level) {

	int choix;

	for (int i = 0 ; i < N ; i++) {
		for (int j = 0 ; j < M ; j++) {
			salle[i][j].nbPorte = 0;
			salle[i][j].est = 0;
			salle[i][j].sud = 0;
			salle[i][j].nord = 0;
			salle[i][j].ouest = 0;
			salle[i][j].explorer = 0;
			salle[i][j].nbMonstres = 0;


			for (int k = 0 ; k < TAILLE_SALLE_Y ; k++) {
				for (int p = 0 ; p < TAILLE_SALLE_X ; p++) {
					if (p == 0 || k == 0 || k == (TAILLE_SALLE_Y-1) || p == (TAILLE_SALLE_X-1)) { // = Mur
						salle[i][j].matTexture[k][p].id = 0;
						salle[i][j].matTexture[k][p].mur = 1;
						salle[i][j].matTexture[k][p].degats = 0;
					}
					else { // = Planche
						choix = rand()%4 + 1;
						switch (choix) {
							case 1:
								salle[i][j].matTexture[k][p].id = 1;	
								break;
							case 2:
								salle[i][j].matTexture[k][p].id = 2;
								break;
							case 3:
								salle[i][j].matTexture[k][p].id = 3;
								break;
							case 4:
								salle[i][j].matTexture[k][p].id = 4;
							default:
								break;
						}
						salle[i][j].matTexture[k][p].mur = 0;
						salle[i][j].matTexture[k][p].degats = 0;
					}
				}
			}

			if (mat[i][j] == COULOIR) { //C'est donc une salle
				if (i || j ) { //La premiere salle ne contient n'y monstre n"y coffre
					//On initialise les monstres de la salle
					salle[i][j].nbMonstres = rand()%MAX_MONSTRE + 1;
					for (int k = 0 ; k < salle[i][j].nbMonstres ; k++) {
						InitMob(screen, &salle[i][j].monstre[k], salle[i][j], player, TAILLE_TILE, TAILLE_TILE, 100*level + (level-1)*50, 30*level + (level-1)*10, 5*level + (level-1)*5, 0);
					}	

					//On initialise les coffres de la salle
					salle[i][j].nbCoffre = rand()%MAX_COFFRE;
					for (int k = 0 ; k < salle[i][j].nbCoffre ; k++) {
						InitCoffre(&salle[i][j].coffre[k], salle[i][j]);
					}
				}

				//On compte le nombre de couloir a cote

				if (valide(j, i+1) && mat[i+1][j] == COULOIR) {
					salle[i][j].nbPorte++;
					salle[i][j].sud = 1;
				}
				if (valide(j, i-1) && mat[i-1][j] == COULOIR) {
					salle[i][j].nbPorte++;
					salle[i][j].nord = 1;
				}
				if (valide(j+1, i) && mat[i][j+1] == COULOIR) {
					salle[i][j].nbPorte++;
					salle[i][j].est = 1;
				}
				if (valide(j-1, i) && mat[i][j-1] == COULOIR) {
					salle[i][j].nbPorte++;
					salle[i][j].ouest = 1;
				}

			}
		}
	}
}


/** 
	\brief Permet d'afficher une salle (Zone principal de l'ecran)
*/
void AfficherSalle(SDL_Renderer * rendu, Salle salle, Player player, int levelActuel) {

	SDL_Rect rectHori = {0, 0, 4*TAILLE_TILE, TAILLE_TILE};
	SDL_Rect rectVerti = {0, 0, TAILLE_TILE	, 4*TAILLE_TILE};

	//Fond

	SDL_Surface * mur1 = IMG_Load("./textures/mur1.png");
	SDL_Surface * mur2 = IMG_Load("./textures/mur2.png");
	SDL_Surface * mur3 = IMG_Load("./textures/mur3.png");
	SDL_Surface * mur4 = IMG_Load("./textures/mur4.png");
	SDL_Surface * planche1 = IMG_Load("./textures/planche1.png");
	SDL_Surface * planche2 = IMG_Load("./textures/planche2.png");
	SDL_Surface * planche3 = IMG_Load("./textures/planche3.png");
	SDL_Surface * planche4 = IMG_Load("./textures/planche4.png");

	SDL_Texture * T_planche1 = SDL_CreateTextureFromSurface(rendu, planche1);
	SDL_Texture * T_planche2 = SDL_CreateTextureFromSurface(rendu, planche2);
	SDL_Texture * T_planche3 = SDL_CreateTextureFromSurface(rendu, planche3);
	SDL_Texture * T_planche4 = SDL_CreateTextureFromSurface(rendu, planche4);
	SDL_Texture * T_mur1 = SDL_CreateTextureFromSurface(rendu, mur1);
	SDL_Texture * T_mur2 = SDL_CreateTextureFromSurface(rendu, mur2);
	SDL_Texture * T_mur3 = SDL_CreateTextureFromSurface(rendu, mur3);
	SDL_Texture * T_mur4 = SDL_CreateTextureFromSurface(rendu, mur4);


	SDL_Rect rect = {0, 0, TAILLE_TILE, TAILLE_TILE};

	for (int i = 0 ; i < TAILLE_SALLE_Y ; i++) {
		for (int j = 0 ; j < TAILLE_SALLE_X ; j++) {
			switch (salle.matTexture[i][j].id) {
				case 0:
					switch (levelActuel) { //En fonction du niveau, les murs changent
						case 1:
							SDL_RenderCopy(rendu, T_mur1, NULL, &rect);
							break;
						case 2:
							SDL_RenderCopy(rendu, T_mur2, NULL, &rect);
							break;
						case 3:
							SDL_RenderCopy(rendu, T_mur3, NULL, &rect);
							break;
						case 4:
							SDL_RenderCopy(rendu, T_mur4, NULL, &rect);
							break;
						default:
							break;
					}
					break;
				case 1:
					SDL_RenderCopy(rendu, T_planche1, NULL, &rect);
					break;
				case 2:
					SDL_RenderCopy(rendu, T_planche2, NULL, &rect);
					break;
				case 3:
					SDL_RenderCopy(rendu, T_planche3, NULL, &rect);
					break;
				case 4:
					SDL_RenderCopy(rendu, T_planche4, NULL, &rect);
					break;
				default:
					break;
			}
			rect.x += TAILLE_TILE;
		}
		rect.x = 0;
		rect.y += TAILLE_TILE;
	}

	SDL_DestroyTexture(T_mur1);
	SDL_DestroyTexture(T_mur2);
	SDL_DestroyTexture(T_mur3);
	SDL_DestroyTexture(T_mur4);
	SDL_DestroyTexture(T_planche1);
	SDL_DestroyTexture(T_planche2);
	SDL_DestroyTexture(T_planche3);
	SDL_DestroyTexture(T_planche4);

	SDL_FreeSurface(mur1);
	SDL_FreeSurface(mur2);
	SDL_FreeSurface(mur3);
	SDL_FreeSurface(mur4);
	SDL_FreeSurface(planche1);
	SDL_FreeSurface(planche2);
	SDL_FreeSurface(planche3);
	SDL_FreeSurface(planche4);


	SDL_SetRenderDrawColor (rendu, 20, 20, 20, 255);

	//On va regarder dans quel direction il y a une porte puis afficher les portes aux endroit prevu

	if (salle.sud) {
		rectHori.x = LARGEUR_ECRAN/2 - 2*TAILLE_TILE;
		rectHori.y = HAUTEUR_ECRAN - TAILLE_TILE;
		SDL_RenderFillRect(rendu, &rectHori);
	}

	if (salle.nord) {
		rectHori.x = LARGEUR_ECRAN/2 - 2*TAILLE_TILE;
		rectHori.y = 0;
		SDL_RenderFillRect(rendu, &rectHori);
	}

	if (salle.est) {
		rectVerti.x = LARGEUR_ECRAN - TAILLE_TILE;
		rectVerti.y = HAUTEUR_ECRAN/2 - 2*TAILLE_TILE;
		SDL_RenderFillRect(rendu, &rectVerti);
	}

	if (salle.ouest) {
		rectVerti.x = 0;
		rectVerti.y = HAUTEUR_ECRAN/2 - 2*TAILLE_TILE;
		SDL_RenderFillRect(rendu, &rectVerti);
	}
}
