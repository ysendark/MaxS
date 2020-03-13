#include "const.h"

/**
 * \file const.c
 * \brief Fichier contenant des fonctions qui nous seront utile dans tout les domaines
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/


/**
 *	\brief Fonction permettant de savoir les coordonnées x et y se trouve bien dans le labyrinthe 
 *	\return Vrai ou Faux
 */
int valide (int x, int y) {
	return ((x >= 0 && x < M) && (y >= 0 && y < N));
}


/**
 *	\brief Fonction permettant de savoir les coordonnées x et y se trouve bien dans la salle 
 *	\return Vrai ou Faux
 */
int valideSalle (int x, int y) {
	return ((x >= 0 && x < LARGEUR_ECRAN-TAILLE_TILE) && (y >= 0 && y < HAUTEUR_ECRAN-TAILLE_TILE));
}


/**
 * \brief Fonction permettant de savoir si les coordonnées x et y se trouve sous la minimap
* \return Vrai ou Faux
*/
int verifMinimap(int x, int y) {
	return (x > TAILLE_SALLE_X*TAILLE_TILE-7*TAILLE_TILE && y < 4*TAILLE_TILE);
}


/**
 * \brief Fonction permettant de savoir si les coordonnées x et y se trouve sous la bar de vie
 * \return Vrai ou Faux
 */
int verifHealthBar(int x, int y) {
	return ((x < 7*TAILLE_TILE) && (y > TAILLE_SALLE_Y*TAILLE_TILE - 4*TAILLE_TILE) && (y < TAILLE_SALLE_Y*TAILLE_TILE));
}