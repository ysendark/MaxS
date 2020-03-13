#include "monstre.h"
#include "const.h"
#include <sys/timeb.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>


/**
 * \file monstre.c
 * \brief Fichier contenant des fonctions nous permettant de gérer les monstres
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/

void InitialisationBoss(SDL_Window * screen, Salle * salle, Salle s, Player player) {
	salle->nbMonstres = 1;
	salle->nbCoffre = 0;

	InitMob(screen, &salle->monstre[0], s, player, rand()%300+100, rand()%300+100, rand()%2000+1000, 60, 30, 1);
}


void AfficherMob(SDL_Renderer * rendu, Monstre mob) {

	SDL_SetRenderDrawColor (rendu, mob.r, mob.g, mob.b, 255);
	SDL_Rect monstre = {mob.salleX, mob.salleY, mob.tailleX, mob.tailleY};
	SDL_RenderFillRect(rendu, &monstre);

	float pourcentageVie = (float)mob.hp/mob.hp_max;
	SDL_Rect hpBar = {mob.salleX, mob.salleY-20, mob.tailleX, 10};
	SDL_SetRenderDrawColor (rendu, 0, 0, 0, 255);
	SDL_RenderFillRect(rendu, &hpBar);
	SDL_SetRenderDrawColor (rendu, 255, 0, 0, 255);
	hpBar.w = mob.tailleX * pourcentageVie;
	SDL_RenderFillRect(rendu, &hpBar);
}


int InitPositionMob(Monstre * mob, Salle salle) {
	if ((salle.matTexture[mob->salleY/TAILLE_TILE][mob->salleX/TAILLE_TILE].mur == 1) || (salle.matTexture[(mob->salleY+mob->tailleY)/TAILLE_TILE][(mob->salleX+mob->tailleX)/TAILLE_TILE].mur == 1)) {
		return 1;
	}
	else if ((mob->salleX < 4*TAILLE_TILE) || (mob->salleX > LARGEUR_ECRAN-5*TAILLE_TILE+mob->tailleX)) {
		return 1;
	}
	else if ((mob->salleY < 4*TAILLE_TILE) || (mob->salleY > HAUTEUR_ECRAN-5*TAILLE_TILE+mob->tailleY)) {
		return 1;
	}
	return 0;
}


void InitMob(SDL_Window * screen, Monstre * mob, Salle salle, Player player, int tailleX, int tailleY, int hp, int maxDamage, int minDamage, int boss) {
	
	mob->An = ChargerAnimation(screen, "test.txt");
	
	if (!boss) {
		mob->tailleX = (mob->An->largeurChar-40)*2;
		mob->tailleY = (mob->An->hauteurChar-15)*2;
	}
	else {
		mob->tailleX = tailleX;
		mob->tailleY = tailleY;
	}

	if (!boss) {
		do {
			mob->salleX = rand()%(TAILLE_SALLE_X*TAILLE_TILE);
			mob->salleY = rand()%(TAILLE_SALLE_Y*TAILLE_TILE);
		} while (InitPositionMob(mob, salle));
	}
	else {
		mob->salleX = LARGEUR_ECRAN/2 - mob->tailleX;
		mob->salleY = HAUTEUR_ECRAN/2 - mob->tailleY;
	}

	mob->r = rand()%255;
	mob->g = rand()%255;
	mob->b = rand()%255;

	mob->sp = InitSprite(mob->An, mob->salleX, mob->salleY);

	mob->hp = mob->hp_max = hp;
	mob->vitesse = 1;

	mob->damages = rand()%maxDamage + minDamage;

	mob->bossFinal = boss;

	ftime(&mob->lastAttack);

}


int TimerMob(Monstre * mob) {

	int delay = 1000;

	struct timeb currentAttack;
	ftime(&currentAttack);
	int secondes = (int) difftime(currentAttack.time, mob->lastAttack.time);
	int ms1 = delay - mob->lastAttack.millitm;
    int ms2 = currentAttack.millitm;

	if ((((ms1+ms2) >= delay) && secondes >= 1) || (secondes >= 2)) {
		ftime(&mob->lastAttack);
		return 1;
	}

	return 0;
}


int erreur = 0;
int xincr, yincr;

void DeplacementMonstre(Monstre * mob, Player player) {


	float mobX = mob->salleX+(mob->tailleX/2), mobY = mob->salleY+(mob->tailleY/2);
	float playerX = player.salleX+(player.tailleX/2), playerY = player.salleY+(player.tailleY/2);

	int dY = abs(playerY - mobY);
	int dX = abs(playerX - mobX);

	if (mobX < playerX)
		xincr = mob->vitesse;
	else
		xincr = -mob->vitesse;
	
	if (mobY < playerY) 
		yincr = mob->vitesse;
	else
		yincr = -mob->vitesse;

	if (dX > dY) {
		if (erreur == 0)
			erreur = dX/2;
		mob->salleX += xincr;
		erreur += dY;
		if (erreur > dX) {	
			erreur -= dX;
			mob->salleY += yincr;
		}
	}
	else {
		if (erreur == 0)
			erreur = dY/2;
		mob->salleY += yincr;
		erreur += dX;
		if (erreur > dY) {
			erreur -= dY;
			mob->salleX += xincr;

		}
	}

	mob->sp->stat = marche;
	MouvementSpriteMob(mob->sp, *mob, mob->sp->stat);
	
}