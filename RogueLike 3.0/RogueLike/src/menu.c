#include "menu.h"
#include "saveload.h"

/**
 * \file menu.c
 * \brief Fichier contenant des fonctions nous permettant de gérer la création et l'affichage des différents menus
 * \author HENRY Allan, STER Maxime, GAISNE Maxime, ZHENG Haoran
 * \version 0.1
 * \date 04/02/2020
*/


/**
 * \brief Permet d'afficher le menu affichants les différentes règles du jeu
*/
void AfficherMenuRegles (SDL_Renderer * rendu, TTF_Font * police) {
    
    /******************** AFFICHE LE FOND D'ECRAN ET LE TITLE ***************************/

    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);
    SDL_RenderClear(rendu);

    SDL_Surface * imageFond = IMG_Load("./img/fondecran.jpg");
    SDL_Surface * imageTitle = IMG_Load("./img/ROGUELIKE.png");

    SDL_Texture * T_imageFond = SDL_CreateTextureFromSurface(rendu, imageFond);
    SDL_Texture * T_imageTitle = SDL_CreateTextureFromSurface(rendu, imageTitle);

    SDL_Rect R_imageFond = {0,0,LARGEUR_ECRAN,HAUTEUR_ECRAN};
    SDL_Rect R_imageTitle = {0,0,0,0};

    SDL_QueryTexture(T_imageTitle, NULL, NULL, &R_imageTitle.w, &R_imageTitle.h);
    R_imageTitle.x = LARGEUR_ECRAN/2 - R_imageTitle.w/2;
    R_imageTitle.y = ((HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100)/2-R_imageTitle.h/2;


    SDL_RenderCopy(rendu, T_imageFond, NULL, &R_imageFond);
    SDL_RenderCopy(rendu, T_imageTitle, NULL, &R_imageTitle);

    SDL_FreeSurface(imageTitle);
    SDL_DestroyTexture(T_imageTitle);
    SDL_FreeSurface(imageFond);
    SDL_DestroyTexture(T_imageFond);

    /************************************************************************************/


    /******************** AFFICHE LE BOUTON RETURN EN BAS A DROITE ***************************/

    SDL_Rect rectReturn = {LARGEUR_ECRAN - 150, HAUTEUR_ECRAN - 125, 64, 64} ;
    SDL_Surface * imageReturn = IMG_Load("./img/return.png");
    SDL_Texture * T_imageReturn = SDL_CreateTextureFromSurface(rendu, imageReturn);
    SDL_QueryTexture(T_imageReturn, NULL, NULL, &rectReturn.w, &rectReturn.h);
    SDL_RenderCopy(rendu, T_imageReturn, NULL, &rectReturn);

    SDL_DestroyTexture(T_imageReturn);
    SDL_FreeSurface(imageReturn);

}


/**
	\brief Permet d'afficher le menu Principal
*/
void AfficherMenuPrincipal(SDL_Renderer * rendu, TTF_Font * police) {

    /******************** AFFICHE LE FOND D'ECRAN ET LE TITLE ***************************/

    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);
    SDL_RenderClear(rendu);

    SDL_Surface * imageFond = IMG_Load("./img/fondecran.jpg");
    SDL_Surface * imageTitle = IMG_Load("./img/ROGUELIKE.png");

    SDL_Texture * T_imageFond = SDL_CreateTextureFromSurface(rendu, imageFond);
    SDL_Texture * T_imageTitle = SDL_CreateTextureFromSurface(rendu, imageTitle);

    SDL_Rect R_imageFond = {0,0,LARGEUR_ECRAN,HAUTEUR_ECRAN};
    SDL_Rect R_imageTitle = {0,0,0,0};

    SDL_QueryTexture(T_imageTitle, NULL, NULL, &R_imageTitle.w, &R_imageTitle.h);
    R_imageTitle.x = LARGEUR_ECRAN/2 - R_imageTitle.w/2;
    R_imageTitle.y = ((HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100)/2-R_imageTitle.h/2;


    SDL_RenderCopy(rendu, T_imageFond, NULL, &R_imageFond);
    SDL_RenderCopy(rendu, T_imageTitle, NULL, &R_imageTitle);

    SDL_FreeSurface(imageTitle);
    SDL_DestroyTexture(T_imageTitle);
    SDL_FreeSurface(imageFond);
    SDL_DestroyTexture(T_imageFond);

    /************************************************************************************/

    int ecartCase = TAILLE_BUTTON_MENU_PRINCIPAL_Y + 55;

    //Rectangle plein
    // {posX, posY, TAILLE_X, TAILLE_Y}
    SDL_Rect rect = {0, 0, TAILLE_BUTTON_MENU_PRINCIPAL_X, TAILLE_BUTTON_MENU_PRINCIPAL_Y};

    rect.x = LARGEUR_ECRAN/2 - TAILLE_BUTTON_MENU_PRINCIPAL_X/2;
    rect.y = (HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100;

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor (rendu, 100, 100, 100, 200);

    for (int i = 0 ; i < NB_BUTTON_MENU_PRINCIPAL ; i++) {
        SDL_RenderFillRect(rendu, &rect);
        rect.y += ecartCase;
    }


    SDL_Color couleur = {255, 255, 255};
    SDL_Surface * surface = TTF_RenderText_Solid(police, "Nouvelle Partie", couleur);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(rendu, surface);
    int texW = 0;
    int texH = 0;



    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {rect.x + 55, HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 15 + 100, texW, texH };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);


    dstrect.y += ecartCase;
    surface = TTF_RenderText_Solid(police, "Charger Partie", couleur);
    texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    dstrect.w = texW;
    dstrect.h = texH;
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);


    dstrect.y += ecartCase;
    dstrect.x += 125;
    surface = TTF_RenderText_Solid(police, "Quitter", couleur);
    texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    dstrect.w = texW;
    dstrect.h = texH;
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    /******************** AFFICHE LE BOUTON SETTING EN BAS A DROITE ***************************/

    SDL_Rect rectReturn = {LARGEUR_ECRAN - 150, HAUTEUR_ECRAN - 150, 64, 64} ;
    SDL_Surface * imageReturn = IMG_Load("./img/setting.png");
    SDL_Texture * T_imageReturn = SDL_CreateTextureFromSurface(rendu, imageReturn);
    SDL_QueryTexture(T_imageReturn, NULL, NULL, &rectReturn.w, &rectReturn.h);
    SDL_RenderCopy(rendu, T_imageReturn, NULL, &rectReturn);

    SDL_DestroyTexture(T_imageReturn);
    SDL_FreeSurface(imageReturn);

}


/**
	\brief Permet d'afficher le menu Charger Partie
*/
void AfficherMenuChargerPartie(SDL_Renderer * rendu, TTF_Font * police) {

    /******************** AFFICHE LE FOND D'ECRAN ET LE TITLE ***************************/

    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);
    SDL_RenderClear(rendu);

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

    FILE * fichier;

    SDL_Surface * imageFond = IMG_Load("./img/fondecran.jpg");
    SDL_Surface * imageTitle = IMG_Load("./img/ROGUELIKE.png");

    SDL_Texture * T_imageFond = SDL_CreateTextureFromSurface(rendu, imageFond);
    SDL_Texture * T_imageTitle = SDL_CreateTextureFromSurface(rendu, imageTitle);

    SDL_Rect R_imageFond = {0,0,LARGEUR_ECRAN,HAUTEUR_ECRAN};
    SDL_Rect R_imageTitle = {0,0,0,0};

    SDL_QueryTexture(T_imageTitle, NULL, NULL, &R_imageTitle.w, &R_imageTitle.h);
    R_imageTitle.x = LARGEUR_ECRAN/2 - R_imageTitle.w/2;
    R_imageTitle.y = ((HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100)/2-R_imageTitle.h/2;


    SDL_RenderCopy(rendu, T_imageFond, NULL, &R_imageFond);
    SDL_RenderCopy(rendu, T_imageTitle, NULL, &R_imageTitle);

    SDL_FreeSurface(imageTitle);
    SDL_DestroyTexture(T_imageTitle);
    SDL_FreeSurface(imageFond);
    SDL_DestroyTexture(T_imageFond);

    /************************************************************************************/

    int ecartCase = TAILLE_BUTTON_MENU_PRINCIPAL_Y + 55;

    //Rectangle plein
    // {posX, posY, TAILLE_X, TAILLE_Y}
    SDL_Rect rect = {LARGEUR_ECRAN/2 - TAILLE_BUTTON_MENU_PRINCIPAL_X/2, (HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100, TAILLE_BUTTON_MENU_PRINCIPAL_X, TAILLE_BUTTON_MENU_PRINCIPAL_Y};

    SDL_SetRenderDrawColor (rendu, 100, 100, 100, 200);

    for (int i = 0 ; i < NB_BUTTON_MENU_PRINCIPAL ; i++) {
        SDL_RenderFillRect(rendu, &rect);
        rect.y += ecartCase;
    }

    SDL_Color couleur = {255, 255, 255};
    SDL_Surface * surface = TTF_RenderText_Solid(police, "Sauvegarde 1", couleur);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(rendu, surface);
    int texW = 0;
    int texH = 0;



    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {rect.x + 75, HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 115, texW, texH };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);


    dstrect.y += ecartCase;
    surface = TTF_RenderText_Solid(police, "Sauvegarde 2", couleur);
    texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    dstrect.w = texW;
    dstrect.h = texH;
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);


    dstrect.y += ecartCase;
    surface = TTF_RenderText_Solid(police, "Sauvegarde 3", couleur);
    texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    dstrect.w = texW;
    dstrect.h = texH;
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    SDL_SetRenderDrawColor (rendu, 20, 20, 20, 100);

    rect.y = (HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100;
    rect.x = LARGEUR_ECRAN/2 - TAILLE_BUTTON_MENU_PRINCIPAL_X/2;
    rect.w = TAILLE_BUTTON_MENU_PRINCIPAL_X;
    rect.h = TAILLE_BUTTON_MENU_PRINCIPAL_Y;
    fichier = fopen("./saves/Save1.txt", "r");
    if (fichier == NULL) {
        SDL_RenderFillRect(rendu, &rect);
    }
    else {
        fclose(fichier);
    }

    rect.y += ecartCase;
    fichier = fopen("./saves/Save2.txt", "r");
    if (fichier == NULL) {
        SDL_RenderFillRect(rendu, &rect);
    }
    else {
        fclose(fichier);
    }

    rect.y += ecartCase;
    fichier = fopen("./saves/Save3.txt", "r");
    if (fichier == NULL) {
        SDL_RenderFillRect(rendu, &rect);
    }
    else {
        fclose(fichier);
    }


    /******************** AFFICHE LE BOUTON RETURN EN BAS A DROITE ***************************/

    SDL_Rect rectReturn = {LARGEUR_ECRAN - 150, HAUTEUR_ECRAN - 150, 64, 64} ;
    SDL_Surface * imageReturn = IMG_Load("./img/return.png");
    SDL_Texture * T_imageReturn = SDL_CreateTextureFromSurface(rendu, imageReturn);
    SDL_QueryTexture(T_imageReturn, NULL, NULL, &rectReturn.w, &rectReturn.h);
    SDL_RenderCopy(rendu, T_imageReturn, NULL, &rectReturn);

    SDL_DestroyTexture(T_imageReturn);
    SDL_FreeSurface(imageReturn);

}


void AfficherMenuVolume (SDL_Renderer * rendu, TTF_Font * police) {

    /******************** AFFICHE LE FOND D'ECRAN ET LE TITLE ***************************/
    
    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);
    SDL_RenderClear(rendu);

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

    SDL_Surface * imageFond = IMG_Load("./img/fondecran.jpg");
    SDL_Surface * imageTitle = IMG_Load("./img/ROGUELIKE.png");

    SDL_Texture * T_imageFond = SDL_CreateTextureFromSurface(rendu, imageFond);
    SDL_Texture * T_imageTitle = SDL_CreateTextureFromSurface(rendu, imageTitle);

    SDL_Rect R_imageFond = {0,0,LARGEUR_ECRAN,HAUTEUR_ECRAN};
    SDL_Rect R_imageTitle = {0,0,0,0};

    SDL_QueryTexture(T_imageTitle, NULL, NULL, &R_imageTitle.w, &R_imageTitle.h);
    R_imageTitle.x = LARGEUR_ECRAN/2 - R_imageTitle.w/2;
    R_imageTitle.y = ((HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100)/2-R_imageTitle.h/2;


    SDL_RenderCopy(rendu, T_imageFond, NULL, &R_imageFond);
    SDL_RenderCopy(rendu, T_imageTitle, NULL, &R_imageTitle);

    SDL_FreeSurface(imageTitle);
    SDL_DestroyTexture(T_imageTitle);
    SDL_FreeSurface(imageFond);
    SDL_DestroyTexture(T_imageFond);

    /************************************************************************************/


    SDL_SetRenderDrawColor (rendu, 20, 20, 20, 100);
    SDL_Rect sliderVolume = {LARGEUR_ECRAN/2 - TAILLE_BUTTON_MENU_PRINCIPAL_X/2, HAUTEUR_ECRAN/2 - 13, TAILLE_BUTTON_MENU_PRINCIPAL_X, 26};
    SDL_RenderFillRect(rendu, &sliderVolume);

    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);
    float pourcentageVie = (float)VOLUME/MIX_MAX_VOLUME;
    sliderVolume.w = TAILLE_BUTTON_MENU_PRINCIPAL_X * pourcentageVie;
    SDL_RenderFillRect(rendu, &sliderVolume);


    /******************** AFFICHE LE BOUTON RETURN EN BAS A DROITE ***************************/

    SDL_Rect rectReturn = {LARGEUR_ECRAN - 150, HAUTEUR_ECRAN - 150, 64, 64} ;
    SDL_Surface * imageReturn = IMG_Load("./img/return.png");
    SDL_Texture * T_imageReturn = SDL_CreateTextureFromSurface(rendu, imageReturn);
    SDL_QueryTexture(T_imageReturn, NULL, NULL, &rectReturn.w, &rectReturn.h);
    SDL_RenderCopy(rendu, T_imageReturn, NULL, &rectReturn);

    SDL_DestroyTexture(T_imageReturn);
    SDL_FreeSurface(imageReturn);

}


/**
	\brief Permet d'afficher le menu option
*/
void AfficherMenuSetting(SDL_Renderer * rendu, TTF_Font * police) {

    /******************** AFFICHE LE FOND D'ECRAN ET LE TITLE ***************************/

    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);
    SDL_RenderClear(rendu);

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

    SDL_Surface * imageFond = IMG_Load("./img/fondecran.jpg");
    SDL_Surface * imageTitle = IMG_Load("./img/ROGUELIKE.png");

    SDL_Texture * T_imageFond = SDL_CreateTextureFromSurface(rendu, imageFond);
    SDL_Texture * T_imageTitle = SDL_CreateTextureFromSurface(rendu, imageTitle);

    SDL_Rect R_imageFond = {0,0,LARGEUR_ECRAN,HAUTEUR_ECRAN};
    SDL_Rect R_imageTitle = {0,0,0,0};

    SDL_QueryTexture(T_imageTitle, NULL, NULL, &R_imageTitle.w, &R_imageTitle.h);
    R_imageTitle.x = LARGEUR_ECRAN/2 - R_imageTitle.w/2;
    R_imageTitle.y = ((HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100)/2-R_imageTitle.h/2;


    SDL_RenderCopy(rendu, T_imageFond, NULL, &R_imageFond);
    SDL_RenderCopy(rendu, T_imageTitle, NULL, &R_imageTitle);

    SDL_FreeSurface(imageTitle);
    SDL_DestroyTexture(T_imageTitle);
    SDL_FreeSurface(imageFond);
    SDL_DestroyTexture(T_imageFond);

    /************************************************************************************/

    int ecartCase = TAILLE_BUTTON_MENU_PRINCIPAL_Y + 55;

    //Rectangle plein
    // {posX, posY, TAILLE_X, TAILLE_Y}
    SDL_Rect rect = {LARGEUR_ECRAN/2 - TAILLE_BUTTON_MENU_PRINCIPAL_X/2, (HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100, TAILLE_BUTTON_MENU_PRINCIPAL_X, TAILLE_BUTTON_MENU_PRINCIPAL_Y};

    SDL_SetRenderDrawColor (rendu, 100, 100, 100, 200);

    for (int i = 0 ; i < NB_BUTTON_MENU_PRINCIPAL ; i++) {
        SDL_RenderFillRect(rendu, &rect);
        rect.y += ecartCase;
    }

    SDL_Color couleur = {255, 255, 255};
    SDL_Surface * surface = TTF_RenderText_Solid(police, "Touches", couleur);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(rendu, surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {rect.x + 150, HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 115, texW, texH };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);


    dstrect.x += 30;
    dstrect.y += ecartCase;
    surface = TTF_RenderText_Solid(police, "Volume", couleur);
    texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    dstrect.w = texW;
    dstrect.h = texH;
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);


    dstrect.x += 5;
    dstrect.y += ecartCase;
    surface = TTF_RenderText_Solid(police, "Regles", couleur);
    texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    dstrect.w = texW;
    dstrect.h = texH;
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    /******************** AFFICHE LE BOUTON RETURN EN BAS A DROITE ***************************/

    SDL_Rect rectReturn = {LARGEUR_ECRAN - 150, HAUTEUR_ECRAN - 150, 64, 64} ;
    SDL_Surface * imageReturn = IMG_Load("./img/return.png");
    SDL_Texture * T_imageReturn = SDL_CreateTextureFromSurface(rendu, imageReturn);
    SDL_QueryTexture(T_imageReturn, NULL, NULL, &rectReturn.w, &rectReturn.h);
    SDL_RenderCopy(rendu, T_imageReturn, NULL, &rectReturn);

    SDL_DestroyTexture(T_imageReturn);
    SDL_FreeSurface(imageReturn);

}


void AfficherMenuTouches(SDL_Renderer * rendu, TTF_Font * police) {

    /******************** AFFICHE LE FOND D'ECRAN ET LE TITLE ***************************/
    
    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 255);
    SDL_RenderClear(rendu);

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

    SDL_Surface * imageFond = IMG_Load("./img/fondecran.jpg");
    SDL_Surface * imageTitle = IMG_Load("./img/ROGUELIKE.png");

    SDL_Texture * T_imageFond = SDL_CreateTextureFromSurface(rendu, imageFond);
    SDL_Texture * T_imageTitle = SDL_CreateTextureFromSurface(rendu, imageTitle);

    SDL_Rect R_imageFond = {0,0,LARGEUR_ECRAN,HAUTEUR_ECRAN};
    SDL_Rect R_imageTitle = {0,0,0,0};

    SDL_QueryTexture(T_imageTitle, NULL, NULL, &R_imageTitle.w, &R_imageTitle.h);
    R_imageTitle.x = LARGEUR_ECRAN/2 - R_imageTitle.w/2;
    R_imageTitle.y = ((HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL) - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 100)/2-R_imageTitle.h/2;


    SDL_RenderCopy(rendu, T_imageFond, NULL, &R_imageFond);
    SDL_RenderCopy(rendu, T_imageTitle, NULL, &R_imageTitle);

    SDL_FreeSurface(imageTitle);
    SDL_DestroyTexture(T_imageTitle);
    SDL_FreeSurface(imageFond);
    SDL_DestroyTexture(T_imageFond);

    /************************************************************************************/

    SDL_SetRenderDrawColor (rendu, 100, 100, 100, 200);

    SDL_Rect rect = {100, HAUTEUR_ECRAN/2 - 150, 550, 60};

    int ecartCase = 75;

    for (int i = 0 ; i < 4 ; i++) {
        SDL_RenderFillRect(rendu, &rect);
        rect.y += ecartCase;
    }

     SDL_Color couleur = {255, 255, 255};
    SDL_Surface * surface = TTF_RenderText_Solid(police, "Touches", couleur);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(rendu, surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {rect.x + 150, HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 115, texW, texH };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);


    SDL_Color couleur = {255, 255, 255};
    SDL_Surface * surface = TTF_RenderText_Solid(police, "attaque : click g ", couleur);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(rendu, surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {rect.x + 15 , HAUTEUR_ECRAN/1.5 - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 120, texW, texH };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

 SDL_Color couleur = {255, 255, 255};
    SDL_Surface * surface = TTF_RenderText_Solid(police, "Touches", couleur);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(rendu, surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {rect.x + 150, HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 115, texW, texH };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

 SDL_Color couleur = {255, 255, 255};
    SDL_Surface * surface = TTF_RenderText_Solid(police, "Touches", couleur);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(rendu, surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {rect.x + 150, HAUTEUR_ECRAN/NB_BUTTON_MENU_PRINCIPAL - TAILLE_BUTTON_MENU_PRINCIPAL_Y + 115, texW, texH };
    SDL_RenderCopy(rendu, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
	

    rect.x = LARGEUR_ECRAN/2 + (LARGEUR_ECRAN/2 - 400);
    rect.y = HAUTEUR_ECRAN/2 - 150;

    /******************** AFFICHE LE BOUTON RETURN EN BAS A DROITE ***************************/

    SDL_Rect rectReturn = {LARGEUR_ECRAN - 150, HAUTEUR_ECRAN - 125, 64, 64} ;
    SDL_Surface * imageReturn = IMG_Load("./img/return.png");
    SDL_Texture * T_imageReturn = SDL_CreateTextureFromSurface(rendu, imageReturn);
    SDL_QueryTexture(T_imageReturn, NULL, NULL, &rectReturn.w, &rectReturn.h);
    SDL_RenderCopy(rendu, T_imageReturn, NULL, &rectReturn);

    SDL_DestroyTexture(T_imageReturn);
    SDL_FreeSurface(imageReturn);
}


/**
    \brief Permet, dans le menu choisi, de séléctionner une intéraction en cliquant sur un des boutons
*/
Menu choixMenu (Menu menuActuel) {

    
	SDL_Event event;
	SDL_PollEvent(&event);

	//Menu principal #1
	if (menuActuel == Principal) {
		switch (event.type) {
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:		
						if ((event.button.y >= 250 && event.button.y <= 350) && (event.button.x >= 200 && event.button.x <= 800)) { //Bouton 1
							return New;
						}
						else if ((event.button.y >= 410 && event.button.y <= 510) && (event.button.x >= 200 && event.button.x <= 800)) { //Bouton 2
							return Load;
						}
						else if ((event.button.y >= 565 && event.button.y <= 660) && (event.button.x >= 200 && event.button.x <= 800)) { //Bouton 3
							return Quit;
						}
                        else if ((event.button.y >= 602 && event.button.y <= 664) && (event.button.x >= 850 && event.button.x <= 914)) { //Bouton Setting
                            return Setting;
                        }
						break;
					default:
						break;
				}
				break;
			case SDL_QUIT:
				return Quit;
			default:
				return Principal;
		}
	}
    else if (menuActuel == Load) {
        FILE * fichier;
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                    	if ((event.button.y >= 250 && event.button.y <= 350) && (event.button.x >= 200 && event.button.x <= 800)) { //Save 1
                            fichier = fopen("./saves/Save1.txt", "r");
                            if (fichier != NULL) {
                                fclose(fichier);
                                return Save1; 
                            }
						}
						else if ((event.button.y >= 410 && event.button.y <= 510) && (event.button.x >= 200 && event.button.x <= 800)) { //Save 2
							fichier = fopen("./saves/Save2.txt", "r");
                            if (fichier != NULL) {
                                fclose(fichier);
                                return Save2; 
                            }
						}
						else if ((event.button.y >= 560 && event.button.y <= 660) && (event.button.x >= 200 && event.button.x <= 800)) { //Save 3
							fichier = fopen("./saves/Save3.txt", "r");
                            if (fichier != NULL) {
                                fclose(fichier);
                                return Save3; 
                            }
						}
                        else if ((event.button.y >= 602 && event.button.y <= 664) && (event.button.x >= 850 && event.button.x <= 914)) { //Bouton return
                            return Principal;
                        }
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                return Quit;
            default:
                return Load;
                break;
        }
    }
    else if (menuActuel == Setting) {
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                    	if ((event.button.y >= 250 && event.button.y <= 350) && (event.button.x >= 200 && event.button.x <= 800)) { //Touches
                            return Touches;
						}
						else if ((event.button.y >= 410 && event.button.y <= 510) && (event.button.x >= 200 && event.button.x <= 800)) { //Volume
							return Volume;
						}
						else if ((event.button.y >= 560 && event.button.y <= 660) && (event.button.x >= 200 && event.button.x <= 800)) { //Save 3
							
						}
                        else if ((event.button.y >= 602 && event.button.y <= 664) && (event.button.x >= 850 && event.button.x <= 914)) { //Bouton return
                            return Principal;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                return Quit;
            default:
                return Setting;
                break;
        }
    }
    else if (menuActuel == Volume) {
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        if (event.button.x >= 200 && event.button.x <= 800 && event.button.y > 367 && event.button.y < 393) {
                            int choix = event.button.x - 200;
                            VOLUME = (choix * MIX_MAX_VOLUME)/TAILLE_BUTTON_MENU_PRINCIPAL_X;
                            Mix_VolumeMusic(VOLUME);
                            SauvegarderSon();
                        }
                        else if ((event.button.y >= 602 && event.button.y <= 664) && (event.button.x >= 850 && event.button.x <= 914)) { //Bouton return
                            return Setting;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                return Quit;
            default:
                return Volume; 
                break;
        }
    }
    else if (menuActuel == Touches) {
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        if ((event.button.y >= 602 && event.button.y <= 664) && (event.button.x >= 850 && event.button.x <= 914)) { //Bouton return
                            return Setting;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                return Quit;
            default:
                return Touches;
        }
    }

	return Aucun;
}








/******************** IN GAME ********************/


/** \brief Nous permet d'afficher le menu de sauvegarde en jeu*/
void AfficherMenuSauvegardeIG (SDL_Renderer * rendu, TTF_Font * police) {

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

    SDL_Color couleur = {255, 255, 255};
    SDL_Surface *texte = NULL;
    SDL_Texture * texture = NULL;
    SDL_Rect rect = {LARGEUR_ECRAN/2 - TAILLE_BUTTON_MENU_IG_X/2, (HAUTEUR_ECRAN/NB_BUTTON_MENU_IG) - TAILLE_BUTTON_MENU_PRINCIPAL_Y, TAILLE_BUTTON_MENU_IG_X, TAILLE_BUTTON_MENU_IG_Y};

    int texW = 0;
    int texH = 0;


    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 200);

    //Btn Resume
    SDL_RenderFillRect(rendu, &rect);
    texte = TTF_RenderText_Solid(police, "Sauvegarde 1", couleur);
    texture = SDL_CreateTextureFromSurface(rendu, texte);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH); //On va savoir la taille exacte de la texture pour pas la redimensionner 
    rect.x += 10;
    rect.y += 15;
    rect.w = texW;
    rect.h = texH;
    SDL_RenderCopy(rendu, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(texte);


     //Btn Quit
    rect.x -= 10;
    rect.y += 150;
    rect.w = TAILLE_BUTTON_MENU_IG_X;
    rect.h = TAILLE_BUTTON_MENU_IG_Y;
    SDL_RenderFillRect(rendu, &rect);
    texte = TTF_RenderText_Solid(police, "Sauvegarde 2", couleur);
    texture = SDL_CreateTextureFromSurface(rendu, texte);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH); //On va savoir la taille exacte de la texture pour pas la redimensionner 
    rect.x += 10;
    rect.y += 15;
    rect.w = texW;
    rect.h = texH;
    SDL_RenderCopy(rendu, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(texte);


    //Btn Quit
    rect.x -= 10;
    rect.y += 150;
    rect.w = TAILLE_BUTTON_MENU_IG_X;
    rect.h = TAILLE_BUTTON_MENU_IG_Y;
    SDL_RenderFillRect(rendu, &rect);
    texte = TTF_RenderText_Solid(police, "Sauvegarde 3", couleur);
    texture = SDL_CreateTextureFromSurface(rendu, texte);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH); //On va savoir la taille exacte de la texture pour pas la redimensionner 
    rect.x += 10;
    rect.y += 15;
    rect.w = texW;
    rect.h = texH;
    SDL_RenderCopy(rendu, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(texte);

    rect.x -= 10;

    SDL_SetRenderDrawColor (rendu, 20, 20, 20, 100);
    FILE * fichier = NULL;

    rect.y = (HAUTEUR_ECRAN/NB_BUTTON_MENU_IG) - TAILLE_BUTTON_MENU_IG_Y;
    rect.w = TAILLE_BUTTON_MENU_IG_X;
    rect.h = TAILLE_BUTTON_MENU_IG_Y;
    fichier = fopen("./saves/Save1.txt", "r");
    if (fichier == NULL) {
        SDL_RenderFillRect(rendu, &rect);
    }
    else {
        fclose(fichier);
    }

    rect.y += 165;
    fichier = fopen("./saves/Save2.txt", "r");
    if (fichier == NULL) {
        SDL_RenderFillRect(rendu, &rect);
    }
    else {
        fclose(fichier);
    }

    rect.y += 165;
    fichier = fopen("./saves/Save3.txt", "r");
    if (fichier == NULL) {
        SDL_RenderFillRect(rendu, &rect);
    }
    else {
        fclose(fichier);
    }


    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 200);

    SDL_Rect rectReturn = {LARGEUR_ECRAN - 300, HAUTEUR_ECRAN - 150, rect.w/2, rect.h} ;
    SDL_RenderFillRect(rendu, &rectReturn);

    rect.x = rectReturn.x + 5;
    rect.y = rectReturn.y + 15;
    texte = TTF_RenderText_Solid(police, "Retour", couleur);
    texture = SDL_CreateTextureFromSurface(rendu, texte);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    rect.w = texW;
    rect.h = texH;
    SDL_RenderCopy(rendu, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(texte);


    SDL_RenderPresent(rendu);
}




/**
    \brief Affichage du menu In Game. Réalise aussi le traitement du choix du joueur : - Resume : Reprend la partie - Quit : Menu principal

    \return 0 si Resume
    \return 1 si Menu Principal
    \return 2 si Quit
*/
void AfficherMenuIG(SDL_Renderer * rendu, TTF_Font * police) {

    SDL_SetRenderDrawBlendMode(rendu, SDL_BLENDMODE_BLEND);

    SDL_Color couleur = {255, 255, 255};
    SDL_Surface *texte = NULL;
    SDL_Texture * texture = NULL;
    SDL_Rect rect = {LARGEUR_ECRAN/2 - TAILLE_BUTTON_MENU_IG_X/2, (HAUTEUR_ECRAN/NB_BUTTON_MENU_IG) - TAILLE_BUTTON_MENU_PRINCIPAL_Y, TAILLE_BUTTON_MENU_IG_X, TAILLE_BUTTON_MENU_IG_Y};

    int texW = 0;
    int texH = 0;


    SDL_SetRenderDrawColor (rendu, 102, 20, 20, 200);

    //Btn Resume
    SDL_RenderFillRect(rendu, &rect);
    texte = TTF_RenderText_Solid(police, "Reprendre", couleur);
    texture = SDL_CreateTextureFromSurface(rendu, texte);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH); //On va savoir la taille exacte de la texture pour pas la redimensionner 
    rect.x += 55;
    rect.y += 15;
    rect.w = texW;
    rect.h = texH;
    SDL_RenderCopy(rendu, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(texte);


     //Btn Quit
    rect.x -= 55;
    rect.y += 150;
    rect.w = TAILLE_BUTTON_MENU_IG_X;
    rect.h = TAILLE_BUTTON_MENU_IG_Y;
    SDL_RenderFillRect(rendu, &rect);
    texte = TTF_RenderText_Solid(police, "Sauvegarder", couleur);
    texture = SDL_CreateTextureFromSurface(rendu, texte);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH); //On va savoir la taille exacte de la texture pour pas la redimensionner 
    rect.x += 20;
    rect.y += 15;
    rect.w = texW;
    rect.h = texH;
    SDL_RenderCopy(rendu, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(texte);


    //Btn Quit
    rect.x -= 20;
    rect.y += 150;
    rect.w = TAILLE_BUTTON_MENU_IG_X;
    rect.h = TAILLE_BUTTON_MENU_IG_Y;
    SDL_RenderFillRect(rendu, &rect);
    texte = TTF_RenderText_Solid(police, "Quitter", couleur);
    texture = SDL_CreateTextureFromSurface(rendu, texte);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH); //On va savoir la taille exacte de la texture pour pas la redimensionner 
    rect.x += 100;
    rect.y += 15;
    rect.w = texW;
    rect.h = texH;
    SDL_RenderCopy(rendu, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(texte);

    SDL_RenderPresent(rendu);
}



MenuIG choixMenuIG (SDL_Renderer * rendu, TTF_Font * police, MenuIG menuActuel) {

    SDL_Event event;

    //On ne change rien au jeu tant que le joueur reste dans le menu
    SDL_PollEvent(&event);

    if (menuActuel == Premier) {
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch(event.button.button) {
                    case SDL_BUTTON_LEFT:
                        if (event.button.y >= 150 && event.button.y <= 250 && event.button.x >= 275 && event.button.x <= 725) { //Si clic sur bouton resume
                            return Resume;
                        }
                        else if (event.button.y >= 320 && event.button.y <= 420 && event.button.x >= 275 && event.button.x <= 725) { //Si clic sur bouton save
                           return Sauvegarde;
                        }
                        else if (event.button.y >= 490 && event.button.y <= 590 && event.button.x >= 275 && event.button.x <= 725) { //Si clic sur bouton quit
                            return ReturnMenu;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYDOWN: //Si le joueur appuie sur ECHAP alors le jeu reprend
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        return Resume;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                return Quitter;
            default:
                break;
        }
    } 
    else if (menuActuel == Sauvegarde) {
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch(event.button.button) {
                    case SDL_BUTTON_LEFT:
                        if (event.button.y >= 150 && event.button.y <= 250 && event.button.x >= 275 && event.button.x <= 725) { //Si clic sur bouton save1
                            return Sauvegarde1;
                        }
                        else if (event.button.y >= 320 && event.button.y <= 420 && event.button.x >= 275 && event.button.x <= 725) { //Si clic sur bouton save2
                            return Sauvegarde2;
                        }
                        else if (event.button.y >= 490 && event.button.y <= 590 && event.button.x >= 275 && event.button.x <= 725) { //Si clic sur bouton save3
                            return Sauvegarde3;
                        }
                        else if (event.button.y >= 600 && event.button.y <= 700 && event.button.x >= 705 && event.button.x <= 925) { //Si clic sur bouton return
                            return Premier;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYDOWN: //Si le joueur appuie sur ECHAP alors le jeu reprend
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        return Resume;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                return Quitter;
                break;
            default:
                break;
        }
    }

    return 0;
}
