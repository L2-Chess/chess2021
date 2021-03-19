// Inclure la bibliothèque SDL
#include <SDL.h>


// Inclusion des bibliothèque standard C
#include <stdio.h>
#include <stdlib.h>

int mouse_x;
int mouse_y;
int IsInSquare = 0;
int mouse_left;
int Action1 = 0;

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window* pWindow = NULL;
    SDL_Renderer* pRenderer = NULL;

    if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN , &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Event events;
    float isOpen = 1;

    //creation rectangle
    SDL_Rect square;
    square.x = 300;
    square.y = 200;
    square.w = 200;
    square.h = 50;


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
                if ( (mouse_x > square.x && mouse_x < square.x + square.w)  &&  (mouse_y > square.y && mouse_y < square.y + square.h) ) {
                    IsInSquare = 1;
                }
                else {
                    IsInSquare = 0;
                }

                SDL_Log("Mouse x = %i , Mouse y = %i , IsInSquare = %i", mouse_x, mouse_y, IsInSquare);
                break;

            case SDL_MOUSEBUTTONDOWN:

                if ( SDL_BUTTON(SDL_BUTTON_LEFT) && IsInSquare == 0) {
                    mouse_left = 1;
                    SDL_Log("LE BOUTON GAUCHE EST CLIQUE");
                }
                else if (IsInSquare == 1 && mouse_left == 1) {
                    SDL_Log("EXECUTER ACTION");
                    if (Action1 == 0) {
                        Action1 = 1;
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

        //POINT
        //SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
        //SDL_RenderDrawPoint(pRenderer, 200, 200);

        
        
        //rectangle couleur
        SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 0);

        //render rectangle
        SDL_RenderFillRect(pRenderer, &square);

        SDL_RenderPresent(pRenderer);


        SDL_Delay(20);
    }


    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return EXIT_SUCCESS;

}