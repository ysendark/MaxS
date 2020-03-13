#ifndef __CONST__
#define __CONST__


/**
 * \file const.h
 * \brief Fichier contenant les definitions importantes, les prototypes du .c ainsi les typedef en vu de les utiliser en tout instantdes fonctions nous permettant de gérer la création et l'affichage du labyrinthe
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.8
 * \date 04/02/2020
*/


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "sys/timeb.h"

#define GOD_MOD 1

/** \brief Permet de connaitre le volume avec lequel on doit jouer les sons*/
int VOLUME;

/** \brief Permet de definir la taille du labyrinthe en Y*/
#define N 5 
/** \brief Permet de definir la taille du labyrinthe en X*/
#define M 7    

/** \brief Permet de definir la taille des salles en X */
#define TAILLE_SALLE_X 20 
/** \brief Permet de definir la taille des salles en Y */
#define TAILLE_SALLE_Y 15

/** \brief Permet de definir la taille d'un tile (d'une "case" de la salle) */
#define TAILLE_TILE 50
/** \brief Permet de definir la taille d'une case du labyrinthe */ 
#define TAILLE_CASE 35

/** \brief On definie la taille de la minimap en largeur avec la taille d'une case de labyrinthe*la taille du labyrinthe en X*/
#define LARGEUR_MINIMAP TAILLE_CASE*M

/** \brief On definie la taille de la minimap en hauteur avec la taille d'une case de labyrinthe*la taille du labyrinthe en Y*/
#define HAUTEUR_MINIMAP TAILLE_CASE*N

/** \brief On definie la taille de l'écran en largeur avec la taille de la salle en X * la taille d'un tiles */
#define LARGEUR_ECRAN TAILLE_TILE*TAILLE_SALLE_X
/** \brief On definie la taille de l'écran en hauteur avec la taille de la salle en Y * la taille d'un tiles */
#define HAUTEUR_ECRAN TAILLE_TILE*TAILLE_SALLE_Y

/** \brief Taille max de la pile */
#define TMAX 100 

/** \brief Constante pour définir un couloir dans le labyrinthe*/
#define COULOIR 0
/** \brief Constante pour définir un mur dans le labyrinthe*/
#define MUR -1

/** \brief Constante pour definir le nombre max de monstre possible dans une salle*/
#define MAX_MONSTRE 2
/** \brief Constante pour definir le nombre max d'objet */
#define MAX_OBJET 30
/** \brief Constante pour definir le nombre max de coffre */
#define MAX_COFFRE 3

#define MIN_LOOT_DAMAGE 2
#define MAX_LOOT_DAMAGE 8
#define MIN_LOOT_ARMOR 2
#define MAX_LOOT_ARMOR 8

#define MIN_LOOT_DAMAGE_LEGENDARY 10
#define MAX_LOOT_DAMAGE_LEGENDARY 20
#define MIN_LOOT_ARMOR_LEGENDARY 10
#define MAX_LOOT_ARMOR_LEGENDARY 20

/**
 * \brief Permet d'identifier les chemins lors de la génération du labyrinthe
*/
typedef enum {None /** Il n'y a donc aucun couloir possible*/, Nord /** Il y a un couloir possible au nord*/, Sud/** Il y a un couloir possible au sud*/, Est/** Il y a un couloir possible à l'est*/, Ouest/** Il y a un couloir possible à l'ouest*/} Position;


typedef enum e_status {arret, marche, attaque} Status;

/**
 * \brief Permet d'identifié les textures à appliqué dans une salle, et de savoir si celle ci sont considéré comme des murs ou non
 */
typedef struct {
    /** Permet de distinguer les blocs*/
    int id;
    /** Permet de savoir si le bloc present doit etre considerer comme un mur*/
    int mur;
    /** Permet de savoir si le bloc present doit faire des degats*/
    int degats;
} Map;

typedef struct s_animUnique {
    int depart;
    int longeur;
    int temps;
} AnimUnique;


typedef struct s_animation {
    SDL_Surface * charset;
    AnimUnique ** tab;
    int largeurChar, hauteurChar;
    int nbXChar, nbYChar;
    int nbSens;
    int nbStats;
} Animation;

typedef struct s_sprite {
    Status stat;
    int sens;
    int x;
    int y;
    Animation * anim;
} Sprite;

/**
 * \brief Permet d'avoir toutes les informations sur un mob dans une même structure 
 */
typedef struct {
    int r,g,b;
    /** \brief Points de vies */
    int hp;
    /** \brief Points de vies max*/
    int hp_max;
    /** \brief Position Salle en X */
    int salleX;
    /** \brief Position Salle en y */
    int salleY;
    /** \brief Degat d'attaque*/
    int damages;
    /** \brief Taille en X */
    int tailleX;
    /** \brief Taille en Y */
    int tailleY;
    /** \brief Vitesse de deplacement */
    int vitesse;
    /** \brief Sauvegarde le moment ou le monstre a attaquer pour la derniere fois*/
    struct timeb lastAttack;
    /** \brief Permet de savoir si le mob en question est un boss ou non*/
    int bossFinal;
    Animation * An;
    Sprite * sp;
} Monstre;


/**
 * \brief Permet d'avoir toute les informations sur un objet dans une meme structure
*/
typedef struct s_objet{
    /** \brief Permet d'avoir le RGB de l'objet*/
    int r;
    /** \brief Permet d'avoir le RGB de l'objet*/
    int g;
    /** \brief Permet d'avoir le RGB de l'objet*/
    int b;
    /** \brief Permet de savoir combien d'attaque ajoutera l'objet*/
    int attaque;
    /** \brief Permet de savoir combien de resistance ajoutera l'objet*/
    int def;
} Objet;


/**
 * \brief Permet d'avoir toute les informations sur un coffre dans une meme structure
*/
typedef struct s_coffre {
    /** \brief Permet de savoir si le coffre est ouvert ou fermer */
    int ouvert;
    /** \brief Permet d'avoir la position du coffre en X*/
    int salleX;
    /** \brief Permet d'avoir la position du coffre en Y*/
    int salleY;
    /** \brief Permet de savoir si c'est un coffre legendaire ou non*/
    int legendary;
} Coffre;


/**
 * \brief Permet d'avoir toute les informations sur l'inventaire du joueur dans une meme structure
*/
typedef struct s_inventaire {
    /** \brief Indique le nombre d'objet présent dans l'inventaire*/
    int nb_objet;
    /** \brief Tableau d'objet, nous donnans les informations détailler sur chaque objet*/
    Objet objet[MAX_OBJET];
} Inventaire;

/**
 * \brief Permet d'identifié les salles indépendament des autres et d'y avoir toutes les informations nécessaire indépendamment chacune
*/
typedef struct {
    /** \brief Sert à indiquer si une porte est présente à l'ouest ou non */
	int ouest;
    /** \brief Sert à indiquer si une porte est présente au sud ou non */
    int sud;
    /** \brief Sert à indiquer si une porte est présente au nord ou non */ 
    int nord;
    /** \brief Sert à indiquer si une porte est présente à l'est ou non */
    int est;
    /** \brief Permet de savoir le nombre de porte que contient une salle*/
	int nbPorte;  
    /** \brief Permet de savoir si la salle a déja était visiter ou non */
	int explorer;
    /** \brief Matrice nous permettant de savoir quelle texture appliqué à l'écran*/
    Map matTexture[TAILLE_SALLE_Y][TAILLE_SALLE_X];
    /** \brief Indique le nombre de monstre present dans la salle*/
    int nbMonstres;
    /** \brief Permet d'enregistrer les monstres present dans la salle*/
    Monstre monstre[MAX_MONSTRE];
    int nbCoffre;
    Coffre coffre[MAX_COFFRE];
} Salle;


/**
    \brief Permet d'avoir toutes les informations sur un joueur dans une même structure
*/
typedef struct {
    int tailleX;
    int tailleY;
    /** \brief Désignent la coordonnées X d'où se trouve le joueur dans la salle (0 <= x < TAILLE_SALLE_X) */
    int salleX;
    /** \brief Désignent la coordonnées Y d'où se trouve le joueur dans la salle (0 <= y < TAILLE_SALLE_Y) */   
    int salleY;
    /** \brief Désignent la coordonnées X de la salle où se trouve le joueur (0 <= x < M)*/
    int labX;
    /** \brief Désignent la coordonnées Y de la salle où se trouve le joueur (0 <= y < N)*/
    int labY;
    /** \brief Points de vies */
    int hp;
    /** \brief Points de vies max */
    int hp_max;
    /** \brief Nombre de damage que vas faire le joueur quand il va donner un coup*/
    int damage;
    /** \brief Nombre de resistance que vas avoir le joueur lorsqu'il va se faire taper*/
    int def;
    /** \brief Permet d'enregister la derniere attaque d'un joueur*/
    struct timeb lastAttack;
    /** \brief Peremt de gérer l'inventaire du joueur*/
    Inventaire inventaire;
    Sprite * sp;
    Animation * An;
} Player;


/**
 *  \brief Permet d'avoir toutes les informations sur le labyrinthe dans une même structure
 */
typedef struct {
    /** \brief Matrice permettant de savoir où sont les mur et les couloirs*/
    int mat[N][M];
    /** \brief Permet d'enregistrer le seed utiliser pour généré le labyrinthe*/
    int seed;
} Labyrinthe;


int valide (int x, int y);
int valideSalle (int x, int y);
int verifMinimap(int x, int y);
int verifHealthBar(int x, int y);

#endif
