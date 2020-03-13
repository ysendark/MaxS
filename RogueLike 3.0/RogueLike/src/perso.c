#include "perso.h"
#include "menu.h"
#include "saveload.h"
#include "objet.h"
#include <unistd.h>
#include <time.h>
#include "son.h"
#include "sprite.h"

/**
 * \file perso.c
 * \brief Fichier contenant des fonctions nous permettant de gérer la création, la modification et l'affichage du joueur
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.2
 * \date 04/02/2020
*/



/**
 * \brief Permet de lancer la musique du boss final du niveau
 */
void PassageBossFinal() {
	
	if (sound != NULL) {
		Mix_FreeMusic(sound);
		sound = NULL;
	}

	sound = Mix_LoadMUS("./sounds/boss.wav");
	Mix_PlayMusic(sound, 1);
}



/**
 * \brief Permet de gerer le delay entre chaque attaque du joueur
*/
int TimerAttackPlayer(Player * player) {

	int delay = 430;

	struct timeb currentAttack;
	ftime(&currentAttack);
	int secondes = (int) difftime(currentAttack.time, player->lastAttack.time);
	int ms1 = 1000 - player->lastAttack.millitm;
    int ms2 = currentAttack.millitm;

	if ((((ms1+ms2) >= delay) && secondes >= 1) || (secondes >= 2) || ((ms2-(-ms1+1000)) >= delay && (secondes == 0))) {
		ftime(&player->lastAttack);
		return 1;
	}

	return 0;
}


/**
	\brief Permet de gérer l'évènement "attaquer"
*/
void AttaquePlayer (SDL_Renderer * rendu, Player * player, Salle * salle, Salle s) {
	for (int i = 0 ; i < salle->nbMonstres ; i++) {
		if (((salle->monstre[i].salleX+salle->monstre[i].tailleX >= (player->salleX-player->tailleX-5)) && (salle->monstre[i].salleX <= (player->salleX+2*player->tailleX))) && ((salle->monstre[i].salleY+salle->monstre[i].tailleY >= (player->salleY-player->tailleY-5)) && (salle->monstre[i].salleY <= (player->salleY+2*player->tailleY)))){
			if (!salle->monstre[i].bossFinal) {
				if (sound != NULL) {
					Mix_FreeMusic(sound);
					sound = NULL;
				}

				sound = Mix_LoadMUS("./sounds/hit.wav");
				Mix_PlayMusic(sound, 1);
			}
			salle->monstre[i].hp -= player->damage;
			if (salle->monstre[i].hp <= 0) {
				if (salle->monstre[i].bossFinal) { //Si on a tuer le boss
					salle->coffre[salle->nbCoffre].legendary = 1;
					salle->coffre[salle->nbCoffre].salleX = salle->monstre[i].salleX + (salle->monstre[i].tailleX/2);
					salle->coffre[salle->nbCoffre].salleY = salle->monstre[i].salleY + (salle->monstre[i].tailleY/2);
					salle->coffre[salle->nbCoffre].ouvert = 0;
					salle->nbCoffre++;
					if (sound != NULL) {
						Mix_FreeMusic(sound);
						sound = NULL;
					}
				}
				LibererAnimation(salle->monstre[i].An);
				LibererSprite(salle->monstre[i].sp);
				for (int j = i ; j < (salle->nbMonstres-1) ; j++) {
					salle->monstre[j] = salle->monstre[j+1];
				}
				salle->nbMonstres--;
				player->hp += 10;
				if (player->hp > player->hp_max) {
					player->hp = player->hp_max;
				}

			}
		}
	}

}


/**
 * \brief Permet d'afficher l'inventaire du joueur
*/
void AfficherInventaire(SDL_Renderer * rendu, Inventaire inventaire, TTF_Font * police) {

	SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);
	SDL_Rect fond = {5, 90, 200, 600};
	SDL_SetRenderDrawColor (rendu, 50, 50, 50, 120);
	SDL_RenderFillRect(rendu, &fond);

	SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);

    char t[50];
	SDL_Color couleur = {255, 255, 255};
    SDL_Surface * texte;
    SDL_Texture * texture;

	SDL_Rect rect = {15, 100, 30, 30};
	for (int i = 0 ; i < inventaire.nb_objet ; i++) {
		SDL_SetRenderDrawColor (rendu, inventaire.objet[i].r, inventaire.objet[i].g, inventaire.objet[i].b, 255);
		SDL_RenderFillRect(rendu, &rect);
		
		rect.x += 75;
		sprintf(t, "%d    %d", inventaire.objet[i].attaque, inventaire.objet[i].def);
		texte = TTF_RenderText_Solid(police, t, couleur);
		texture = SDL_CreateTextureFromSurface(rendu, texte);
		//SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
		rect.w *= 2;
		SDL_RenderCopy(rendu, texture, NULL, &rect);
		
		rect.x -= 75;
		rect.y += 35;
		rect.w = 30;
		rect.h = 30;

		SDL_DestroyTexture(texture);
    	SDL_FreeSurface(texte);
	}
}



/**
	\brief Permet de gerer le mouvement du personnage dans une salle
*/
int ActionSalle(Input * in, SDL_Renderer * rendu, TTF_Font * police, Player * player, Salle salle, int * inGame, int * inMenu, int * levelActuel, Menu * menuActuel, Salle salleSave[N][M], Labyrinthe labyrinthe) {

	int vitesse = 2;

	if (in->key[SDLK_ESCAPE]) {
		int menuIG = 1;
		MenuIG actuel = Premier;
		MenuIG choix;
		AfficherMenuIG(rendu,police);
		while (menuIG) {
			choix = choixMenuIG(rendu,police,actuel);
			switch (choix) {
				case Resume:
					menuIG = 0;
					break;
				case ReturnMenu:
					*inMenu = 1;
					*inGame = 0;
					*menuActuel = Principal;
					menuIG = 0;
					break;
				case Quitter:
					in->quit = 1;
					menuIG = 0;
					break;
				case Sauvegarde:
					AfficherSalle(rendu, salleSave[player->labY][player->labX], *player, *levelActuel);
					AfficherPlayerSalle(rendu, *player);
					AfficherMinimap(rendu, salleSave, *player);
					AfficherHUD(rendu, salleSave, *player);
					AfficherMenuSauvegardeIG(rendu,police);
					actuel = Sauvegarde;
					break;
				case Sauvegarde1:
					SauvegarderPartie("./saves/Save1.txt", labyrinthe, *player, salleSave);
					AfficherSalle(rendu, salleSave[player->labY][player->labX], *player, *levelActuel);
					AfficherPlayerSalle(rendu, *player);
					AfficherMinimap(rendu, salleSave, *player);
					AfficherHUD(rendu, salleSave, *player);
					AfficherMenuIG(rendu,police);
					actuel = Premier;
					break;
				case Sauvegarde2:
					SauvegarderPartie("./saves/Save2.txt", labyrinthe, *player, salleSave);
					AfficherSalle(rendu, salleSave[player->labY][player->labX], *player, *levelActuel);
					AfficherPlayerSalle(rendu, *player);
					AfficherMinimap(rendu, salleSave, *player);
					AfficherHUD(rendu, salleSave, *player);
					AfficherMenuIG(rendu,police);
					actuel = Premier;
					break;
				case Sauvegarde3:
					SauvegarderPartie("./saves/Save3.txt", labyrinthe, *player, salleSave);
					AfficherSalle(rendu, salleSave[player->labY][player->labX], *player, *levelActuel);
					AfficherPlayerSalle(rendu, *player);
					AfficherMinimap(rendu, salleSave, *player);
					AfficherHUD(rendu, salleSave, *player);
					AfficherMenuIG(rendu,police);
					actuel = Premier;
					break;
				case Premier:
					AfficherSalle(rendu, salleSave[player->labY][player->labX], *player, *levelActuel);
					AfficherPlayerSalle(rendu, *player);
					AfficherMinimap(rendu, salleSave, *player);
					AfficherHUD(rendu, salleSave, *player);
					AfficherMenuIG(rendu,police);
					actuel = Premier;
					break;
				default:
					break;
			}
		}


		in->key[SDLK_ESCAPE] = 0;
		in->key[SDLK_z] = 0;
		in->key[SDLK_d] = 0;
		in->key[SDLK_s] = 0;
		in->key[SDLK_q] = 0;
	}

	int passZ = 0, passS = 0, passD = 0, passQ = 0;
	for (int i = 0 ; i < salle.nbMonstres ; i++) {
		if ((valideSalle(player->salleX, player->salleY-vitesse)) && !CollisionMob(player->salleX, player->salleY-vitesse, player->tailleX, player->tailleY, salle.monstre[i].salleX, salle.monstre[i].salleY, salle.monstre[i].tailleX, salle.monstre[i].tailleY))
			passZ++;
		if ((valideSalle(player->salleX, player->salleY+vitesse+player->tailleY)) && !CollisionMob(player->salleX, player->salleY+vitesse, player->tailleX, player->tailleY, salle.monstre[i].salleX, salle.monstre[i].salleY, salle.monstre[i].tailleX, salle.monstre[i].tailleY))
			passS++;
		if ((valideSalle(player->salleX-vitesse, player->salleY)) && !CollisionMob(player->salleX-vitesse, player->salleY, player->tailleX, player->tailleY, salle.monstre[i].salleX, salle.monstre[i].salleY, salle.monstre[i].tailleX, salle.monstre[i].tailleY))
			passQ++;
		if ((valideSalle(player->salleX+vitesse, player->salleY+player->tailleX)) && !CollisionMob(player->salleX+vitesse, player->salleY, player->tailleX, player->tailleY, salle.monstre[i].salleX, salle.monstre[i].salleY, salle.monstre[i].tailleX, salle.monstre[i].tailleY))
			passD++;
	}

	if (in->key[SDLK_z]) {
		if (passZ == salle.nbMonstres && !salle.matTexture[(player->salleY-vitesse)/TAILLE_TILE][player->salleX/TAILLE_TILE].mur)
			player->salleY -= vitesse;
	}
	if (in->key[SDLK_s]) {
		if (passS == salle.nbMonstres && !salle.matTexture[(player->salleY+player->tailleY)/TAILLE_TILE][player->salleX/TAILLE_TILE].mur)
			player->salleY += vitesse;
	}
	if (in->key[SDLK_q]) {
		if (passQ == salle.nbMonstres && !salle.matTexture[player->salleY/TAILLE_TILE][(player->salleX-vitesse)/TAILLE_TILE].mur)
			player->salleX -= vitesse;
	}
	if (in->key[SDLK_d]) {
		if (passD == salle.nbMonstres && !salle.matTexture[player->salleY/TAILLE_TILE][(player->salleX+player->tailleX)/TAILLE_TILE].mur)
			player->salleX += vitesse;
	}

	player->sp->stat = marche;
	MouvementSpritePlayer(player->sp, *player, player->sp->stat);


	if (in->key[SDLK_p]) {
		if (*levelActuel + 1 <= 4) {
			*levelActuel += 1;
			sleep(1);
		}
	}
	if (in->key[SDLK_o]) {
		if (*levelActuel - 1 >= 1) {
			*levelActuel -= 1;
			sleep(1);
		}
	}

	if (in->key[SDLK_f]) {
		for (int i = 0 ; i < salleSave[player->labY][player->labX].nbCoffre ; i++) {
			if (CollisionCoffre(player->salleX, player->salleY, salleSave[player->labY][player->labX].coffre[i].salleX, salleSave[player->labY][player->labX].coffre[i].salleY) && !salleSave[player->labY][player->labX].coffre[i].ouvert) {
				salleSave[player->labY][player->labX].coffre[i].ouvert = 1;
				if (salleSave[player->labY][player->labX].coffre[i].legendary) {
					InitObjet_Legendary(&player->inventaire.objet[player->inventaire.nb_objet]);
					*levelActuel += 1;
					AfficherCoffre(rendu, salleSave[player->labY][player->labX].coffre[i]);
					SDL_RenderPresent(rendu);
					sleep(1);
					return 1;
				}
				else {
					InitObjet(&player->inventaire.objet[player->inventaire.nb_objet]);
				}
				player->damage += player->inventaire.objet[player->inventaire.nb_objet].attaque;
				player->def += player->inventaire.objet[player->inventaire.nb_objet].def;
				player->inventaire.nb_objet++;
			}
		}
	}


	if (in->mousebuttons[SDL_BUTTON_LEFT] && TimerAttackPlayer(player)) {
		AttaquePlayer(rendu, player,&salleSave[player->labY][player->labX], salle);
		SDL_RenderPresent(rendu);
	}
	return 0;
}



/**
    \brief Permet d'afficher la joueur sur la minimap à la position x - y
*/
void AfficherPlayerMinimap(SDL_Renderer * rendu, int x, int y, int px, int py) {

	SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

	if (verifMinimap(px,py)) {
		SDL_SetRenderDrawColor (rendu, 0, 255, 255, 100);;
	}
	else {
		SDL_SetRenderDrawColor (rendu, 0, 255, 255, 255);
	}


	SDL_Rect player = {LARGEUR_ECRAN - LARGEUR_MINIMAP - 20 + x*TAILLE_CASE + TAILLE_CASE/4, 20 + y*TAILLE_CASE + TAILLE_CASE/4, TAILLE_CASE/2, TAILLE_CASE/2};
	SDL_RenderFillRect(rendu, &player);

}


/**
    \brief Permet d'afficher la joueur dans la salle à la position x - y
*/
void AfficherPlayerSalle(SDL_Renderer * rendu, Player player) {

	SDL_SetRenderDrawColor (rendu, 0, 255, 255, 255);

	SDL_Rect rect = {player.salleX, player.salleY, player.tailleX, player.tailleY};
	SDL_RenderFillRect(rendu, &rect);
}


/**
	\brief Fonction permettant à un joueur de passer d'une salle a une autre. Permet également de mettre à jour la minimap en ajoutant la salle comme explorer
*/
void PassagePorte(Salle salle[N][M], Player * player) {

	int boxCollision = TAILLE_TILE;
	
	if (!(salle[player->labY][player->labX].nbMonstres == 1 && salle[player->labY][player->labX].monstre[0].bossFinal) || GOD_MOD) { //Si on est dans la salle du boss, et qu'il est toujours en vie alors on peu pas revenir en arriere
		if (salle[player->labY][player->labX].est == 1) { //Si il y a une porte a est
			if (!salle[player->labY][player->labX].nbMonstres || salle[player->labY][player->labX].explorer || GOD_MOD) {
				if ((player->salleX >= LARGEUR_ECRAN-player->tailleX-boxCollision) && (player->salleX <= LARGEUR_ECRAN) && (player->salleY >= HAUTEUR_ECRAN/2-2*TAILLE_TILE-boxCollision) && (player->salleY <= ((HAUTEUR_ECRAN/2+2*TAILLE_TILE+boxCollision)))) {
					player->labX += 1;
					player->salleX = 2*TAILLE_TILE;
					player->salleY = HAUTEUR_ECRAN/2;
					salle[player->labY][player->labX].explorer = 1;
					if (salle[player->labY][player->labX].nbMonstres && salle[player->labY][player->labX].monstre[0].bossFinal) {
						PassageBossFinal();
					}
				}
			}
		}

		//Si il y a une porte a ouest
		if (salle[player->labY][player->labX].ouest == 1) {
			if (!salle[player->labY][player->labX].nbMonstres || salle[player->labY][player->labX].explorer || GOD_MOD) {
				if ((player->salleX>= 0) && (player->salleX <= TAILLE_TILE+1) && (player->salleY >= (HAUTEUR_ECRAN/2-2*TAILLE_TILE-boxCollision)) && (player->salleY <= (HAUTEUR_ECRAN/2+2*TAILLE_TILE))) {
					player->labX -= 1;
					player->salleX = LARGEUR_ECRAN - 4*TAILLE_TILE;
					player->salleY = HAUTEUR_ECRAN/2;
					salle[player->labY][player->labX].explorer = 1;
					if (salle[player->labY][player->labX].nbMonstres && salle[player->labY][player->labX].monstre[0].bossFinal) {
						PassageBossFinal();
					}
				}
			}
		}

		//Si il y a une porte a sud
		if (salle[player->labY][player->labX].sud == 1) {
			if (!salle[player->labY][player->labX].nbMonstres || salle[player->labY][player->labX].explorer || GOD_MOD) {
				if ((player->salleY >= HAUTEUR_ECRAN-player->tailleY-boxCollision) && (player->salleY <= HAUTEUR_ECRAN) && (player->salleX >= (LARGEUR_ECRAN/2-2*TAILLE_TILE)-boxCollision) && (player->salleX <= (LARGEUR_ECRAN/2+2*TAILLE_TILE)-1)) {
					player->labY += 1;
					player->salleX = LARGEUR_ECRAN/2;
					player->salleY = 2*TAILLE_TILE;
					salle[player->labY][player->labX].explorer = 1;
					if (salle[player->labY][player->labX].nbMonstres && salle[player->labY][player->labX].monstre[0].bossFinal) {
						PassageBossFinal();
					}
				}
			}
		}

		//Si il y a une porte a nord
		if (salle[player->labY][player->labX].nord == 1) {
			if (!salle[player->labY][player->labX].nbMonstres || salle[player->labY][player->labX].explorer || GOD_MOD) {
				if ((player->salleY >= 0) && (player->salleY <= TAILLE_TILE+1) && (player->salleX >= (LARGEUR_ECRAN/2-2*TAILLE_TILE)-boxCollision) && (player->salleX <= (LARGEUR_ECRAN/2+2*TAILLE_TILE)-1)) {
					player->labY -= 1;
					player->salleX = LARGEUR_ECRAN/2;
					player->salleY = HAUTEUR_ECRAN - 4*TAILLE_TILE;
					salle[player->labY][player->labX].explorer = 1;
					if (salle[player->labY][player->labX].nbMonstres && salle[player->labY][player->labX].monstre[0].bossFinal) {
						PassageBossFinal();
					}
				}
			}
		}
	}
	
}




/**
	\brief Permet d'afficher l'HUD (Head Up Display). Ceci permet au joueur d'avoir les informations les plus utiles à porter de main (comme par exemple sa barre de vie)
*/
void AfficherHUD (SDL_Renderer * rendu, Salle salle[N][M], Player player) {

	SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

	int verif = 0;

	//Si coffre sous la minimap
	for (int i = 0 ; i < salle[player.labY][player.labX].nbCoffre ; i++) {
		if (verifHealthBar(salle[player.labY][player.labX].coffre[i].salleX, salle[player.labY][player.labX].coffre[i].salleY)) {
			verif = 1;
			break;
		}
	}

	//Si mob sous la minimap
	if (!verif) {
		for (int i = 0 ; i < salle[player.labY][player.labX].nbMonstres ; i++) {
			if (verifHealthBar(salle[player.labY][player.labX].monstre[i].salleX, salle[player.labY][player.labX].monstre[i].salleY)) {
				verif = 1;
				break;
			}
		}
	}

	if (verifHealthBar(player.salleX, player.salleY) || verif) {
		SDL_SetRenderDrawColor (rendu, 150, 150, 150, 100);
	}
	else {
		SDL_SetRenderDrawColor (rendu, 150, 150, 150, 255);
	}

	int contours = 5;
	SDL_Rect rect = {20-contours, HAUTEUR_ECRAN - 100 - contours, contours, HP_BAR_Y+(contours*2)};
	SDL_RenderFillRect(rendu, &rect);
	rect.x += HP_BAR_X + contours;
	SDL_RenderFillRect(rendu, &rect);

	rect.x -= HP_BAR_X;
	rect.h = contours;
	rect.w = HP_BAR_X;
	SDL_RenderFillRect(rendu, &rect);
	rect.y += HP_BAR_Y + contours;
	SDL_RenderFillRect(rendu, &rect);



	float pourcentageVie = (float)player.hp/player.hp_max;
	if (verifHealthBar(player.salleX, player.salleY) || verif) {
		SDL_SetRenderDrawColor (rendu, 0, 0, 0, 100);
	}
	else {
		SDL_SetRenderDrawColor (rendu, 0, 0, 0, 255);
	}

	SDL_Rect hpBar = {20, HAUTEUR_ECRAN - 100, HP_BAR_X, HP_BAR_Y};

	SDL_RenderFillRect(rendu, &hpBar);

	if (verifHealthBar(player.salleX, player.salleY) || verif) {
		SDL_SetRenderDrawColor (rendu, 0, 255, 0, 100);
	}
	else {
		SDL_SetRenderDrawColor (rendu, 0, 255, 0, 255);
	}

	hpBar.w = HP_BAR_X * pourcentageVie;
	SDL_RenderFillRect(rendu, &hpBar);

}	


/**
	\brief Permet d'initialiser une structure player
*/
void initPlayer(Player * player, SDL_Window *screen, const char f[50], int labX, int labY, int salleX, int salleY) {
	player->An = ChargerAnimation(screen, f);
	player->damage = PLAYER_DEFAULT_DAMAGE;
	player->hp = PLAYER_DEFAULT_HEALTH;
	player->hp_max = PLAYER_DEFAULT_HEALTH;
	player->labX = labX;
	player->labY = labY;
	player->salleX = salleX;
	player->salleY = salleY;
	ftime(&player->lastAttack);
	player->inventaire.nb_objet = 0;
	player->def = 0;
	player->tailleY = (player->An->hauteurChar-15)*2;
	player->tailleX = (player->An->largeurChar-40)*2;
	if (GOD_MOD) {
		player->damage = 100000;
		player->hp = player->hp_max = 500;
	}
	player->sp = InitSprite(player->An, player->salleX, player->salleY);
}


/**
 * \brief Permet de savoir si un joueur rentre en collision avec un mob
*/
int CollisionMob(int pX, int pY, int pTailleX, int pTailleY, int mX, int mY, int mTailleX, int mTailleY) {
	if ((((mX >= pX) && (mX <= (pX + pTailleX))) || ((mX+mTailleX >= pX) && (mX+mTailleX <= (pX + pTailleX)))) && (((mY >= pY) && (mY <= (pY + pTailleY))) || ((mY+mTailleY >= pY) && (mY+mTailleY <= (pY + pTailleY)))))
		return 1;
	return 0;
}


void LibererPlayer(Player * player) {
	if (player->sp != NULL) {
		LibererSprite(player->sp);
		player->sp = NULL;
	}
	if (player->An != NULL) {
		LibererAnimation(player->An);
		player->An = NULL;
	}

}