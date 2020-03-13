#include "animation.h"
#include <stdlib.h>


void ChargerCharset(SDL_Window * window, FILE * f, Animation * An) {
    char buffer[50];
    fscanf(f, "%s", buffer); //#Charset
    fscanf(f, "%s", buffer);
	An->charset = IMG_Load(buffer);
    fscanf(f,"%d %d",&(An->nbXChar),&(An->nbYChar));
	An->largeurChar = An->charset->w / An->nbXChar;
	An->hauteurChar = An->charset->h / An->nbYChar;
}


void ChargerSequence(FILE * f, Animation * An) {
    char buffer[50];
    AnimUnique * Anim;
    fscanf(f,"%s",buffer);  // #sequences
	fscanf(f,"%d %d",&(An->nbSens),&(An->nbStats));
	An->tab = malloc(An->nbSens * sizeof(AnimUnique*));
	for (int i = 0 ; i < An->nbSens ; i++) {
		An->tab[i] = malloc(An->nbStats * sizeof(AnimUnique));
		for(int j = 0 ; j < An->nbStats ; j++) {
			Anim = &(An->tab[i][j]);
			fscanf(f,"%d %d %d",&(Anim->depart),&(Anim->longeur),&(Anim->temps));
		}
	}
}

void LibererAnimation(Animation* An) {      
	for (int i = 0 ; i < An->nbSens ; i++) {
        free(An->tab[i]);
    }
	free(An->tab);
	SDL_FreeSurface(An->charset);
	free(An);
}


Animation * ChargerAnimation(SDL_Window *window, const char* fichier) {
    Animation * An = malloc(sizeof(Animation));

    FILE * f = fopen(fichier, "r");
    if (f == NULL) {
        printf("Erreur : Fichier %s introuvable\n", fichier);
        exit(1);
    }
    An = malloc(sizeof(Animation));
    ChargerCharset(window, f, An);
    ChargerSequence(f, An);
    fclose(f);
    return An;
}

void AffichageAnimation(Animation* An, SDL_Renderer * rendu, int sens, int stat, int x, int y) {
	int frame;
	SDL_Rect src,dst;
	AnimUnique* Anim;
	Anim = &(An->tab[sens][stat]);

	frame = Anim->depart + (SDL_GetTicks()/Anim->temps)%Anim->longeur;

	src.x = (frame%An->nbXChar) * An->largeurChar+20;
	src.y = (frame/An->nbXChar) * An->hauteurChar+15;
	src.w = An->largeurChar - 40;
	src.h = An->hauteurChar - 15;
    
	dst.h = src.h * 2;
	dst.w = src.w * 2;
    dst.x = x;
    dst.y = y;
	//SDL_RenderFillRect(rendu, &dst);
	SDL_Texture * T_charset = SDL_CreateTextureFromSurface(rendu, An->charset);
    SDL_RenderCopy(rendu, T_charset, &src, &dst);
    SDL_DestroyTexture(T_charset);
}