
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


#define WIDTHSCREEN 800

#define HEIGHTSCREEN 600

#define TOTAL_POINTS 5000


int main(int argc, char* argv[])
{
     if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }

     SDL_Window* pWindow=NULL;
    SDL_Renderer* pRenderer=NULL;

     if (SDL_CreateWindowAndRenderer(WIDTHSCREEN, HEIGHTSCREEN, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Event events;
    float isOpen = 1;

    SDL_Surface* image = IMG_Load("echec.jpg");
    SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(pRenderer, image);

    SDL_FreeSurface(image);
    SDL_Rect src1={0, 0, 0, 0};
    SDL_Rect src2={ 0, 0, 0, 0 };

    SDL_Rect dst1={ 0, 0, 400, 300 };
    SDL_Rect dst2={ WIDTHSCREEN - 100, HEIGHTSCREEN - 100, 100, 100};

    SDL_QueryTexture(pTextureImage, NULL, NULL, &src1.w, &src1.h);

    // Récuperer les bons coordonnées x et y pour afficher la tête du tigre
    src2.x = src1.w / 2 - 30;
    src2.y = src1.h / 2 - 50;
    src2.w = 50;
    src2.h = 50;


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

        SDL_RenderCopy(pRenderer, pTextureImage, &src1, &dst1); // Affiche la texture entièrement
        SDL_RenderCopy(pRenderer, pTextureImage, &src2, &dst2); // Affiche sur une partie de la texture

        SDL_RenderPresent(pRenderer);
    }

    SDL_DestroyTexture(pTextureImage);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return EXIT_SUCCESS;
}
