#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>
#define changer_pixel(x,y,couleur) if(dans_ecran(x,y))  *((Uint32 *)ecran->pixels + y*largeur_fenetre + x) = couleur
typedef struct cases {int x,y, joueur, piece, couleur,a_bouge,a_bouge_au_tour_prececent,position_precedente_x,position_precedente_y;} CASES;

void clean_ressources(SDL_Window* w, SDL_Renderer* r, SDL_Texture* t) {

	if (t != NULL) {
		SDL_DestroyTexture(t);
	}
	if (t != NULL) {
		SDL_DestroyRenderer(r);
	}
	if (t != NULL) {
		SDL_DestroyWindow(w);
	}
	SDL_Quit();
}

void dessiner_rectangle(Uint32 couleur, int x_min,int y_min,int x_max,int y_max)
{
	int x,y;

	for (x=x_min;x<=x_max;x++)
	{
		for (y=y_min;y<=y_max;y++)
		{
			changer_pixel(x,y,couleur);
		}
	}
}


void dessiner_case_damier(int x,int y)
{
	if(!(x>=0 && x<8 && y>=0 && y<8))
	{
		printf("erreur ! dessiner_case_damier() : x et y invalides. x=�%d, y=%d\n",x,y);
		return ;
	}

	int xmin=cases[x][y].x-50, xmax=cases[x][y].x+50, ymin=cases[x][y].y-50, ymax=cases[x][y].y+50;
	Uint32 couleur;
	if((x+y)%2==0) couleur=gris;
	else couleur=blanc;
	dessiner_rectangle(couleur,xmin,ymin,xmax,ymax);
}





int main(int argc, char* argv[]){

	SDL_Window* window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Surface *picture = NULL;
	SDL_Texture* texture = NULL;



	window = SDL_CreateWindow("Affichage avec SDL2_image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);


	picture = IMG_Load("./pink.jpg");
	// picture=SDL_CreateRGBSurface(0, 1920, 1080, 32, 0,0,0,0);//Cr�ation d'une surface noir permettant de contenir le texte de d�marage du jeu

	if (renderer == NULL) {
		SDL_Log("ERREUR > %s\n", SDL_GetError());
		clean_ressources(window, renderer, NULL);
		exit(EXIT_FAILURE);
	}

	texture = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_FreeSurface(picture);
	if (texture == NULL) {
		SDL_Log("ERREUR > %s\n", SDL_GetError());
		clean_ressources(window, renderer, NULL);
		exit(EXIT_FAILURE);
	}

	SDL_RenderCopy(renderer, texture, NULL, NULL);

	SDL_RenderPresent(renderer);
	while(1);
	printf("huehfe");
	clean_ressources(window, renderer, texture);
	return EXIT_SUCCESS;
}
