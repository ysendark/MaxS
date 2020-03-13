#include <unistd.h>
#include "labyrinthe.h"
#include "saveload.h"
#include "animation.h"
#include "perso.h"
#include "monstre.h"
#include "objet.h"
#include "son.h"

/**
 * \file roguelike.c
 * \brief Fichier contenant la fonction main de notre programme
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/

/** \brief Permet de savoir si le joueur est dans un menu ou non*/
int inGame = 0;
/** \brief Permet de savoir si le joueur est en partie ou non */
int inMenu = 1;

/** \brief Permet de savoir dans quel menu le joueur se trouve (si il est dans un menu)*/
Menu menuActuel = Principal;

/** \brief Permet de savoir dans quel niveau le joueur se trouve*/
int levelActuel = 1;

int fps = 0;
int n = 0;
struct timeb lastFPS;

void AfficherFPS(SDL_Renderer * rendu, TTF_Font * police) {

	struct timeb currentFPS;

	char texteTab[5];

	SDL_Rect rect;
	SDL_Surface * texte;
	SDL_Color couleur = {94, 148, 0};

	rect.x = 5;
	rect.y = 5;

	ftime(&currentFPS);
	int secondes = (int) difftime(currentFPS.time, lastFPS.time);
	int ms1 = 1000 - lastFPS.millitm;
    int ms2 = currentFPS.millitm;

	fps++;

	if ((((ms1+ms2) >= 1000) && secondes >= 1) || (secondes >= 2)) {
		ftime(&lastFPS);
		n = fps;
		fps = 0;
	}

	sprintf(texteTab, "%d", n);
	texte = TTF_RenderText_Solid(police, texteTab, couleur);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(rendu, texte);
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(rendu, texture, NULL, &rect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(texte);

}


/**
 * \brief Permet de gerer la mort d'un joueur
*/
void MortPlayer(Player * player, SDL_Window * screen, Salle salle[N][M], Labyrinthe * labyrinthe) {
	levelActuel = 1;
	initLab(labyrinthe);
	initPlayer(player, screen, "player.txt", 0, 0, LARGEUR_ECRAN/2 - TAILLE_TILE/2, HAUTEUR_ECRAN/2 - TAILLE_TILE/2);
	Player p = *player;
	initSalle(screen, salle, labyrinthe->mat, p, levelActuel);
	salle[player->labY][player->labX].explorer = 1;
	int lX, lY;
	Labyrinthe lab = *labyrinthe;
	CheminLePlusLong(lab, &lX, &lY);
	Player j = *player;
	InitialisationBoss(screen, &salle[lY][lX], salle[player->labY][player->labX], j);
	if (sound != NULL) {
		Mix_FreeMusic(sound);
		sound = NULL;
	}
}

/**
 * \brief Permet de gerer tout l'affichage du jeu
*/
void Affichage(SDL_Renderer * rendu, TTF_Font * police, Salle salle[N][M], Player player) {

	AfficherSalle(rendu, salle[player.labY][player.labX], player, levelActuel);

	for (int i = 0 ; i < salle[player.labY][player.labX].nbCoffre ; i++) {
		AfficherCoffre(rendu, salle[player.labY][player.labX].coffre[i]);
	}
	
	//AfficherPlayerSalle(rendu, player);
	AffichageAnimation(player.An, rendu, player.sp->sens, (int)player.sp->stat, player.sp->x, player.sp->y);
	
	for (int i = 0 ; i < salle[player.labY][player.labX].nbMonstres ; i++) {
		AfficherMob(rendu, salle[player.labY][player.labX].monstre[i]);
		AffichageAnimation(salle[player.labY][player.labX].monstre[i].An, rendu, salle[player.labY][player.labX].monstre[i].sp->sens, (int)salle[player.labY][player.labX].monstre[i].sp->stat, salle[player.labY][player.labX].monstre[i].sp->x, salle[player.labY][player.labX].monstre[i].sp->y);
	}

	AfficherMinimap(rendu, salle, player);
	AfficherHUD(rendu, salle, player);
	AfficherFPS(rendu, police);

}


/**
 * \brief Permet de gerer l'evolution des monstres
 * \return 1 Si le joueur est mort suite a une collision avec un mob
 * \return 0 Sinon
*/
int  EvolutionMonstres (Salle salle[N][M], Player player, Player * p) {
	for (int i = 0 ; i < salle[player.labY][player.labX].nbMonstres ; i++) {
		if (((player.salleX >= (salle[player.labY][player.labX].monstre[i].salleX-salle[player.labY][player.labX].monstre[i].tailleX*7)) && (player.salleX <= (salle[player.labY][player.labX].monstre[i].salleX+salle[player.labY][player.labX].monstre[i].tailleX)+7*salle[player.labY][player.labX].monstre[i].tailleX)) && ((player.salleY >= (salle[player.labY][player.labX].monstre[i].salleY-7*salle[player.labY][player.labX].monstre[i].tailleY)) && (player.salleY <= (salle[player.labY][player.labX].monstre[i].salleY+salle[player.labY][player.labX].monstre[i].tailleY)+7*salle[player.labY][player.labX].monstre[i].tailleX))) {
			if (!CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX+2, salle[player.labY][player.labX].monstre[i].salleY, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY) && !CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX-2, salle[player.labY][player.labX].monstre[i].salleY, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY) && !CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX, salle[player.labY][player.labX].monstre[i].salleY+2, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY) && !CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX, salle[player.labY][player.labX].monstre[i].salleY-2, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY)) {
				DeplacementMonstre(&salle[player.labY][player.labX].monstre[i], player);
			}
		}
		if (CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX+2, salle[player.labY][player.labX].monstre[i].salleY, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY) || CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX-2, salle[player.labY][player.labX].monstre[i].salleY, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY) || CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX, salle[player.labY][player.labX].monstre[i].salleY+2, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY) || CollisionMob(player.salleX, player.salleY, player.tailleX, player.tailleY, salle[player.labY][player.labX].monstre[i].salleX, salle[player.labY][player.labX].monstre[i].salleY-2, salle[player.labY][player.labX].monstre[i].tailleX, salle[player.labY][player.labX].monstre[i].tailleY)) {
			if (TimerMob(&salle[player.labY][player.labX].monstre[i])) {
				int degats = salle[player.labY][player.labX].monstre[i].damages - p->def/4;
				if (salle[player.labY][player.labX].nbMonstres && !salle[player.labY][player.labX].monstre[0].bossFinal) {
					if (sound != NULL) {
						Mix_FreeMusic(sound);
						sound = NULL;
					}
					sound = Mix_LoadMUS("./sounds/hitted.wav");
					Mix_PlayMusic(sound, 1);
				}

				if (!GOD_MOD) {
					if (degats < 5) {
						p->hp -= 5;
					}
					else {
						p->hp -= degats;
					}
					if (p->hp <= 0) {
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


/**
 * \brief Fonction main du programme
 */
int main(int argc, char ** argv) {

	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
	TTF_Init();

	SDL_Window *screen = SDL_CreateWindow("RogueLike", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_ECRAN, HAUTEUR_ECRAN, SDL_SWSURFACE);
	SDL_Renderer * rendu = SDL_CreateRenderer(screen, -1, 0);
	SDL_Surface * icon = SDL_LoadBMP("img/Icon.bmp");
	SDL_SetWindowIcon(screen, icon);
	SDL_FreeSurface(icon);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);


	TTF_Font * police = TTF_OpenFont("Font.ttf", 65);

	Salle salle[N][M];

	Input in;
	Player player;
	player.sp = NULL;
	player.An = NULL;

	Labyrinthe labyrinthe;

	sound = NULL;
	VOLUME = MIX_MAX_VOLUME/2;
	ChargerSon();

	//Initialisation nécessaire
	InitEvents(&in);
	ftime(&lastFPS);

	while (!in.quit) {

		if (sound != NULL) {
			Mix_FreeMusic(sound);
			sound = NULL;
		}

		sound = Mix_LoadMUS("./sounds/mainpage.wav");
		Mix_PlayMusic(sound, 1);
		Mix_VolumeMusic(VOLUME);

		while (inMenu && !in.quit) {

			Menu choix = choixMenu(menuActuel);

			switch (choix) {
				case Principal:
					menuActuel = Principal;
					AfficherMenuPrincipal(rendu, police);
					break;
				case New:
					inMenu = 0;
					inGame = 1;
					initLab(&labyrinthe);
					initPlayer(&player, screen, "player.txt", 0, 0, LARGEUR_ECRAN/2 - TAILLE_TILE/2, HAUTEUR_ECRAN/2 - TAILLE_TILE/2);
					initSalle(screen, salle, labyrinthe.mat, player, levelActuel);
					int lX, lY;
					CheminLePlusLong(labyrinthe, &lX, &lY);
					InitialisationBoss(screen, &salle[lY][lX], salle[player.labY][player.labX], player);
					levelActuel = 1;
					salle[player.labY][player.labX].explorer = 1;
					break;
				case Load:
					menuActuel = Load;
					AfficherMenuChargerPartie(rendu, police);
					break;
				case Quit:
					in.quit = 1;
					break;
				case Setting:
					menuActuel = Setting;
					AfficherMenuSetting(rendu, police);
					break;
				case Volume:
					menuActuel = Volume;
					AfficherMenuVolume(rendu, police);
					break;
				case Save1:
					inMenu = 0;
					inGame = 1;
					ChargerPartie("./saves/Save1.txt", &labyrinthe, &player, salle);
					ChargerLab(&labyrinthe);
					break;
				case Save2:
					inMenu = 0;
					inGame = 1;
					ChargerPartie("./saves/Save2.txt", &labyrinthe, &player, salle);
					ChargerLab(&labyrinthe);
					break;
				case Save3:
					inMenu = 0;
					inGame = 1;
					ChargerPartie("./saves/Save3.txt", &labyrinthe, &player, salle);
					ChargerLab(&labyrinthe);
					break;
				case Touches:
					menuActuel = Touches;
					AfficherMenuTouches(rendu, police);
					break;
				default:
					break;
			}
			AfficherFPS(rendu, police);
			SDL_RenderPresent(rendu);
			SDL_Delay(2);
		}

		if (sound != NULL) {
			Mix_FreeMusic(sound);
			sound = NULL;
		}

		while (inGame && !in.quit) {
			
			UpdateEvents(&in);

			if (ActionSalle(&in, rendu, police, &player, salle[player.labY][player.labX], &inGame, &inMenu, &levelActuel, &menuActuel, salle, labyrinthe)) { //Si on doit up de lvl
				LibererPlayer(&player);
				initLab(&labyrinthe);
				Player p;
				initPlayer(&player, screen, "player.txt", 0, 0, LARGEUR_ECRAN/2 - TAILLE_TILE/2, HAUTEUR_ECRAN/2 - TAILLE_TILE/2);
				p.damage = player.damage;
				p.def = player.def;
				p.hp_max = p.hp = player.hp_max*levelActuel;
				player = p;
				initSalle(screen, salle, labyrinthe.mat, player, levelActuel);
				salle[player.labY][player.labX].explorer = 1;
				int lX, lY;
				CheminLePlusLong(labyrinthe, &lX, &lY);
				InitialisationBoss(screen, &salle[lY][lX], salle[player.labY][player.labX], player);
				if (sound != NULL) {
					Mix_FreeMusic(sound);
					sound = NULL;
				}
			}
			PassagePorte(salle, &player);

			if (EvolutionMonstres(salle, player, &player)) {
				MortPlayer(&player, screen, salle, &labyrinthe);
			}

			Affichage(rendu, police, salle, player);

			if (in.key[SDLK_TAB]) {
				AfficherInventaire(rendu, player.inventaire, police);
			}

			SDL_RenderPresent(rendu);
			SDL_Delay(2);
		}

		LibererPlayer(&player);
	}

	if (sound != NULL)
		Mix_FreeMusic(sound);

	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
