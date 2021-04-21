/**
 * \file chess.c
 * \brief Programme du jeu SDL.
 * \author Angel/Bastien (conseils/aides : Ayoub)
 * \version 1.00
 * \date 19.04.21
 *
 * Programme en SDL du jeu d'échecs
 *
 */

// gcc Angel-Bastien/chess.c -o bin/prog -I include -L ./lib -l mingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf




// Inclure la biblioth�que SDL
#include <SDL.h>
#include <SDL_image.h>


// Inclusion des biblioth�que standard C
#include <stdio.h>
#include <stdlib.h>


#define RECAD 10

int mouse_x;
int mouse_y;
int mouse_left;
int Action1 = 0;
int GrabMode = 0;
int PieceDrop = 0;
//int Action2 = 0;
//int Action3 = 0;
//int Action4 = 0;


int prise_x;
int prise_y;
int prise_w;
int prise_h;

int IsInSquare = 0;

//INIT DE TOUTES LES CASES
char CASE[2];

char CASE_ARRIVEE[2];

char CASE_DEPART[2];


/* SDL_Window* pWindow=NULL;
SDL_Renderer* pRenderer= NULL;

void afficher_message(int message,int afficher)
{
  SDL_Color color= { 15, 5, 107 };
  SDL_Color color1= { 249, 234, 195 };
  SDL_Rect position= { 300,300, 300,300};
  int ok=0,taille_police=100, hauteur_max_texte=45, largeur_max_texte=350;
  char *texte;

  SDL_Texture *texture;
  SDL_Surface *texte_sdl;
    SDL_Surface *texteS;
  SDL_Rect position_texte;
  TTF_Font *police;
  SDL_Color couleur;

  couleur.r=255;//couleur : blanc
  couleur.g=255;
  couleur.b=255;

  position_texte.x=940;
  position_texte.y=550;

  TTF_Init();
  switch(message) {
    case 0: texte=malloc(sizeof(char)*strlen("Cliquez pour demarrer la partie"));
    strcpy(texte,"Cliquez pour demarrer la partie"); break;
    case 1:  texte=malloc(sizeof(char)*strlen("Roi noir en échec")); strcpy(texte,"Roi noir en échec"); break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    default: break;
  }
  /*
  else if(message==2)  {
  strcpy(texte,"Roi blanc en échec");
}
  else if(message==3)  strcpy(texte,"Pat");
  else if(message==4)  strcpy(texte,"Roi noir en échec et mat !");
  else if(message==5)  strcpy(texte,"Roi blanc en échec et mat !");
  else if(message==6)  strcpy(texte,"Le joueur blanc gagne");
  else if(message==7)  strcpy(texte,"Le joueur noir gagne");
  else if(message==8)  strcpy(texte,"En quoi le pion doit il etre promu?");


  if(message==0) position_texte.x-=10;
  else if(message==1 || message==2) position_texte.x-=5;
  else if(message==3)  position_texte.x+=60;
  else if(message==6 || message==7)
  {
    position_texte.x-=7;
    position_texte.y+=50;
  }
  else if(message==8)
  {
    largeur_max_texte=360;
    hauteur_max_texte=46;

    position_texte.x-=5;
    position_texte.y-=380;
  }


  if(afficher)
  {
    while(!ok && taille_police>2)
    {
      police = TTF_OpenFont("arial.ttf",taille_police);
      texte_sdl = TTF_RenderText_Blended(police,texte,color1);

      taille_police--;
      if(texte_sdl->w<largeur_max_texte && texte_sdl->h<hauteur_max_texte) ok=1;
    }

    position.x = WIDTHSCREEN  - position.w ;
    position.y = HEIGHTSCREEN  - position.h ;
    position.w=text_sdl->w;
    position.h=text_sdl->h;

      SDL_BlitSurface(texte_sdl,NULL,texteS,&position);
      texture=SDL_CreateTextureFromSurface(pRenderer,texteS);
      SDL_RenderCopy(pRenderer, texture, NULL, &position_texte);

      SDL_FreeSurface(texte_sdl);

      SDL_RenderPresent(pRenderer);
      SDL_SaveBMP(texte_sdl, "somefile.bmp");
      free(texte);
      SDL_DestroyTexture(texture);
  }


}
*/


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

    SDL_Texture* tab[12];





    if (SDL_CreateWindowAndRenderer(1280, 960, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }


    pSurface = IMG_Load("./echequier.jpg");
    pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);



    SDL_SetWindowTitle(pWindow, "Jeu d'echecs - projet");


    //blanc
    SDL_Surface* pion_b = IMG_Load("pieces/pion_blanc.png");
    SDL_Surface* tour_b = IMG_Load("pieces/tour_blanc.png");
    SDL_Surface* cavalier_b = IMG_Load("pieces/cavalier_blanc.png");
    SDL_Surface* fou_b = IMG_Load("pieces/fou_blanc.png");
    SDL_Surface* roi_b = IMG_Load("pieces/roi_blanc.png");
    SDL_Surface* reine_b = IMG_Load("pieces/reine_blanc.png");

    //noir
    SDL_Surface* pion_n = IMG_Load("pieces/pion_noir.png");
    SDL_Surface* tour_n = IMG_Load("pieces/tour_noir.png");
    SDL_Surface* cavalier_n = IMG_Load("pieces/cavalier_noir.png");
    SDL_Surface* fou_n = IMG_Load("pieces/fou_noir.png");
    SDL_Surface* roi_n = IMG_Load("pieces/roi_noir.png");
    SDL_Surface* reine_n = IMG_Load("pieces/reine_noir.png");
    SDL_Surface* echequier = IMG_Load("echec_local.png");

    tab[0] = SDL_CreateTextureFromSurface(pRenderer, pion_b);
    tab[1] = SDL_CreateTextureFromSurface(pRenderer, tour_b);
    tab[2] = SDL_CreateTextureFromSurface(pRenderer, cavalier_b);
    tab[3] = SDL_CreateTextureFromSurface(pRenderer, fou_b);
    tab[4] = SDL_CreateTextureFromSurface(pRenderer, roi_b);
    tab[5] = SDL_CreateTextureFromSurface(pRenderer, reine_b);
    tab[6] = SDL_CreateTextureFromSurface(pRenderer, pion_n);
    tab[7] = SDL_CreateTextureFromSurface(pRenderer, tour_n);
    tab[8] = SDL_CreateTextureFromSurface(pRenderer, cavalier_n);
    tab[9] = SDL_CreateTextureFromSurface(pRenderer, fou_n);
    tab[10] = SDL_CreateTextureFromSurface(pRenderer, roi_n);
    tab[11] = SDL_CreateTextureFromSurface(pRenderer, reine_n);

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



    // TOUTES LES CASES
    //////////////////////////////////////////////////////
    //A1
    SDL_Rect a1;
    a1.x = 50;
    a1.y = 750;
    a1.w = 100;
    a1.h = 100;

    //B1
    SDL_Rect b1;
    b1.x = 150;
    b1.y = 750;
    b1.w = 100;
    b1.h = 100;

    //C1
    SDL_Rect c1;
    c1.x = 250;
    c1.y = 750;
    c1.w = 100;
    c1.h = 100;

    //D1
    SDL_Rect d1;
    d1.x = 350;
    d1.y = 750;
    d1.w = 100;
    d1.h = 100;

    //E1
    SDL_Rect e1;
    e1.x = 450;
    e1.y = 750;
    e1.w = 100;
    e1.h = 100;

    //F1
    SDL_Rect f1;
    f1.x = 550;
    f1.y = 750;
    f1.w = 100;
    f1.h = 100;

    //G1
    SDL_Rect g1;
    g1.x = 650;
    g1.y = 750;
    g1.w = 100;
    g1.h = 100;

    //H1
    SDL_Rect h1;
    h1.x = 750;
    h1.y = 750;
    h1.w = 100;
    h1.h = 100;
    //////////////////////////////////////////////////////////////////////
    //A2
    SDL_Rect a2;
    a2.x = 50;
    a2.y = 650;
    a2.w = 100;
    a2.h = 100;

    //B2
    SDL_Rect b2;
    b2.x = 150;
    b2.y = 650;
    b2.w = 100;
    b2.h = 100;

    //C2
    SDL_Rect c2;
    c2.x = 250;
    c2.y = 650;
    c2.w = 100;
    c2.h = 100;

    //D2
    SDL_Rect d2;
    d2.x = 350;
    d2.y = 650;
    d2.w = 100;
    d2.h = 100;

    //E2
    SDL_Rect e2;
    e2.x = 450;
    e2.y = 650;
    e2.w = 100;
    e2.h = 100;

    //F2
    SDL_Rect f2;
    f2.x = 550;
    f2.y = 650;
    f2.w = 100;
    f2.h = 100;

    //G2
    SDL_Rect g2;
    g2.x = 650;
    g2.y = 650;
    g2.w = 100;
    g2.h = 100;

    //h2
    SDL_Rect h2;
    h2.x = 750;
    h2.y = 650;
    h2.w = 100;
    h2.h = 100;
    //////////////////////////////////////////////////////////////////////
    //A3
    SDL_Rect a3;
    a3.x = 50;
    a3.y = 550;
    a3.w = 100;
    a3.h = 100;

    //B2
    SDL_Rect b3;
    b3.x = 150;
    b3.y = 550;
    b3.w = 100;
    b3.h = 100;

    //C2
    SDL_Rect c3;
    c3.x = 250;
    c3.y = 550;
    c3.w = 100;
    c3.h = 100;

    //D2
    SDL_Rect d3;
    d3.x = 350;
    d3.y = 550;
    d3.w = 100;
    d3.h = 100;

    //E2
    SDL_Rect e3;
    e3.x = 450;
    e3.y = 550;
    e3.w = 100;
    e3.h = 100;

    //F2
    SDL_Rect f3;
    f3.x = 550;
    f3.y = 550;
    f3.w = 100;
    f3.h = 100;

    //G2
    SDL_Rect g3;
    g3.x = 650;
    g3.y = 550;
    g3.w = 100;
    g3.h = 100;

    //h2
    SDL_Rect h3;
    h3.x = 750;
    h3.y = 550;
    h3.w = 100;
    h3.h = 100;
    //////////////////////////////////////////////////////////////////////
    //A4
    SDL_Rect a4;
    a4.x = 50;
    a4.y = 450;
    a4.w = 100;
    a4.h = 100;

    //B4
    SDL_Rect b4;
    b4.x = 150;
    b4.y = 450;
    b4.w = 100;
    b4.h = 100;

    //C4
    SDL_Rect c4;
    c4.x = 250;
    c4.y = 450;
    c4.w = 100;
    c4.h = 100;

    //D4
    SDL_Rect d4;
    d4.x = 350;
    d4.y = 450;
    d4.w = 100;
    d4.h = 100;

    //E4
    SDL_Rect e4;
    e4.x = 450;
    e4.y = 450;
    e4.w = 100;
    e4.h = 100;

    //F4
    SDL_Rect f4;
    f4.x = 550;
    f4.y = 450;
    f4.w = 100;
    f4.h = 100;

    //G4
    SDL_Rect g4;
    g4.x = 650;
    g4.y = 450;
    g4.w = 100;
    g4.h = 100;

    //h4
    SDL_Rect h4;
    h4.x = 750;
    h4.y = 450;
    h4.w = 100;
    h4.h = 100;
    //////////////////////////////////////////////////////////////////////
    //A5
    SDL_Rect a5;
    a5.x = 50;
    a5.y = 350;
    a5.w = 100;
    a5.h = 100;

    //B5
    SDL_Rect b5;
    b5.x = 150;
    b5.y = 350;
    b5.w = 100;
    b5.h = 100;

    //C5
    SDL_Rect c5;
    c5.x = 250;
    c5.y = 350;
    c5.w = 100;
    c5.h = 100;

    //D5
    SDL_Rect d5;
    d5.x = 350;
    d5.y = 350;
    d5.w = 100;
    d5.h = 100;

    //E5
    SDL_Rect e5;
    e5.x = 450;
    e5.y = 350;
    e5.w = 100;
    e5.h = 100;

    //F5
    SDL_Rect f5;
    f5.x = 550;
    f5.y = 350;
    f5.w = 100;
    f5.h = 100;

    //G5
    SDL_Rect g5;
    g5.x = 650;
    g5.y = 350;
    g5.w = 100;
    g5.h = 100;

    //h5
    SDL_Rect h5;
    h5.x = 750;
    h5.y = 350;
    h5.w = 100;
    h5.h = 100;
    //////////////////////////////////////////////////////////////////////
    //A6
    SDL_Rect a6;
    a6.x = 50;
    a6.y = 250;
    a6.w = 100;
    a6.h = 100;

    //B6
    SDL_Rect b6;
    b6.x = 150;
    b6.y = 250;
    b6.w = 100;
    b6.h = 100;

    //C6
    SDL_Rect c6;
    c6.x = 250;
    c6.y = 250;
    c6.w = 100;
    c6.h = 100;

    //D6
    SDL_Rect d6;
    d6.x = 350;
    d6.y = 250;
    d6.w = 100;
    d6.h = 100;

    //E6
    SDL_Rect e6;
    e6.x = 450;
    e6.y = 250;
    e6.w = 100;
    e6.h = 100;

    //F6
    SDL_Rect f6;
    f6.x = 550;
    f6.y = 250;
    f6.w = 100;
    f6.h = 100;

    //G6
    SDL_Rect g6;
    g6.x = 650;
    g6.y = 250;
    g6.w = 100;
    g6.h = 100;

    //h6
    SDL_Rect h6;
    h6.x = 750;
    h6.y = 250;
    h6.w = 100;
    h6.h = 100;
    //////////////////////////////////////////////////////////////////////
    //A7
    SDL_Rect a7;
    a7.x = 50;
    a7.y = 150;
    a7.w = 100;
    a7.h = 100;

    //B7
    SDL_Rect b7;
    b7.x = 150;
    b7.y = 150;
    b7.w = 100;
    b7.h = 100;

    //C7
    SDL_Rect c7;
    c7.x = 250;
    c7.y = 150;
    c7.w = 100;
    c7.h = 100;

    //D7
    SDL_Rect d7;
    d7.x = 350;
    d7.y = 150;
    d7.w = 100;
    d7.h = 100;

    //E7
    SDL_Rect e7;
    e7.x = 450;
    e7.y = 150;
    e7.w = 100;
    e7.h = 100;

    //F7
    SDL_Rect f7;
    f7.x = 550;
    f7.y = 150;
    f7.w = 100;
    f7.h = 100;

    //G7
    SDL_Rect g7;
    g7.x = 650;
    g7.y = 150;
    g7.w = 100;
    g7.h = 100;

    //h7
    SDL_Rect h7;
    h7.x = 750;
    h7.y = 150;
    h7.w = 100;
    h7.h = 100;
    //////////////////////////////////////////////////////////////////////
    //A8
    SDL_Rect a8;
    a8.x = 50;
    a8.y = 50;
    a8.w = 100;
    a8.h = 100;

    //B8
    SDL_Rect b8;
    b8.x = 150;
    b8.y = 50;
    b8.w = 100;
    b8.h = 100;

    //C8
    SDL_Rect c8;
    c8.x = 250;
    c8.y = 50;
    c8.w = 100;
    c8.h = 100;

    //D8
    SDL_Rect d8;
    d8.x = 350;
    d8.y = 50;
    d8.w = 100;
    d8.h = 100;

    //E8
    SDL_Rect e8;
    e8.x = 450;
    e8.y = 50;
    e8.w = 100;
    e8.h = 100;

    //F8
    SDL_Rect f8;
    f8.x = 550;
    f8.y = 50;
    f8.w = 100;
    f8.h = 100;

    //G7
    SDL_Rect g8;
    g8.x = 650;
    g8.y = 50;
    g8.w = 100;
    g8.h = 100;

    //h8
    SDL_Rect h8;
    h8.x = 750;
    h8.y = 50;
    h8.w = 100;
    h8.h = 100;

    //PIECES
    SDL_Rect square;
    square.x = a2.x + (a2.w / RECAD);
    square.y = a2.y + (a2.h / RECAD);
    square.w = 80;
    square.h = 80;

    SDL_Rect p_noir;
    p_noir.x = a7.x + (a7.w / RECAD);
    p_noir.y = a7.y + (a7.h / RECAD);
    p_noir.w = 80;
    p_noir.h = 80;

   /* SDL_Rect p_noir2;
    p_noir.x = a7.x + (a7.w / RECAD);
    p_noir.y = a7.y + (a7.h / RECAD);
    p_noir.w = 80;
    p_noir.h = 80;

    SDL_Rect p_noir3;
    p_noir.x = a7.x + (a7.w / RECAD);
    p_noir.y = a7.y + (a7.h / RECAD);
    p_noir.w = 80;
    p_noir.h = 80;

    SDL_Rect p_noir2;
    p_noir.x = a7.x + (a7.w / RECAD);
    p_noir.y = a7.y + (a7.h / RECAD);
    p_noir.w = 80;
    p_noir.h = 80;

    SDL_Rect p_noir;
    p_noir.x = a7.x + (a7.w / RECAD);
    p_noir.y = a7.y + (a7.h / RECAD);
    p_noir.w = 80;
    p_noir.h = 80;*/


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


                SDL_Log("Mouse x = %i , Mouse y = %i , IIS1 = %i , CASE = %c%c,CASE de depart = %c%c, CASE arrivee = %c%c, GRAB = %i , PIECE_DROP = %i", mouse_x, mouse_y, IsInSquare, CASE[0],CASE[1], CASE_DEPART[0],CASE_DEPART[1], CASE_ARRIVEE[0],CASE_ARRIVEE[1], GrabMode, PieceDrop);



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

               CASE_DEPART[0] = 'R' ;
               CASE_DEPART[1] = 'R' ;


               if (GrabMode == 1) {
                   CASE_DEPART[0] = CASE[0];
                   CASE_DEPART[1] = CASE[1];
               }

               //VALEURE SAVOIR CASE DE DEPART





               break;

            case SDL_MOUSEBUTTONUP:
            CASE_ARRIVEE[0] = 'Z' ;
            CASE_ARRIVEE[1] = 'Z' ;

                if (GrabMode == 1) {
                    switch (CASE[0])
                    {
                    case 'A':
                        switch (CASE[1])
                        {
                        case '1':
                            CASE_ARRIVEE[0] = CASE[0];
                            CASE_ARRIVEE[1] = CASE[1];
                            square.x = a1.x + (a1.w / RECAD);
                            square.y = a1.y + (a1.h / RECAD);
                            break;
                        case '2':
                            CASE_ARRIVEE[0] = CASE[0];
                            CASE_ARRIVEE[1] = CASE[1];
                            square.x = a2.x + (a2.w / RECAD);
                            square.y = a2.y + (a2.h / RECAD);
                            break;
                        case '3':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = a3.x + (a3.w / RECAD);
                            square.y = a3.y + (a3.h / RECAD);
                            break;
                        case '4':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = a4.x + (a4.w / RECAD);
                            square.y = a4.y + (a4.h / RECAD);
                            break;
                        case '5':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = a5.x + (a5.w / RECAD);
                            square.y = a5.y + (a5.h / RECAD);
                            break;
                        case '6':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = a6.x + (a6.w / RECAD);
                            square.y = a6.y + (a6.h / RECAD);
                            break;
                        case '7':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = a7.x + (a7.w / RECAD);
                            square.y = a7.y + (a7.h / RECAD);
                            break;
                        case '8':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = a8.x + (a8.w / RECAD);
                            square.y = a8.y + (a8.h / RECAD);
                            break;
                        }
                        break;
                    case 'B':
                        switch (CASE[1])
                        {
                        case '1':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = b1.x + (b1.w / RECAD);
                            square.y = b1.y + (b1.h / RECAD);
                            break;
                        case '2':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = b2.x + (b2.w / RECAD);
                            square.y = b2.y + (b2.h / RECAD);
                            break;
                        case '3':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = b3.x + (b3.w / RECAD);
                            square.y = b3.y + (b3.h / RECAD);
                            break;
                        case '4':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = b4.x + (b4.w / RECAD);
                            square.y = b4.y + (b4.h / RECAD);
                            break;
                        case '5':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = b5.x + (b5.w / RECAD);
                            square.y = b5.y + (b5.h / RECAD);
                            break;
                        case '6':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = b6.x + (b6.w / RECAD);
                            square.y = b6.y + (b6.h / RECAD);
                            break;
                        case '7':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = b7.x + (b7.w / RECAD);
                            square.y = b7.y + (b7.h / RECAD);
                            break;
                        case '8':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = b8.x + (b8.w / RECAD);
                            square.y = b8.y + (b8.h / RECAD);
                            break;
                        }
                        break;
                    case 'C':
                        switch (CASE[1])
                        {
                        case '1':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = c1.x + (c1.w / RECAD);
                            square.y = c1.y + (c1.h / RECAD);
                            break;
                        case '2':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = c2.x + (c2.w / RECAD);
                            square.y = c2.y + (c2.h / RECAD);
                            break;
                        case '3':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = c3.x + (c3.w / RECAD);
                            square.y = c3.y + (c3.h / RECAD);
                            break;
                        case '4':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = c4.x + (c4.w / RECAD);
                            square.y = c4.y + (c4.h / RECAD);
                            break;
                        case '5':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = c5.x + (c5.w / RECAD);
                            square.y = c5.y + (c5.h / RECAD);
                            break;
                        case '6':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = c6.x + (c6.w / RECAD);
                            square.y = c6.y + (c6.h / RECAD);
                            break;
                        case '7':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = c7.x + (c7.w / RECAD);
                            square.y = c7.y + (c7.h / RECAD);
                            break;
                        case '8':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = c8.x + (c8.w / RECAD);
                            square.y = c8.y + (c8.h / RECAD);
                            break;
                        }
                        break;
                    case 'D':
                        switch (CASE[1])
                        {
                        case '1':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = d1.x + (d1.w / RECAD);
                            square.y = d1.y + (d1.h / RECAD);
                            break;
                        case '2':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = d2.x + (d2.w / RECAD);
                            square.y = d2.y + (d2.h / RECAD);
                            break;
                        case '3':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = d3.x + (d3.w / RECAD);
                            square.y = d3.y + (d3.h / RECAD);
                            break;
                        case '4':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = d4.x + (d4.w / RECAD);
                            square.y = d4.y + (d4.h / RECAD);
                            break;
                        case '5':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = d5.x + (d5.w / RECAD);
                            square.y = d5.y + (d5.h / RECAD);
                            break;
                        case '6':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = d6.x + (d6.w / RECAD);
                            square.y = d6.y + (d6.h / RECAD);
                            break;
                        case '7':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = d7.x + (d7.w / RECAD);
                            square.y = d7.y + (d7.h / RECAD);
                            break;
                        case '8':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = d8.x + (d8.w / RECAD);
                            square.y = d8.y + (d8.h / RECAD);
                            break;
                        }
                        break;
                    case 'E':
                        switch (CASE[1])
                        {
                        case '1':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = e1.x + (e1.w / RECAD);
                            square.y = e1.y + (e1.h / RECAD);
                            break;
                        case '2':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = e2.x + (e2.w / RECAD);
                            square.y = e2.y + (e2.h / RECAD);
                            break;
                        case '3':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = e3.x + (e3.w / RECAD);
                            square.y = e3.y + (e3.h / RECAD);
                            break;
                        case '4':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = e4.x + (e4.w / RECAD);
                            square.y = e4.y + (e4.h / RECAD);
                            break;
                        case '5':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = e5.x + (e5.w / RECAD);
                            square.y = e5.y + (e5.h / RECAD);
                            break;
                        case '6':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = e6.x + (e6.w / RECAD);
                            square.y = e6.y + (e6.h / RECAD);
                            break;
                        case '7':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = e7.x + (e7.w / RECAD);
                            square.y = e7.y + (e7.h / RECAD);
                            break;
                        case '8':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = e8.x + (e8.w / RECAD);
                            square.y = e8.y + (e8.h / RECAD);
                            break;
                        }
                        break;
                    case 'F':
                        switch (CASE[1])
                        {
                        case '1':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = f1.x + (f1.w / RECAD);
                            square.y = f1.y + (f1.h / RECAD);
                            break;
                        case '2':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = f2.x + (f2.w / RECAD);
                            square.y = f2.y + (f2.h / RECAD);
                            break;
                        case '3':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = f3.x + (f3.w / RECAD);
                            square.y = f3.y + (f3.h / RECAD);
                            break;
                        case '4':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = f4.x + (f4.w / RECAD);
                            square.y = f4.y + (f4.h / RECAD);
                            break;
                        case '5':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = f5.x + (f5.w / RECAD);
                            square.y = f5.y + (f5.h / RECAD);
                            break;
                        case '6':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = f6.x + (f6.w / RECAD);
                            square.y = f6.y + (f6.h / RECAD);
                            break;
                        case '7':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = f7.x + (f7.w / RECAD);
                            square.y = f7.y + (f7.h / RECAD);
                            break;
                        case '8':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = f8.x + (f8.w / RECAD);
                            square.y = f8.y + (f8.h / RECAD);
                            break;
                        }
                        break;
                    case 'G':
                        switch (CASE[1])
                        {
                        case '1':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = g1.x + (g1.w / RECAD);
                            square.y = g1.y + (g1.h / RECAD);
                            break;
                        case '2':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = g2.x + (g2.w / RECAD);
                            square.y = g2.y + (g2.h / RECAD);
                            break;
                        case '3':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = g3.x + (g3.w / RECAD);
                            square.y = g3.y + (g3.h / RECAD);
                            break;
                        case '4':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = g4.x + (g4.w / RECAD);
                            square.y = g4.y + (g4.h / RECAD);
                            break;
                        case '5':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = g5.x + (g5.w / RECAD);
                            square.y = g5.y + (g5.h / RECAD);
                            break;
                        case '6':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = g6.x + (g6.w / RECAD);
                            square.y = g6.y + (g6.h / RECAD);
                            break;
                        case '7':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = g7.x + (g7.w / RECAD);
                            square.y = g7.y + (g7.h / RECAD);
                            break;
                        case '8':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = g8.x + (g8.w / RECAD);
                            square.y = g8.y + (g8.h / RECAD);
                            break;
                        }
                        break;
                    case 'H':
                        switch (CASE[1])
                        {
                        case '1':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = h1.x + (h1.w / RECAD);
                            square.y = h1.y + (h1.h / RECAD);
                            break;
                        case '2':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = h2.x + (h2.w / RECAD);
                            square.y = h2.y + (h2.h / RECAD);
                            break;
                        case '3':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = h3.x + (h3.w / RECAD);
                            square.y = h3.y + (h3.h / RECAD);
                            break;
                        case '4':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = h4.x + (h4.w / RECAD);
                            square.y = h4.y + (h4.h / RECAD);
                            break;
                        case '5':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = h5.x + (h5.w / RECAD);
                            square.y = h5.y + (h5.h / RECAD);
                            break;
                        case '6':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = h6.x + (h6.w / RECAD);
                            square.y = h6.y + (h6.h / RECAD);
                            break;
                        case '7':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = h7.x + (h7.w / RECAD);
                            square.y = h7.y + (h7.h / RECAD);
                            break;
                        case '8':
                        CASE_ARRIVEE[0] = CASE[0];
                        CASE_ARRIVEE[1] = CASE[1];
                            square.x = h8.x + (h8.w / RECAD);
                            square.y = h8.y + (h8.h / RECAD);
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
        //BLANC
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 0);
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
        //SDL_RenderFillRect(pRenderer, &square);

        //blanc
        SDL_RenderCopy(pRenderer, tab[0], NULL, &square);
        SDL_RenderCopy(pRenderer, tab[1], NULL, &a1);
        SDL_RenderCopy(pRenderer, tab[2], NULL, &b1);
        SDL_RenderCopy(pRenderer, tab[3], NULL, &c1);
        SDL_RenderCopy(pRenderer, tab[5], NULL, &d1);
        SDL_RenderCopy(pRenderer, tab[4], NULL, &e1);
        SDL_RenderCopy(pRenderer, tab[3], NULL, &f1);
        SDL_RenderCopy(pRenderer, tab[2], NULL, &g1);
        SDL_RenderCopy(pRenderer, tab[1], NULL, &h1);
        SDL_RenderCopy(pRenderer, tab[0], NULL, &b2);
        SDL_RenderCopy(pRenderer, tab[0], NULL, &c2);
        SDL_RenderCopy(pRenderer, tab[0], NULL, &d2);
        SDL_RenderCopy(pRenderer, tab[0], NULL, &e2);
        SDL_RenderCopy(pRenderer, tab[0], NULL, &f2);
        SDL_RenderCopy(pRenderer, tab[0], NULL, &g2);
        SDL_RenderCopy(pRenderer, tab[0], NULL, &h2);



        //noir
        SDL_RenderCopy(pRenderer, tab[6], NULL, &p_noir);
        SDL_RenderCopy(pRenderer, tab[7], NULL, &a8);
        SDL_RenderCopy(pRenderer, tab[8], NULL, &b8);
        SDL_RenderCopy(pRenderer, tab[9], NULL, &c8);
        SDL_RenderCopy(pRenderer, tab[11], NULL, &d8);
        SDL_RenderCopy(pRenderer, tab[10], NULL, &e8);
        SDL_RenderCopy(pRenderer, tab[9], NULL, &f8);
        SDL_RenderCopy(pRenderer, tab[8], NULL, &g8);
        SDL_RenderCopy(pRenderer, tab[7], NULL, &h8);
        SDL_RenderCopy(pRenderer, tab[6], NULL, &b7);
        SDL_RenderCopy(pRenderer, tab[6], NULL, &c7);
        SDL_RenderCopy(pRenderer, tab[6], NULL, &d7);
        SDL_RenderCopy(pRenderer, tab[6], NULL, &e7);
        SDL_RenderCopy(pRenderer, tab[6], NULL, &f7);
        SDL_RenderCopy(pRenderer, tab[6], NULL, &g7);
        SDL_RenderCopy(pRenderer, tab[6], NULL, &h7);

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
