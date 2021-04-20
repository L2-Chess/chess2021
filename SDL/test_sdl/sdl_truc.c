#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>







int main(int argc, char* argv[]){

	SDL_Window* window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Surface *picture = NULL;
	SDL_Texture* texture = NULL;



	window = SDL_CreateWindow("Affichage avec SDL2_image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);


	picture = IMG_Load("./echec.jpg");

    texture = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);




	SDL_RenderCopy(renderer, texture, NULL, NULL);

	SDL_RenderPresent(renderer);
	while(1);
	printf("huehfe");
	clean_ressources(window, renderer, texture);
	return EXIT_SUCCESS;
}
