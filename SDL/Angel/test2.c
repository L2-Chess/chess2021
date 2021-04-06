// Inclure la bibliothèque SDL
#include <SDL.h>
#include <SDL_image.h>


// Inclusion des bibliothèque standard C
#include <stdio.h>
#include <stdlib.h>

int mouse_x;
int mouse_y;
int mouse_left;
int Action1 = 0;
int GrabMode = 0;
int PieceDrop = 0;
//int Action2 = 0;
//int Action3 = 0;
//int Action4 = 0;

int IsInSquare = 0;

//INIT DE TOUTES LES CASES

char CASE[2];



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

    //PIECE
    SDL_Rect square;
    square.x = 300;
    square.y = 200;
    square.w = 50;
    square.h = 50;


    // TOUTES LES CASES

    //A1
    SDL_Rect a1;
    a1.x = 50;
    a1.y = 600;
    a1.w = 100;
    a1.h = 100;
    
    //B1
    SDL_Rect b1;
    b1.x = 150;
    b1.y = 600;
    b1.w = 100;
    b1.h = 100;

    //C1
    SDL_Rect c1;
    c1.x = 250;
    c1.y = 600;
    c1.w = 100;
    c1.h = 100;

    //D1
    SDL_Rect d1;
    d1.x = 350;
    d1.y = 600;
    d1.w = 100;
    d1.h = 100;

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

                ///////////////////////////////
                if ((mouse_x > a1.x && mouse_x < a1.x + a1.w) && (mouse_y > a1.y && mouse_y < a1.y + a1.h)) {
                    CASE[0] = 'A';
                    CASE[1] = '1';
                }
                else if ((mouse_x > b1.x && mouse_x < b1.x + b1.w) && (mouse_y > b1.y && mouse_y < b1.y + b1.h)) {
                    CASE[0] = 'B';
                    CASE[1] = '1';
                }
                else if ((mouse_x > c1.x && mouse_x < c1.x + c1.w) && (mouse_y > c1.y && mouse_y < c1.y + c1.h)) {
                    CASE[0] = 'C';
                    CASE[1] = '1';
                }
                else if ((mouse_x > d1.x && mouse_x < d1.x + d1.w) && (mouse_y > d1.y && mouse_y < d1.y + d1.h)) {
                    CASE[0] = 'D';
                    CASE[1] = '1';
                }
                else {
                    CASE[0] = 'R';
                    CASE[1] = 'R';
                }
                
           
                SDL_Log("Mouse x = %i , Mouse y = %i , IIS1 = %i , CASE = %s, GRAB = %i , PIECE_DROP = %i", mouse_x, mouse_y, IsInSquare, CASE, GrabMode, PieceDrop);


                

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
                
               //VALEURE SAVOIR CASE DE DEPART

               
               break;
                
            case SDL_MOUSEBUTTONUP:

                if (GrabMode == 1) {
                    switch (CASE[0])
                    {
                    case 'A':
                        switch (CASE[1])
                        {
                        case '1':
                            square.x = a1.x + (a1.w / 4);
                            square.y = a1.y + (a1.h / 4);
                            break;
                        case '2':
                            break;
                        case '3':
                            break;
                        case '4':
                            break;
                        case '5':
                            break;
                        case '6':
                            break;
                        case '7':
                            break;
                        case '8':
                            break;
                        }
                        break;
                    case 'B':
                        switch (CASE[1])
                        {
                        case '1':
                            square.x = b1.x + (b1.w / 4);
                            square.y = b1.y + (b1.h / 4);
                            break;
                        case '2':
                            break;
                        case '3':
                            break;
                        case '4':
                            break;
                        case '5':
                            break;
                        case '6':
                            break;
                        case '7':
                            break;
                        case '8':
                            break;
                        }
                        break;
                    case 'C':
                        switch (CASE[1])
                        {
                        case '1':
                            square.x = c1.x + (c1.w / 4);
                            square.y = c1.y + (c1.h / 4);
                            break;
                        case '2':
                            break;
                        case '3':
                            break;
                        case '4':
                            break;
                        case '5':
                            break;
                        case '6':
                            break;
                        case '7':
                            break;
                        case '8':
                            break;
                        }
                        break;
                    case 'D':
                        switch (CASE[1])
                        {
                        case '1':
                            square.x = d1.x + (d1.w / 4);
                            square.y = d1.y + (d1.h / 4);
                            break;
                        case '2':
                            break;
                        case '3':
                            break;
                        case '4':
                            break;
                        case '5':
                            break;
                        case '6':
                            break;
                        case '7':
                            break;
                        case '8':
                            break;
                        }
                        break;
                    }
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



        //RENDER DES CASES
        //
        //
        //
        //NOIR
        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
        SDL_RenderFillRect(pRenderer, &a1);
        SDL_RenderFillRect(pRenderer, &c1);
        //BLANC
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 0);
        SDL_RenderFillRect(pRenderer, &b1);
        SDL_RenderFillRect(pRenderer, &d1);

        //
        //
        //

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