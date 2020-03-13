#include "labyrinthe.h"


/**
 * \file labyrinthe.c
 * \brief Fichier contenant des fonctions nous permettant de gérer la création et l'affichage du labyrinthe
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/


/***************** PILE ***********/

/**
 * \brief Fonction nous permettant d'initier la pile
 */
void initPile () {
	sommet = -1;
}

/**
 * \brief Fonction nous permettant d'ajouter un élément à la pile
 */
void empiler (int n) {
	if (sommet < TMAX) {
		sommet++;
		pile[sommet] = n;
	}
}

/**
 * \brief Fonction nous permettant d'enlever un élement à la pile
 */
void depiler (int * n) {
	if (sommet > -1) {
		*n = pile[sommet];
		sommet--;
	}
}

/**
 * \brief Fonction nous permettant de savoir si la pile est vide ou non
 * \return 1 si pile vide, 0 sinon
 */
int pileVide () {
	return (sommet == -1);
}


/*************************************/


/**
	\brief Permet d'initialiser une matrice labyrinthe avec que des murs
*/
void initMat (int mat[N][M]) {
	for (int i = 0 ; i < N ; i++) {
		for (int j = 0 ; j < M ; j++) {
			mat[i][j] = MUR;
		}
	}
}


/**
	\brief Permet de générer un labyrinthe de taille N*M (defini dans const.h) à l'aide d'un seed
*/
void ChargerLab(Labyrinthe * labyrinthe) {

	initPile();
	int x = 0, y = 0, i;
	Position choix[4];


	srand(labyrinthe->seed);
	int mat[N][M];
	initMat(mat);
	mat[y][x] = COULOIR;

	empiler(x);
	empiler(y);

	while (!pileVide ()) {

		for (i = 0 ; i < 4 ; i++) {
			choix[i] = None;
		}

		i = 0;

		depiler(&y);
		depiler(&x);

		if (valide(x+2,y) && mat[y][x+2] == MUR) {
			choix[i] = Ouest;
			i++;
		}

		if (valide(x-2,y) && mat[y][x-2] == MUR) {
			choix[i] = Est;
			i++;
		}

		if (valide(x,y+2) && mat[y+2][x] == MUR) {
			choix[i] = Sud;
			i++;
		}

		if (valide(x,y-2) && mat[y-2][x] == MUR) {
			choix[i] = Nord;
			i++;
		}

		if (i >= 1) {
			i = rand()%i;

			empiler(x);
			empiler(y);

			switch (choix[i]) {
				case Nord:
					empiler(x);
					empiler(y-2);
					mat[y-1][x] = COULOIR;
					mat[y-2][x] = COULOIR;
					break;
				case Sud:
					empiler(x);
					empiler(y+2);
					mat[y+2][x] = COULOIR;
					mat[y+1][x] = COULOIR;
					break;
				case Est:
					empiler(x-2);
					empiler(y);
					mat[y][x-2] = COULOIR;
					mat[y][x-1] = COULOIR;
					break;
				case Ouest:
					empiler(x+2);
					empiler(y);
					mat[y][x+2] = COULOIR;
					mat[y][x+1] = COULOIR;
					break;
				default:
					break;
			}
		}

	}

	for (int i = 0 ; i < N ; i++) {
		for (int j = 0 ; j < M ; j++) {
			labyrinthe->mat[i][j] = mat[i][j];
		}
	}

}



/**
	\brief Permet la génération aléatoire du labyrinthe de taille N*M (défini dans const.h)
*/
void initLab(Labyrinthe * labyrinthe) {

	initPile();
	int x = 0, y = 0, i;
	labyrinthe->seed = time(0);
	Position choix[4];


	srand(labyrinthe->seed);
	int mat[N][M];
	initMat(mat);
	mat[y][x] = COULOIR;

	empiler(x);
	empiler(y);

	while (!pileVide ()) {

		for (i = 0 ; i < 4 ; i++) {
			choix[i] = None;
		}

		i = 0;

		depiler(&y);
		depiler(&x);

		if (valide(x+2,y) && mat[y][x+2] == MUR) {
			choix[i] = Ouest;
			i++;
		}

		if (valide(x-2,y) && mat[y][x-2] == MUR) {
			choix[i] = Est;
			i++;
		}

		if (valide(x,y+2) && mat[y+2][x] == MUR) {
			choix[i] = Sud;
			i++;
		}

		if (valide(x,y-2) && mat[y-2][x] == MUR) {
			choix[i] = Nord;
			i++;
		}

		if (i >= 1) {
			i = rand()%i;

			empiler(x);
			empiler(y);

			switch (choix[i]) {
				case Nord:
					empiler(x);
					empiler(y-2);
					mat[y-1][x] = COULOIR;
					mat[y-2][x] = COULOIR;
					break;
				case Sud:
					empiler(x);
					empiler(y+2);
					mat[y+2][x] = COULOIR;
					mat[y+1][x] = COULOIR;
					break;
				case Est:
					empiler(x-2);
					empiler(y);
					mat[y][x-2] = COULOIR;
					mat[y][x-1] = COULOIR;
					break;
				case Ouest:
					empiler(x+2);
					empiler(y);
					mat[y][x+2] = COULOIR;
					mat[y][x+1] = COULOIR;
					break;
				default:
					break;
			}
		}

	}

	for (int i = 0 ; i < N ; i++) {
		for (int j = 0 ; j < M ; j++) {
			labyrinthe->mat[i][j] = mat[i][j];
		}
	}

}


/**
 * \brief Nous permet de savoir quel est la salle la plus éloigner du point de spawn (vas nous servir à savroi dans quel salle faire spawn le boss)
*/
void CheminLePlusLong(Labyrinthe labyrinthe, int * labX, int * labY) {
	int x = 0, y = 0;
	
	int indice = 0;
	int mat[N][M];
	for (int i = 0 ; i < N ; i++) {
		for (int j = 0 ; j < M ; j++) {
			mat[i][j] = 0;
		}
	}
	mat[y][x] = 0;

	initPile();

	empiler(x);
	empiler(y);

	int max = 0, maxX, maxY;

	while (!pileVide()) {

		depiler(&y);
		depiler(&x);
		if (mat[y][x] > max) {
			max = mat[y][x];
			maxX = x;
			maxY = y;
		}
		indice = mat[y][x];

		if (valide(x+1, y) && labyrinthe.mat[y][x+1] == COULOIR && mat[y][x+1] == 0) {
			empiler(x+1);
			empiler(y);
			mat[y][x+1] = indice+1;
		}
		if (valide(x-1, y) && labyrinthe.mat[y][x-1] == COULOIR && mat[y][x-1] == 0) {
			empiler(x-1);
			empiler(y);
			mat[y][x-1] = indice+1;
		}
		if (valide(x, y+1) && labyrinthe.mat[y+1][x] == COULOIR && mat[y+1][x] == 0) {
			empiler(x);
			empiler(y+1);
			mat[y+1][x] = indice+1;
		}
		if (valide(x, y-1) && labyrinthe.mat[y-1][x] == COULOIR && mat[y-1][x] == 0) {
			empiler(x);
			empiler(y-1);
			mat[y-1][x] = indice+1;
		}

	}

	*labX = maxX;
	*labY = maxY;
}



/**
	\brief Permet d'afficher la minimap en prenans en compte les zones visités ou non (pour le brouillard) ainsi que la transparence si le joueur se trouve en dessous
*/
void AfficherMinimap(SDL_Renderer * rendu, Salle salle[N][M], Player player) {

	SDL_Rect rect = {LARGEUR_ECRAN - LARGEUR_MINIMAP - 20, 20, TAILLE_CASE, TAILLE_CASE};
	SDL_Rect rectContour = {LARGEUR_ECRAN - LARGEUR_MINIMAP - 30, 20, 10, HAUTEUR_MINIMAP};
	SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

	int verif = 0;

	//Si coffre sous la minimap
	for (int i = 0 ; i < salle[player.labY][player.labX].nbCoffre ; i++) {
		if (verifMinimap(salle[player.labY][player.labX].coffre[i].salleX, salle[player.labY][player.labX].coffre[i].salleY)) {
			verif = 1;
			break;
		}
	}

	//Si mob sous la minimap
	if (!verif) {
		for (int i = 0 ; i < salle[player.labY][player.labX].nbMonstres ; i++) {
			if (verifMinimap(salle[player.labY][player.labX].monstre[i].salleX, salle[player.labY][player.labX].monstre[i].salleY)) {
				verif = 1;
				break;
			}
		}
	}


	/***********************************  CONTOURS  ******************************************/

	if (verifMinimap(player.salleX, player.salleY) || verif)
		SDL_SetRenderDrawColor(rendu, 150, 150, 150, 100);
	else 
		SDL_SetRenderDrawColor(rendu, 150, 150, 150, 255);


	SDL_RenderFillRect(rendu, &rectContour);
	rectContour.x += LARGEUR_MINIMAP + 10;
	SDL_RenderFillRect(rendu, &rectContour);
	rectContour.x -= LARGEUR_MINIMAP + 10;
	rectContour.y -= 10;
	rectContour.w = LARGEUR_MINIMAP + 20;
	rectContour.h = 10;
	SDL_RenderFillRect(rendu, &rectContour);
	rectContour.y += HAUTEUR_MINIMAP + 10;
	SDL_RenderFillRect(rendu, &rectContour);


	/***********************************  LABYRINTHE  ******************************************/


	for (int i = 0 ; i < N ; i++) {
		for (int j = 0 ; j < M ; j++) {
			if (verifMinimap(player.salleX, player.salleY) || verif) {
				if (salle[i][j].explorer == 1) {
					SDL_SetRenderDrawColor (rendu, 255, 255, 255, 100);;
				}
				else {
					SDL_SetRenderDrawColor (rendu, 0, 0, 0, 100);
				}
			}
			else {
				if (salle[i][j].explorer == 1) {
					SDL_SetRenderDrawColor (rendu, 255, 255, 255, 255);;
				}
				else {
					SDL_SetRenderDrawColor (rendu, 0, 0, 0, 255);
				}
			}
			SDL_RenderFillRect(rendu, &rect);
			rect.x += TAILLE_CASE;
		}
		rect.x = LARGEUR_ECRAN - LARGEUR_MINIMAP - 20;
		rect.y += TAILLE_CASE;
	}

	SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_NONE);

	AfficherPlayerMinimap(rendu, player.labX, player.labY, player.salleX, player.salleY);
}
