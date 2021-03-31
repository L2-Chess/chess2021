// Inclure la bibliothèque SDL
#include <SDL.h>
#include <SDL_image.h>


// Inclusion des bibliothèque standard C
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
int GrabMode = 0;
int PieceDrop = 0;
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

    //SDL_Texture* pTexture1 = NULL;

    

    

    if (SDL_CreateWindowAndRenderer(1280, 720, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }


    pSurface = IMG_Load("./echec_background.jpg");
    pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    



    /*SDL_Surface* image1 = IMG_Load("./pion_blanc.jpg");
    pTexture1 = SDL_CreateTextureFromSurface(pRenderer, image1);
    

    //IMAGE1
    SDL_Rect image1_pos;
    image1_pos.x = 0;
    image1_pos.y = 0;
    image1_pos.w = 50;
    image1_pos.h = 50;*/
   

    SDL_Event events;
    float isOpen = 1;

    //creation rectangle 1
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
                //rectangle premier
                if ((mouse_x > square.x && mouse_x < square.x + square.w) && (mouse_y > square.y && mouse_y < square.y + square.h)) {
                    IsInSquare = 1;
                }
                else {
                    IsInSquare = 0;
                }
                

                SDL_Log("Mouse x = %i , Mouse y = %i , IIS1 = %i , GRAB = %i , PIECE_DROP = %i", mouse_x, mouse_y, IsInSquare, GrabMode, PieceDrop);


                

                break;



            case SDL_MOUSEBUTTONDOWN:
                PieceDrop == 0;
                GrabMode == 0;
                //drag and drop


               if (SDL_BUTTON_LEFT && IsInSquare == 0) {
                    mouse_left = 1;
                    SDL_Log("LE BOUTON GAUCHE EST CLIQUE");            
               }
               else if (SDL_BUTTON_LEFT && IsInSquare == 1) {
                   SDL_Log("GRAB");
                   if (GrabMode == 0) {
                       GrabMode = 1;
                   }
                   
               }
                
               
               break;
                
            case SDL_MOUSEBUTTONUP:

               
                

               if (GrabMode == 1) {
                    square.x = mouse_x - (square.w / 2);
                    square.y = mouse_y - (square.h / 2);
               }

               GrabMode = 0;
               break;


                /*case SDL_MOUSEWHEEL:

                    if (events.wheel.y > 0) // scroll up
                    {
                        square.x = square.x - 4;
                    }
                    else if (events.wheel.y < 0) // scroll down
                    {
                        square.x = square.x + 4;
                    }*/
                    
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

        //RENDER IMAGE BACKGROUND
        SDL_RenderCopy(pRenderer, pTexture, NULL, NULL);

        //IMAGE DRAW
        // SDL_RenderCopy(pRenderer, pTexture1, NULL, NULL);

        //POINT
        //SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
        //SDL_RenderDrawPoint(pRenderer, 200, 200);

        

        //RECTANGLE TEST
        SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 0);
        SDL_RenderFillRect(pRenderer, &square);

        SDL_RenderPresent(pRenderer);

        
        


        SDL_Delay(20);
    }


    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    //SDL_FreeSurface(image1);
    SDL_FreeSurface(pSurface);
    SDL_Quit();

    return EXIT_SUCCESS;

}