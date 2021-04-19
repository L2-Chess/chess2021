// Inclure la biblioth�que SDL
#include <SDL.h>
#include <SDL_image.h>


// Inclusion des biblioth�que standard C
#include <stdio.h>
#include <stdlib.h>


// Inclure la bibliotheque locale
#include "cases.h"



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


    if (SDL_CreateWindowAndRenderer(1280, 960, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

      SDL_SetWindowTitle(pWindow, "Jeu d'echecs - projet");



    pSurface = IMG_Load("./echec_local.png");
    pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);


    SDL_Texture* tab[13];
    //BLANC

    SDL_Surface* pion_b = IMG_Load("pieces/pion_blanc.png");
    SDL_Surface* tour_b = IMG_Load("pieces/tour_blanc.png");
    SDL_Surface* cavalier_b = IMG_Load("pieces/cavalier_blanc.png");
    SDL_Surface* fou_b = IMG_Load("pieces/fou_blanc.png");
    SDL_Surface* roi_b = IMG_Load("pieces/roi_blanc.png");
    SDL_Surface* reine_b = IMG_Load("pieces/reine_blanc.png");

    //NOIR
    SDL_Surface* pion_n = IMG_Load("pieces/pion_noir.png");
    SDL_Surface* tour_n = IMG_Load("pieces/tour_noir.png");
    SDL_Surface* cavalier_n = IMG_Load("pieces/cavalier_noir.png");
    SDL_Surface* fou_n = IMG_Load("pieces/fou_noir.png");
    SDL_Surface* roi_n = IMG_Load("pieces/roi_noir.png");
    SDL_Surface* reine_n = IMG_Load("pieces/reine_noir.png");
    SDL_Surface* echequier = IMG_Load("echec_local.png");


    tab[0]=SDL_CreateTextureFromSurface(pRenderer,pion_b);
    tab[1]=SDL_CreateTextureFromSurface(pRenderer,tour_b);
    tab[2]=SDL_CreateTextureFromSurface(pRenderer,cavalier_b);
    tab[3]=SDL_CreateTextureFromSurface(pRenderer,fou_b);
    tab[4]=SDL_CreateTextureFromSurface(pRenderer,roi_b);
    tab[5]=SDL_CreateTextureFromSurface(pRenderer,reine_b);

    tab[6]=SDL_CreateTextureFromSurface(pRenderer,pion_n);
    tab[7]=SDL_CreateTextureFromSurface(pRenderer,tour_n);
    tab[8]=SDL_CreateTextureFromSurface(pRenderer,cavalier_n);
    tab[9]=SDL_CreateTextureFromSurface(pRenderer,fou_n);
    tab[10]=SDL_CreateTextureFromSurface(pRenderer,roi_n);
    tab[11]=SDL_CreateTextureFromSurface(pRenderer,reine_n);
    tab[12]=SDL_CreateTextureFromSurface(pRenderer,echequier);


    SDL_FreeSurface(pion_b);
    SDL_FreeSurface(tour_b);
    SDL_FreeSurface(cavalier_b);
    SDL_FreeSurface(fou_b);
    SDL_FreeSurface(roi_b);
    SDL_FreeSurface(reine_b);
    SDL_FreeSurface(pion_n);
    SDL_FreeSurface(tour_n);
    SDL_FreeSurface(cavalier_n);
    SDL_FreeSurface(fou_n);
    SDL_FreeSurface(roi_n);
    SDL_FreeSurface(reine_n);
    SDL_FreeSurface(echequier);

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

    cases();


    //PIECES
    SDL_Rect square;
    square.x = a1.x + (a1.w / 4);
    square.y = a1.y + (a1.h / 4);
    square.w = 50;
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

                /////////////////////////////////////////////////////////////////////////////
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
                else if ((mouse_x > e1.x && mouse_x < e1.x + e1.w) && (mouse_y > e1.y && mouse_y < e1.y + e1.h)) {
                    CASE[0] = 'E';
                    CASE[1] = '1';
                }
                else if ((mouse_x > f1.x && mouse_x < f1.x + f1.w) && (mouse_y > f1.y && mouse_y < f1.y + f1.h)) {
                    CASE[0] = 'F';
                    CASE[1] = '1';
                }
                else if ((mouse_x > g1.x && mouse_x < g1.x + g1.w) && (mouse_y > g1.y && mouse_y < g1.y + g1.h)) {
                    CASE[0] = 'G';
                    CASE[1] = '1';
                }
                else if ((mouse_x > h1.x && mouse_x < h1.x + h1.w) && (mouse_y > h1.y && mouse_y < h1.y + h1.h)) {
                    CASE[0] = 'H';
                    CASE[1] = '1';
                }//////////////////////////////////////////////////////////////////////////
                else if ((mouse_x > a2.x && mouse_x < a2.x + a2.w) && (mouse_y > a2.y && mouse_y < a2.y + a2.h)) {
                    CASE[0] = 'A';
                    CASE[1] = '2';
                }
                else if ((mouse_x > b2.x && mouse_x < b2.x + b2.w) && (mouse_y > b2.y && mouse_y < b2.y + b2.h)) {
                    CASE[0] = 'B';
                    CASE[1] = '2';
                }
                else if ((mouse_x > c2.x && mouse_x < c2.x + c2.w) && (mouse_y > c2.y && mouse_y < c2.y + c2.h)) {
                    CASE[0] = 'C';
                    CASE[1] = '2';
                }
                else if ((mouse_x > d2.x && mouse_x < d2.x + d2.w) && (mouse_y > d2.y && mouse_y < d2.y + d2.h)) {
                    CASE[0] = 'D';
                    CASE[1] = '2';
                }
                else if ((mouse_x > e2.x && mouse_x < e2.x + e2.w) && (mouse_y > e2.y && mouse_y < e2.y + e2.h)) {
                    CASE[0] = 'E';
                    CASE[1] = '2';
                }
                else if ((mouse_x > f2.x && mouse_x < f2.x + f2.w) && (mouse_y > f2.y && mouse_y < f2.y + f2.h)) {
                    CASE[0] = 'F';
                    CASE[1] = '2';
                }
                else if ((mouse_x > g2.x && mouse_x < g2.x + g2.w) && (mouse_y > g2.y && mouse_y < g2.y + g2.h)) {
                    CASE[0] = 'G';
                    CASE[1] = '2';
                }
                else if ((mouse_x > h2.x && mouse_x < h2.x + h2.w) && (mouse_y > h2.y && mouse_y < h2.y + h2.h)) {
                    CASE[0] = 'H';
                    CASE[1] = '2';
                }
                //////////////////////////////////////////////////////////////////////////////
                else if ((mouse_x > a3.x && mouse_x < a3.x + a3.w) && (mouse_y > a3.y && mouse_y < a3.y + a3.h)) {
                    CASE[0] = 'A';
                    CASE[1] = '3';
                }
                else if ((mouse_x > b3.x && mouse_x < b3.x + b3.w) && (mouse_y > b3.y && mouse_y < b3.y + b3.h)) {
                    CASE[0] = 'B';
                    CASE[1] = '3';
                }
                else if ((mouse_x > c3.x && mouse_x < c3.x + c3.w) && (mouse_y > c3.y && mouse_y < c3.y + c3.h)) {
                    CASE[0] = 'C';
                    CASE[1] = '3';
                }
                else if ((mouse_x > d3.x && mouse_x < d3.x + d3.w) && (mouse_y > d3.y && mouse_y < d3.y + d3.h)) {
                    CASE[0] = 'D';
                    CASE[1] = '3';
                }
                else if ((mouse_x > e3.x && mouse_x < e3.x + e3.w) && (mouse_y > e3.y && mouse_y < e3.y + e3.h)) {
                    CASE[0] = 'E';
                    CASE[1] = '3';
                }
                else if ((mouse_x > f3.x && mouse_x < f3.x + f3.w) && (mouse_y > f3.y && mouse_y < f3.y + f3.h)) {
                    CASE[0] = 'F';
                    CASE[1] = '3';
                }
                else if ((mouse_x > g3.x && mouse_x < g3.x + g3.w) && (mouse_y > g3.y && mouse_y < g3.y + g3.h)) {
                    CASE[0] = 'G';
                    CASE[1] = '3';
                }
                else if ((mouse_x > h3.x && mouse_x < h3.x + h3.w) && (mouse_y > h3.y && mouse_y < h3.y + h3.h)) {
                    CASE[0] = 'H';
                    CASE[1] = '3';
                }
                //////////////////////////////////////////////////////////////////////////////
                else if ((mouse_x > a4.x && mouse_x < a4.x + a4.w) && (mouse_y > a4.y && mouse_y < a4.y + a4.h)) {
                    CASE[0] = 'A';
                    CASE[1] = '4';
                }
                else if ((mouse_x > b4.x && mouse_x < b4.x + b4.w) && (mouse_y > b4.y && mouse_y < b4.y + b4.h)) {
                    CASE[0] = 'B';
                    CASE[1] = '4';
                }
                else if ((mouse_x > c4.x && mouse_x < c4.x + c4.w) && (mouse_y > c4.y && mouse_y < c4.y + c4.h)) {
                    CASE[0] = 'C';
                    CASE[1] = '4';
                }
                else if ((mouse_x > d4.x && mouse_x < d4.x + d4.w) && (mouse_y > d4.y && mouse_y < d4.y + d4.h)) {
                    CASE[0] = 'D';
                    CASE[1] = '4';
                }
                else if ((mouse_x > e4.x && mouse_x < e4.x + e4.w) && (mouse_y > e4.y && mouse_y < e4.y + e4.h)) {
                    CASE[0] = 'E';
                    CASE[1] = '4';
                }
                else if ((mouse_x > f4.x && mouse_x < f4.x + f4.w) && (mouse_y > f4.y && mouse_y < f4.y + f4.h)) {
                    CASE[0] = 'F';
                    CASE[1] = '4';
                }
                else if ((mouse_x > g4.x && mouse_x < g4.x + g4.w) && (mouse_y > g4.y && mouse_y < g4.y + g4.h)) {
                    CASE[0] = 'G';
                    CASE[1] = '4';
                }
                else if ((mouse_x > h4.x && mouse_x < h4.x + h4.w) && (mouse_y > h4.y && mouse_y < h4.y + h4.h)) {
                    CASE[0] = 'H';
                    CASE[1] = '4';
                }
                //////////////////////////////////////////////////////////////////////////////
                else if ((mouse_x > a5.x && mouse_x < a5.x + a5.w) && (mouse_y > a5.y && mouse_y < a5.y + a5.h)) {
                    CASE[0] = 'A';
                    CASE[1] = '5';
                }
                else if ((mouse_x > b5.x && mouse_x < b5.x + b5.w) && (mouse_y > b5.y && mouse_y < b5.y + b5.h)) {
                    CASE[0] = 'B';
                    CASE[1] = '5';
                }
                else if ((mouse_x > c5.x && mouse_x < c5.x + c5.w) && (mouse_y > c5.y && mouse_y < c5.y + c5.h)) {
                    CASE[0] = 'C';
                    CASE[1] = '5';
                }
                else if ((mouse_x > d5.x && mouse_x < d5.x + d5.w) && (mouse_y > d5.y && mouse_y < d5.y + d5.h)) {
                    CASE[0] = 'D';
                    CASE[1] = '5';
                }
                else if ((mouse_x > e5.x && mouse_x < e5.x + e5.w) && (mouse_y > e5.y && mouse_y < e5.y + e5.h)) {
                    CASE[0] = 'E';
                    CASE[1] = '5';
                }
                else if ((mouse_x > f5.x && mouse_x < f5.x + f5.w) && (mouse_y > f5.y && mouse_y < f5.y + f5.h)) {
                    CASE[0] = 'F';
                    CASE[1] = '5';
                }
                else if ((mouse_x > g5.x && mouse_x < g5.x + g5.w) && (mouse_y > g5.y && mouse_y < g5.y + g5.h)) {
                    CASE[0] = 'G';
                    CASE[1] = '5';
                }
                else if ((mouse_x > h5.x && mouse_x < h5.x + h5.w) && (mouse_y > h5.y && mouse_y < h5.y + h5.h)) {
                    CASE[0] = 'H';
                    CASE[1] = '5';
                }
                //////////////////////////////////////////////////////////////////////////////
                else if ((mouse_x > a6.x && mouse_x < a6.x + a6.w) && (mouse_y > a6.y && mouse_y < a6.y + a6.h)) {
                    CASE[0] = 'A';
                    CASE[1] = '6';
                }
                else if ((mouse_x > b6.x && mouse_x < b6.x + b6.w) && (mouse_y > b6.y && mouse_y < b6.y + b6.h)) {
                    CASE[0] = 'B';
                    CASE[1] = '6';
                }
                else if ((mouse_x > c6.x && mouse_x < c6.x + c6.w) && (mouse_y > c6.y && mouse_y < c6.y + c6.h)) {
                    CASE[0] = 'C';
                    CASE[1] = '6';
                }
                else if ((mouse_x > d6.x && mouse_x < d6.x + d6.w) && (mouse_y > d6.y && mouse_y < d6.y + d6.h)) {
                    CASE[0] = 'D';
                    CASE[1] = '6';
                }
                else if ((mouse_x > e6.x && mouse_x < e6.x + e6.w) && (mouse_y > e6.y && mouse_y < e6.y + e6.h)) {
                    CASE[0] = 'E';
                    CASE[1] = '6';
                }
                else if ((mouse_x > f6.x && mouse_x < f6.x + f6.w) && (mouse_y > f6.y && mouse_y < f6.y + f6.h)) {
                    CASE[0] = 'F';
                    CASE[1] = '6';
                }
                else if ((mouse_x > g6.x && mouse_x < g6.x + g6.w) && (mouse_y > g6.y && mouse_y < g6.y + g6.h)) {
                    CASE[0] = 'G';
                    CASE[1] = '6';
                }
                else if ((mouse_x > h6.x && mouse_x < h6.x + h6.w) && (mouse_y > h6.y && mouse_y < h6.y + h6.h)) {
                    CASE[0] = 'H';
                    CASE[1] = '6';
                }
                //////////////////////////////////////////////////////////////////////////////
                else if ((mouse_x > a7.x && mouse_x < a7.x + a7.w) && (mouse_y > a7.y && mouse_y < a7.y + a7.h)) {
                    CASE[0] = 'A';
                    CASE[1] = '7';
                }
                else if ((mouse_x > b7.x && mouse_x < b7.x + b7.w) && (mouse_y > b7.y && mouse_y < b7.y + b7.h)) {
                    CASE[0] = 'B';
                    CASE[1] = '7';
                }
                else if ((mouse_x > c7.x && mouse_x < c7.x + c7.w) && (mouse_y > c7.y && mouse_y < c7.y + c7.h)) {
                    CASE[0] = 'C';
                    CASE[1] = '7';
                }
                else if ((mouse_x > d7.x && mouse_x < d7.x + d7.w) && (mouse_y > d7.y && mouse_y < d7.y + d7.h)) {
                    CASE[0] = 'D';
                    CASE[1] = '7';
                }
                else if ((mouse_x > e7.x && mouse_x < e7.x + e7.w) && (mouse_y > e7.y && mouse_y < e7.y + e7.h)) {
                    CASE[0] = 'E';
                    CASE[1] = '7';
                }
                else if ((mouse_x > f7.x && mouse_x < f7.x + f7.w) && (mouse_y > f7.y && mouse_y < f7.y + f7.h)) {
                    CASE[0] = 'F';
                    CASE[1] = '7';
                }
                else if ((mouse_x > g7.x && mouse_x < g7.x + g7.w) && (mouse_y > g7.y && mouse_y < g7.y + g7.h)) {
                    CASE[0] = 'G';
                    CASE[1] = '7';
                }
                else if ((mouse_x > h7.x && mouse_x < h7.x + h7.w) && (mouse_y > h7.y && mouse_y < h7.y + h7.h)) {
                    CASE[0] = 'H';
                    CASE[1] = '7';
                }
                //////////////////////////////////////////////////////////////////////////////
                else if ((mouse_x > a8.x && mouse_x < a8.x + a8.w) && (mouse_y > a8.y && mouse_y < a8.y + a8.h)) {
                    CASE[0] = 'A';
                    CASE[1] = '8';
                }
                else if ((mouse_x > b8.x && mouse_x < b8.x + b8.w) && (mouse_y > b8.y && mouse_y < b8.y + b8.h)) {
                    CASE[0] = 'B';
                    CASE[1] = '8';
                }
                else if ((mouse_x > c8.x && mouse_x < c8.x + c8.w) && (mouse_y > c8.y && mouse_y < c8.y + c8.h)) {
                    CASE[0] = 'C';
                    CASE[1] = '8';
                }
                else if ((mouse_x > d8.x && mouse_x < d8.x + d8.w) && (mouse_y > d8.y && mouse_y < d8.y + d8.h)) {
                    CASE[0] = 'D';
                    CASE[1] = '8';
                }
                else if ((mouse_x > e8.x && mouse_x < e8.x + e8.w) && (mouse_y > e8.y && mouse_y < e8.y + e8.h)) {
                    CASE[0] = 'E';
                    CASE[1] = '8';
                }
                else if ((mouse_x > f8.x && mouse_x < f8.x + f8.w) && (mouse_y > f8.y && mouse_y < f8.y + f8.h)) {
                    CASE[0] = 'F';
                    CASE[1] = '8';
                }
                else if ((mouse_x > g8.x && mouse_x < g8.x + g8.w) && (mouse_y > g8.y && mouse_y < g8.y + g8.h)) {
                    CASE[0] = 'G';
                    CASE[1] = '8';
                }
                else if ((mouse_x > h8.x && mouse_x < h8.x + h8.w) && (mouse_y > h8.y && mouse_y < h8.y + h8.h)) {
                    CASE[0] = 'H';
                    CASE[1] = '8';
                }
                //////////////////////////////////////////////////////////////////////////////
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
                            square.x = a2.x + (a2.w / 4);
                            square.y = a2.y + (a2.h / 4);
                            break;
                        case '3':
                            square.x = a3.x + (a3.w / 4);
                            square.y = a3.y + (a3.h / 4);
                            break;
                        case '4':
                            square.x = a4.x + (a4.w / 4);
                            square.y = a4.y + (a4.h / 4);
                            break;
                        case '5':
                            square.x = a5.x + (a5.w / 4);
                            square.y = a5.y + (a5.h / 4);
                            break;
                        case '6':
                            square.x = a6.x + (a6.w / 4);
                            square.y = a6.y + (a6.h / 4);
                            break;
                        case '7':
                            square.x = a7.x + (a7.w / 4);
                            square.y = a7.y + (a7.h / 4);
                            break;
                        case '8':
                            square.x = a8.x + (a8.w / 4);
                            square.y = a8.y + (a8.h / 4);
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
                            square.x = b2.x + (b2.w / 4);
                            square.y = b2.y + (b2.h / 4);
                            break;
                        case '3':
                            square.x = b3.x + (b3.w / 4);
                            square.y = b3.y + (b3.h / 4);
                            break;
                        case '4':
                            square.x = b4.x + (b4.w / 4);
                            square.y = b4.y + (b4.h / 4);
                            break;
                        case '5':
                            square.x = b5.x + (b5.w / 4);
                            square.y = b5.y + (b5.h / 4);
                            break;
                        case '6':
                            square.x = b6.x + (b6.w / 4);
                            square.y = b6.y + (b6.h / 4);
                            break;
                        case '7':
                            square.x = b7.x + (b7.w / 4);
                            square.y = b7.y + (b7.h / 4);
                            break;
                        case '8':
                            square.x = b8.x + (b8.w / 4);
                            square.y = b8.y + (b8.h / 4);
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
                            square.x = c2.x + (c2.w / 4);
                            square.y = c2.y + (c2.h / 4);
                            break;
                        case '3':
                            square.x = c3.x + (c3.w / 4);
                            square.y = c3.y + (c3.h / 4);
                            break;
                        case '4':
                            square.x = c4.x + (c4.w / 4);
                            square.y = c4.y + (c4.h / 4);
                            break;
                        case '5':
                            square.x = c5.x + (c5.w / 4);
                            square.y = c5.y + (c5.h / 4);
                            break;
                        case '6':
                            square.x = c6.x + (c6.w / 4);
                            square.y = c6.y + (c6.h / 4);
                            break;
                        case '7':
                            square.x = c7.x + (c7.w / 4);
                            square.y = c7.y + (c7.h / 4);
                            break;
                        case '8':
                            square.x = c8.x + (c8.w / 4);
                            square.y = c8.y + (c8.h / 4);
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
                            square.x = d2.x + (d2.w / 4);
                            square.y = d2.y + (d2.h / 4);
                            break;
                        case '3':
                            square.x = d3.x + (d3.w / 4);
                            square.y = d3.y + (d3.h / 4);
                            break;
                        case '4':
                            square.x = d4.x + (d4.w / 4);
                            square.y = d4.y + (d4.h / 4);
                            break;
                        case '5':
                            square.x = d5.x + (d5.w / 4);
                            square.y = d5.y + (d5.h / 4);
                            break;
                        case '6':
                            square.x = d6.x + (d6.w / 4);
                            square.y = d6.y + (d6.h / 4);
                            break;
                        case '7':
                            square.x = d7.x + (d7.w / 4);
                            square.y = d7.y + (d7.h / 4);
                            break;
                        case '8':
                            square.x = d8.x + (d8.w / 4);
                            square.y = d8.y + (d8.h / 4);
                            break;
                        }
                        break;
                    case 'E':
                        switch (CASE[1])
                        {
                        case '1':
                            square.x = e1.x + (e1.w / 4);
                            square.y = e1.y + (e1.h / 4);
                            break;
                        case '2':
                            square.x = e2.x + (e2.w / 4);
                            square.y = e2.y + (e2.h / 4);
                            break;
                        case '3':
                            square.x = e3.x + (e3.w / 4);
                            square.y = e3.y + (e3.h / 4);
                            break;
                        case '4':
                            square.x = e4.x + (e4.w / 4);
                            square.y = e4.y + (e4.h / 4);
                            break;
                        case '5':
                            square.x = e5.x + (e5.w / 4);
                            square.y = e5.y + (e5.h / 4);
                            break;
                        case '6':
                            square.x = e6.x + (e6.w / 4);
                            square.y = e6.y + (e6.h / 4);
                            break;
                        case '7':
                            square.x = e7.x + (e7.w / 4);
                            square.y = e7.y + (e7.h / 4);
                            break;
                        case '8':
                            square.x = e8.x + (e8.w / 4);
                            square.y = e8.y + (e8.h / 4);
                            break;
                        }
                        break;
                    case 'F':
                        switch (CASE[1])
                        {
                        case '1':
                            square.x = f1.x + (f1.w / 4);
                            square.y = f1.y + (f1.h / 4);
                            break;
                        case '2':
                            square.x = f2.x + (f2.w / 4);
                            square.y = f2.y + (f2.h / 4);
                            break;
                        case '3':
                            square.x = f3.x + (f3.w / 4);
                            square.y = f3.y + (f3.h / 4);
                            break;
                        case '4':
                            square.x = f4.x + (f4.w / 4);
                            square.y = f4.y + (f4.h / 4);
                            break;
                        case '5':
                            square.x = f5.x + (f5.w / 4);
                            square.y = f5.y + (f5.h / 4);
                            break;
                        case '6':
                            square.x = f6.x + (f6.w / 4);
                            square.y = f6.y + (f6.h / 4);
                            break;
                        case '7':
                            square.x = f7.x + (f7.w / 4);
                            square.y = f7.y + (f7.h / 4);
                            break;
                        case '8':
                            square.x = f8.x + (f8.w / 4);
                            square.y = f8.y + (f8.h / 4);
                            break;
                        }
                        break;
                    case 'G':
                        switch (CASE[1])
                        {
                        case '1':
                            square.x = g1.x + (g1.w / 4);
                            square.y = g1.y + (g1.h / 4);
                            break;
                        case '2':
                            square.x = g2.x + (g2.w / 4);
                            square.y = g2.y + (g2.h / 4);
                            break;
                        case '3':
                            square.x = g3.x + (g3.w / 4);
                            square.y = g3.y + (g3.h / 4);
                            break;
                        case '4':
                            square.x = g4.x + (g4.w / 4);
                            square.y = g4.y + (g4.h / 4);
                            break;
                        case '5':
                            square.x = g5.x + (g5.w / 4);
                            square.y = g5.y + (g5.h / 4);
                            break;
                        case '6':
                            square.x = g6.x + (g6.w / 4);
                            square.y = g6.y + (g6.h / 4);
                            break;
                        case '7':
                            square.x = g7.x + (g7.w / 4);
                            square.y = g7.y + (g7.h / 4);
                            break;
                        case '8':
                            square.x = g8.x + (g8.w / 4);
                            square.y = g8.y + (g8.h / 4);
                            break;
                        }
                        break;
                    case 'H':
                        switch (CASE[1])
                        {
                        case '1':
                            square.x = h1.x + (h1.w / 4);
                            square.y = h1.y + (h1.h / 4);
                            break;
                        case '2':
                            square.x = h2.x + (h2.w / 4);
                            square.y = h2.y + (h2.h / 4);
                            break;
                        case '3':
                            square.x = h3.x + (h3.w / 4);
                            square.y = h3.y + (h3.h / 4);
                            break;
                        case '4':
                            square.x = h4.x + (h4.w / 4);
                            square.y = h4.y + (h4.h / 4);
                            break;
                        case '5':
                            square.x = h5.x + (h5.w / 4);
                            square.y = h5.y + (h5.h / 4);
                            break;
                        case '6':
                            square.x = h6.x + (h6.w / 4);
                            square.y = h6.y + (h6.h / 4);
                            break;
                        case '7':
                            square.x = h7.x + (h7.w / 4);
                            square.y = h7.y + (h7.h / 4);
                            break;
                        case '8':
                            square.x = h8.x + (h8.w / 4);
                            square.y = h8.y + (h8.h / 4);
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
        //MARRON
        SDL_SetRenderDrawColor(pRenderer, 164, 93, 68, 70);
        SDL_RenderFillRect(pRenderer, &a1);
        SDL_RenderFillRect(pRenderer, &c1);
        SDL_RenderFillRect(pRenderer, &e1);
        SDL_RenderFillRect(pRenderer, &g1);

        SDL_RenderFillRect(pRenderer, &b2);
        SDL_RenderFillRect(pRenderer, &d2);
        SDL_RenderFillRect(pRenderer, &f2);
        SDL_RenderFillRect(pRenderer, &h2);

        SDL_RenderFillRect(pRenderer, &a3);
        SDL_RenderFillRect(pRenderer, &c3);
        SDL_RenderFillRect(pRenderer, &e3);
        SDL_RenderFillRect(pRenderer, &g3);

        SDL_RenderFillRect(pRenderer, &b4);
        SDL_RenderFillRect(pRenderer, &d4);
        SDL_RenderFillRect(pRenderer, &f4);
        SDL_RenderFillRect(pRenderer, &h4);

        SDL_RenderFillRect(pRenderer, &a5);
        SDL_RenderFillRect(pRenderer, &c5);
        SDL_RenderFillRect(pRenderer, &e5);
        SDL_RenderFillRect(pRenderer, &g5);

        SDL_RenderFillRect(pRenderer, &b6);
        SDL_RenderFillRect(pRenderer, &d6);
        SDL_RenderFillRect(pRenderer, &f6);
        SDL_RenderFillRect(pRenderer, &h6);

        SDL_RenderFillRect(pRenderer, &a7);
        SDL_RenderFillRect(pRenderer, &c7);
        SDL_RenderFillRect(pRenderer, &e7);
        SDL_RenderFillRect(pRenderer, &g7);

        SDL_RenderFillRect(pRenderer, &b8);
        SDL_RenderFillRect(pRenderer, &d8);
        SDL_RenderFillRect(pRenderer, &f8);
        SDL_RenderFillRect(pRenderer, &h8);
        //BLANC ROSE
        SDL_SetRenderDrawColor(pRenderer, 255, 181, 175, 100);
        SDL_RenderFillRect(pRenderer, &b1);
        SDL_RenderFillRect(pRenderer, &d1);
        SDL_RenderFillRect(pRenderer, &f1);
        SDL_RenderFillRect(pRenderer, &h1);

        SDL_RenderFillRect(pRenderer, &a2);
        SDL_RenderFillRect(pRenderer, &c2);
        SDL_RenderFillRect(pRenderer, &e2);
        SDL_RenderFillRect(pRenderer, &g2);

        SDL_RenderFillRect(pRenderer, &b3);
        SDL_RenderFillRect(pRenderer, &d3);
        SDL_RenderFillRect(pRenderer, &f3);
        SDL_RenderFillRect(pRenderer, &h3);

        SDL_RenderFillRect(pRenderer, &a4);
        SDL_RenderFillRect(pRenderer, &c4);
        SDL_RenderFillRect(pRenderer, &e4);
        SDL_RenderFillRect(pRenderer, &g4);

        SDL_RenderFillRect(pRenderer, &b5);
        SDL_RenderFillRect(pRenderer, &d5);
        SDL_RenderFillRect(pRenderer, &f5);
        SDL_RenderFillRect(pRenderer, &h5);

        SDL_RenderFillRect(pRenderer, &a6);
        SDL_RenderFillRect(pRenderer, &c6);
        SDL_RenderFillRect(pRenderer, &e6);
        SDL_RenderFillRect(pRenderer, &g6);

        SDL_RenderFillRect(pRenderer, &b7);
        SDL_RenderFillRect(pRenderer, &d7);
        SDL_RenderFillRect(pRenderer, &f7);
        SDL_RenderFillRect(pRenderer, &h7);

        SDL_RenderFillRect(pRenderer, &a8);
        SDL_RenderFillRect(pRenderer, &c8);
        SDL_RenderFillRect(pRenderer, &e8);
        SDL_RenderFillRect(pRenderer, &g8);


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
