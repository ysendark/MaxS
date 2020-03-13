#include "saveload.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * \file saveload.c
 * \brief Fichier contenant les fontions nous permettant de gérer la sauvegarde et le chargement de partie
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 09/02/2020
*/


/**
 * \brief Fonction nous permettant de sauvegarder une partie dans un fichier avec le nom rentrer en parametre
 * \details La fonction va sauvegarder le labyrinthe (son seed), toutes les informations de la structure player, ainsi que toutes les informations des structures salle 
 */
void SauvegarderPartie (const char name[30], Labyrinthe labyrinthe, Player player, Salle salle[N][M]) {
	FILE * fichier = NULL;

	fichier = fopen(name, "w+");

	/* Fichier */
	fprintf(fichier,"#Sauvegarde\n%s\n",name);
	/* Labyrinthe */
	fprintf(fichier,"#Labyrinthe\nSeed\n%d\n", labyrinthe.seed);
	/* Player */
	fprintf(fichier,"#Player\nPV\n%d\nPVMax\n%d\nCoord_Pl_Salle\n%d %d\nCoord_Pl_Lab\n%d %d\nDamage\n%d\nNbObjets\n%d\n", player.hp, player.hp_max, player.salleX, player.salleY, player.labX, player.labY, player.damage, player.inventaire.nb_objet);
	fprintf(fichier, "#Inventaire\n");
	for (int i = 0 ; i < player.inventaire.nb_objet ; i++) {
		fprintf(fichier, "%d %d %d %d %d", player.inventaire.objet[i].r, player.inventaire.objet[i].g, player.inventaire.objet[i].b, player.inventaire.objet[i].attaque, player.inventaire.objet[i].def);
		fprintf(fichier, "\n");
	}
	/* Salles */
	fprintf(fichier, "#Salles\n");
	fprintf(fichier, "#Explorer\n");
	for (int i = 0 ; i < N ; i++) {
		for (int j = 0 ; j < M ; j++) {
			fprintf(fichier, "%d %d %d %d %d %d %d %d\n", salle[i][j].explorer, salle[i][j].nbPorte, salle[i][j].nord, salle[i][j].sud, salle[i][j].est, salle[i][j].ouest, salle[i][j].nbCoffre, salle[i][j].nbMonstres);
			for (int k = 0 ; k < TAILLE_SALLE_Y ; k++) {
				for (int p = 0 ; p < TAILLE_SALLE_X ; p++) {
					fprintf(fichier, "%d ", salle[i][j].matTexture[k][p].id);
				}
				fprintf(fichier, "\n");
			}
			fprintf(fichier, "\n");
			for (int k = 0 ; k < salle[i][j].nbCoffre ; k++) {
				fprintf(fichier, "%d %d %d %d", salle[i][j].coffre[k].ouvert, salle[i][j].coffre[k].salleX, salle[i][j].coffre[k].salleY, salle[i][j].coffre[k].legendary);
				fprintf(fichier, "\n");
			}
			for (int k = 0 ; k < salle[i][j].nbMonstres ; k++) {
				fprintf(fichier, "%d %d %d %d %d %d %d %d %d %d %d", salle[i][j].monstre[k].r, salle[i][j].monstre[k].g, salle[i][j].monstre[k].b, salle[i][j].monstre[k].salleX, salle[i][j].monstre[k].salleY, salle[i][j].monstre[k].hp, salle[i][j].monstre[k].hp_max, salle[i][j].monstre[k].vitesse, salle[i][j].monstre[k].tailleX, salle[i][j].monstre[k].tailleY, salle[i][j].monstre[k].bossFinal);
				fprintf(fichier, "\n");
			}
		}
	}

	fclose(fichier);
}


/**
 * \brief Nous permet de charger une partie, partie précédemment enregister dans un fichier dont le nom est rentrer en paramètre
 * \details la fonction va charger toutes les informations qui sont sauvegarder dans la fonction SauvegarderPartie
*/
void ChargerPartie (const char name[30], Labyrinthe * labyrinthe, Player * player, Salle salle[N][M]) {
	FILE * fichier = NULL;

	fichier = fopen(name, "r");

	char buffer[30];

	fscanf(fichier,"%s", buffer); //#Sauvegarde
	fscanf(fichier,"%s", buffer); //Nom fichier

	/********** Labyrinthe ************/
	fscanf(fichier,"%s", buffer); //#Labyrinthe
	fscanf(fichier,"%s", buffer); //Seed
	fscanf(fichier,"%d", &labyrinthe->seed); //Seed (int)

	/********** Player ************/
	fscanf(fichier,"%s", buffer); //#Player
	fscanf(fichier,"%s", buffer); //Pv
	fscanf(fichier,"%d", &player->hp); //Pv (int)
	fscanf(fichier,"%s", buffer); //Pv Max
	fscanf(fichier,"%d", &player->hp_max); //Pv Max (int)
	fscanf(fichier,"%s", buffer); //Coord_Pl_Salle
	fscanf(fichier,"%d %d", &player->salleX, &player->salleY); //salleX salleY (int)
	fscanf(fichier,"%s", buffer); //Coord_Pl_Lab
	fscanf(fichier,"%d %d", &player->labX, &player->labY); //labX labY (int)
	fscanf(fichier,"%s", buffer); //Damage
	fscanf(fichier,"%d", &player->damage); //Damage (int)
	fscanf(fichier,"%s", buffer); //NbObjet
	fscanf(fichier,"%d", &player->inventaire.nb_objet); //NbObjet (int)
	fscanf(fichier,"%s", buffer); //Inventaire
	for (int i = 0 ; i < player->inventaire.nb_objet ; i++) {
		fscanf(fichier, "%d %d %d %d %d", &player->inventaire.objet[i].r, &player->inventaire.objet[i].g, &player->inventaire.objet[i].b, &player->inventaire.objet[i].attaque, &player->inventaire.objet[i].def);
		fscanf(fichier, "\n");
	}

	/********** Salles ************/
	fscanf(fichier,"%s", buffer); //#Salle
	fscanf(fichier,"%s", buffer); //Explorer
	for (int i = 0 ; i < N ; i++) {
		for (int j = 0 ; j < M ; j++) {
			fscanf(fichier, "%d %d %d %d %d %d %d %d", &salle[i][j].explorer, &salle[i][j].nbPorte, &salle[i][j].nord, &salle[i][j].sud, &salle[i][j].est, &salle[i][j].ouest, &salle[i][j].nbCoffre, &salle[i][j].nbMonstres);
			for (int k = 0 ; k < TAILLE_SALLE_Y ; k++) {
				for (int p = 0 ; p < TAILLE_SALLE_X ; p++) {
					fscanf(fichier, "%d", &salle[i][j].matTexture[k][p].id);
				}
			}
			for (int k = 0 ; k < salle[i][j].nbCoffre ; k++) {
				fscanf(fichier, "%d %d %d %d", &salle[i][j].coffre[k].ouvert, &salle[i][j].coffre[k].salleX, &salle[i][j].coffre[k].salleY, &salle[i][j].coffre[k].legendary);
			}
			for (int k = 0 ; k < salle[i][j].nbMonstres ; k++) {
				fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d %d", &salle[i][j].monstre[k].r, &salle[i][j].monstre[k].g, &salle[i][j].monstre[k].b, &salle[i][j].monstre[k].salleX, &salle[i][j].monstre[k].salleY, &salle[i][j].monstre[k].hp, &salle[i][j].monstre[k].hp_max, &salle[i][j].monstre[k].vitesse, &salle[i][j].monstre[k].tailleX, &salle[i][j].monstre[k].tailleY, &salle[i][j].monstre[k].bossFinal);
			}
		}
	}


	fclose(fichier);
}



void SauvegarderSon () {
	FILE * f = NULL;
	f = fopen("./saves/Son.txt", "w+");
	if (f == NULL) {
		printf("Erreur fichier sauvegarde son");
	}
	fprintf(f, "#VolumePrincipal\n%d\n", VOLUME);
	fclose(f);
}


void ChargerSon () {
	FILE * f = NULL;
	f = fopen("./saves/Son.txt", "r");
	if (f != NULL) {
		char buffer[50];
		fscanf(f, "%s", buffer);
		fscanf(f, "%d", &VOLUME);
		fclose(f);
	}
}