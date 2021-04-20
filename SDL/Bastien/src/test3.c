#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>


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


    TTF_Font* font = TTF_OpenFont("arial.ttf", 32); // Crée une police avec la police "ariali.ttf" et de taille 18 pixels
    TTF_Font* font1 = TTF_OpenFont("arial.ttf", 70); // Crée une police avec la police "ariali.ttf" et de taille 18 pixels

    int save = 0;
    SDL_Surface *picture = NULL;
    SDL_Color color= { 15, 5, 107 };
    SDL_Color color1= { 249, 234, 195 };
    SDL_Rect position= { 230,200, 230,200};
    SDL_Rect position1= { 330,200, 330,200};
    SDL_Rect position2= { 270,200, 270,200};
    SDL_Rect position3= { 100,200, 100,200};
    SDL_Rect position4= { 200,200, 200,200};

    SDL_Surface* text = NULL;
    SDL_Surface* buffer = NULL; // Crée un surface qui contient le texte
    SDL_Surface* final = SDL_CreateRGBSurface(0, WIDTHSCREEN, HEIGHTSCREEN, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

      text=TTF_RenderText_Blended(font, "Jouer 1vs1 local",color1);
      position.x = WIDTHSCREEN / 2 - position.w / 2;
      position.y = (HEIGHTSCREEN - 200) - (position.h / 2);
      position.w=text->w;
      position.h=text->h;
      SDL_BlitSurface(text,NULL,final,&position);
      SDL_FreeSurface(text);
      text=TTF_RenderText_Blended(font, "Jouer contre ordinateur",color1);
      position1.x = WIDTHSCREEN / 2 - position1.w / 2;
      position1.y = (HEIGHTSCREEN - 150 ) - (position1.h / 2)  ;
      position1.w=text->w;
      position1.h=text->h;
      SDL_BlitSurface(text,NULL,final,&position1);
      SDL_FreeSurface(text);
      text=TTF_RenderText_Blended(font, "Charger une partie",color1);
      position2.x = WIDTHSCREEN / 2 - position2.w / 2;
      position2.y = (HEIGHTSCREEN - 100) - (position2.h  / 2);
      position2.w=text->w;
      position2.h=text->h;
      SDL_BlitSurface(text,NULL,final,&position2);
      SDL_FreeSurface(text);
      text=TTF_RenderText_Blended(font, "Quitter",color1);
      position3.x = WIDTHSCREEN / 2 - position3.w / 2;
      position3.y = (HEIGHTSCREEN -50) - (position3.h / 2);
      position3.w=text->w;
      position3.h=text->h;
      SDL_BlitSurface(text,NULL,final,&position3);
      SDL_FreeSurface(text);
      text=TTF_RenderText_Blended(font1, "Chess",color);
      position4.x = WIDTHSCREEN / 2  - position4.w / 2;
      position4.y = HEIGHTSCREEN / 15 - position4.h / 15;
      position4.w=text->w;
      position4.h=text->h;
      SDL_BlitSurface(text,NULL,final,&position4);
      SDL_FreeSurface(text);
      save = SDL_SaveBMP(final, "somefile.bmp");


  SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, final); // Crée la texture qu'on va afficher a partir de la surface


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

        SDL_RenderCopy(pRenderer, texture, NULL, NULL);

        SDL_RenderPresent(pRenderer);
    }


     SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
