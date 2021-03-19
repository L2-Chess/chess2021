#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        return -1;
    }

    /* Création de la fenêtre */

    SDL_Window* pWindow = NULL;
    SDL_Renderer* pRenderer = NULL;

    if ( SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0);
    {
        fprintf(stdout, "Échec de l'initialisation de la fenetre (%s)\n", SDL_GetError());
        return -1;
    }

        
        
    SDL_Event event;
    float isOpen = 1;

    while (isOpen) {

        while (SDL_PollEvent(&event)) {

            switch (event.type) 
            {
            case SDL_QUIT:
                isOpen = 0;
                break;
            }
        }
        
        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(pRenderer);
     }

    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    
    SDL_Quit();

    return 0;

    //gcc sdl_truc.c -o sdl_truc -lmingw32 -lSDL2main -lSDL2
}