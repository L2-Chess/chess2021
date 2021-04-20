#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>


#define WIDTHSCREEN 800

#define HEIGHTSCREEN 600

#define TOTAL_PO INTS 5000

int main(int argc, char* argv[])
{
     if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (TTF_Init() < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window* pWindow=NULL;
    SDL_Renderer* pRenderer= NULL;

     if (SDL_CreateWindowAndRenderer(WIDTHSCREEN, HEIGHTSCREEN, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Event events;
    float isOpen=1;


    TTF_Font* font = TTF_OpenFont("arial.ttf", 24); // Crée une police avec la police "ariali.ttf" et de taille 18 pixels
    TTF_Font* font1 = TTF_OpenFont("arial.ttf", 52); // Crée une police avec la police "ariali.ttf" et de taille 18 pixels

    if (font == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());

    }
    SDL_Color color= { 0, 255, 0 };
    SDL_Surface* text = TTF_RenderText_Blended(font, "Jouer",color); // Crée un surface qui contient le texte
    SDL_Surface* text1 = TTF_RenderText_Blended(font, "Jeu d'échecs",color); // Crée un surface qui contient le texte

    if (text == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, text); // Crée la texture qu'on va afficher a partir de la surface
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(pRenderer, text1); // Crée la texture qu'on va afficher a partir de la surface


    if (texture == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
    }

    SDL_Rect position;
    SDL_Rect position1;

    SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h); // Récupere la dimension de la texture
    SDL_QueryTexture(texture1, NULL, NULL, &position1.w, &position1.h); // Récupere la dimension de la texture

    // Centre la texture sur l'écran
    position.x = WIDTHSCREEN / 2 - position.w / 2;
    position.y = HEIGHTSCREEN / 2 - position.h / 2;

    position1.x = WIDTHSCREEN  - position1.w 2;
    position1.y = HEIGHTSCREEN - position1.h 2;



    // Libération des resource de la police et de la surface qui contient le texte
    SDL_FreeSurface(text);
    SDL_FreeSurface(text1);
    TTF_CloseFont(font);


     while (isOpen)
    {
         while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                isOpen = 0;
                break;
            }
        }


        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(pRenderer);

        SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
        SDL_RenderCopy(pRenderer, texture, NULL, &position);
        SDL_RenderCopy(pRenderer, texture1, NULL, &position1);

        SDL_RenderPresent(pRenderer);
    }


    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture1);
     SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
