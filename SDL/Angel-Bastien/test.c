// Inclure la biblioth�que SDL
#include <SDL.h>
#include <SDL_image.h>


// Inclusion des biblioth�que standard C
#include <stdio.h>
#include <stdlib.h>

int mouse_x;
int mouse_y;
int IsInSquare = 0;
int IsInSquare2 = 0;
int IsInSquare3 = 0;
int IsInSquare4 = 0;
int mouse_left;
int Action1 = 0;
//int Action2 = 0;
//int Action3 = 0;
//int Action4 = 0;


int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window* pWindow = NULL;
    SDL_Renderer* pRenderer = NULL;
    SDL_Surface* pSurface = NULL;
    SDL_Texture* pTexture = NULL;

    if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN , &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }


    pSurface = IMG_Load("./somefile.bmp");

    pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    SDL_FreeSurface(pSurface);

    SDL_Event events;
    float isOpen = 1;

    //creation rectangle 1
    SDL_Rect square;
    square.x = 300;
    square.y = 200;
    square.w = 200;
    square.h = 50;

    //creation rectangle 2
    SDL_Rect square2;
    square2.x = 300;
    square2.y = 300;
    square2.w = 200;
    square2.h = 50;

    //creation rectangle 3
    SDL_Rect square3;
    square3.x = 300;
    square3.y = 400;
    square3.w = 200;
    square3.h = 50;

    //creation rectangle 4
    SDL_Rect square4;
    square4.x = 300;
    square4.y = 500;
    square4.w = 200;
    square4.h = 50;


    while (isOpen)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                isOpen = 0;
                break;

            case SDL_MOUSEMOTION:

                SDL_GetMouseState(&mouse_x, &mouse_y);
                //rectangle premier
                if ( (mouse_x > square.x && mouse_x < square.x + square.w)  &&  (mouse_y > square.y && mouse_y < square.y + square.h) ) {
                    IsInSquare = 1;
                }
                else {
                    IsInSquare = 0;
                }
                //rectangle deucieme
                if ((mouse_x > square2.x && mouse_x < square2.x + square2.w) && (mouse_y > square2.y && mouse_y < square2.y + square2.h)) {
                    IsInSquare2 = 1;
                }
                else {
                    IsInSquare2 = 0;
                }

                //rectangle 3
                if ((mouse_x > square3.x && mouse_x < square3.x + square3.w) && (mouse_y > square3.y && mouse_y < square3.y + square3.h)) {
                    IsInSquare3 = 1;
                }
                else {
                    IsInSquare3 = 0;
                }

                //rectangle 4
                if ((mouse_x > square4.x && mouse_x < square4.x + square4.w) && (mouse_y > square4.y && mouse_y < square4.y + square4.h)) {
                    IsInSquare4 = 1;
                }
                else {
                    IsInSquare4 = 0;
                }

                SDL_Log("Mouse x = %i , Mouse y = %i , IIS1 = %i , IIS2 = %i , IIS3 = %i , IIS4 = %i", mouse_x, mouse_y, IsInSquare, IsInSquare2, IsInSquare3, IsInSquare4);
                break;

            case SDL_MOUSEBUTTONDOWN:

                if ( SDL_BUTTON(SDL_BUTTON_LEFT) && IsInSquare == 0 && IsInSquare2 == 0 && IsInSquare3 == 0 && IsInSquare4 == 0) {
                    mouse_left = 1;
                    SDL_Log("LE BOUTON GAUCHE EST CLIQUE");
                }
                else if (IsInSquare == 1 && mouse_left == 1) {
                    SDL_Log("COULEUR ROUGE");
                    if (Action1 == 0) {
                        Action1 = 1;
                    }
                    else {
                        Action1 = 0;
                    }
                }
                else if (IsInSquare2 == 1 && mouse_left == 1) {
                    SDL_Log("COULEUR BLANCHE");
                    if (Action1 == 0) {
                        Action1 = 2;
                    }
                    else {
                        Action1 = 0;
                    }
                }
                else if (IsInSquare3 == 1 && mouse_left == 1) {
                    SDL_Log("COULEUR BLEU");
                    if (Action1 == 0) {
                        Action1 = 3;
                    }
                    else {
                        Action1 = 0;
                    }
                }
                else if (IsInSquare4 == 1 && mouse_left == 1) {
                    SDL_Log("QUITTER");
                    if (Action1 == 0) {
                        Action1 = 4;
                    }else {
                        Action1 = 0;
                    }
                }else  {
                    mouse_left = 0;
                }


            /*case SDL_MOUSEWHEEL:

                if (events.wheel.y > 0) // scroll up
                {
                    square.x = square.x - 4;
                }
                else if (events.wheel.y < 0) // scroll down
                {
                    square.x = square.x + 4;
                }
                break;*/
            }
        }

        //FOND
        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(pRenderer);

        if (Action1 == 1) {
            SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
            SDL_RenderClear(pRenderer);
        }
        else if (Action1 == 0) {
            SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
            SDL_RenderClear(pRenderer);
        }
        else if (Action1 == 2) {
            SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
            SDL_RenderClear(pRenderer);
        }
        else if (Action1 == 3) {
            SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
            SDL_RenderClear(pRenderer);
        }
        else if (Action1 == 4) {
            isOpen = 0;
        }

        //POINT
        //SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
        //SDL_RenderDrawPoint(pRenderer, 200, 200);

        SDL_RenderCopy(pRenderer, pTexture, NULL, NULL);

        //rectangle couleur
        SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 0);

        //render rectangle
        SDL_RenderDrawRect(pRenderer, &square);

        SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 0);

        SDL_RenderDrawRect(pRenderer, &square2);

        SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 0);

        SDL_RenderDrawRect(pRenderer, &square3);

        SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 0);

        SDL_RenderDrawRect(pRenderer, &square4);

        SDL_RenderPresent(pRenderer);




        SDL_Delay(20);
    }


    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return EXIT_SUCCESS;

}
