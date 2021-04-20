#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define gris       0x808080
#define noir       0x000000
#define blanc      0xFFFFFF
#define jaune_vert 0x9ACD32
#define bleu       0x0000FF
#define vert       0x00FF00
#define rouge      0xFF0000
#define violet     0x800080

#define WIDTHSCREEN 1280

#define HEIGHTSCREEN 960

SDL_Surface *picture = NULL;

void afficher_message(int message,int afficher);









int main(int argc, char* argv[])
{

  TTF_Font* font = TTF_OpenFont("arial.ttf", 32); // Crée une police avec la police "ariali.ttf" et de taille 18 pixels
  TTF_Font* font1 = TTF_OpenFont("arial.ttf", 70); // Crée une police avec la police "ariali.ttf" et de taille 18 pixels

  int save = 0;

  SDL_Color color= { 15, 5, 107 };
  SDL_Color color1= { 249, 234, 195 };









  int mouse_x;
  int mouse_y;
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
    void afficher_message(int message,int afficher)
    {
    	int ok=0,taille_police=100, hauteur_max_texte=45, largeur_max_texte=350;
    	char *texte;

      SDL_Texture *texture;
    	SDL_Surface *texte_sdl;
    	SDL_Rect position_texte;
    	TTF_Font *police;
    	SDL_Color couleur;

    	couleur.r=255;//couleur : blanc
    	couleur.g=255;
    	couleur.b=255;

    	position_texte.x=940;
    	position_texte.y=550;

    	TTF_Init();

    	if(message==0)      {
        texte=malloc(sizeof(char)*strlen("Cliquez pour demarrer la partie"));
        strcpy(texte,"Cliquez pour demarrer la partie");
                    }
    	else if(message==1) {
      strcpy(texte,"Roi noir en échec"); }
    	else if(message==2)  {
      strcpy(texte,"Roi blanc en échec");
    }
    	else if(message==3)  strcpy(texte,"Pat");
    	else if(message==4)  strcpy(texte,"Roi noir en échec et mat !");
    	else if(message==5)  strcpy(texte,"Roi blanc en échec et mat !");
    	else if(message==6)  strcpy(texte,"Le joueur blanc gagne");
    	else if(message==7)  strcpy(texte,"Le joueur noir gagne");
    	else if(message==8)  strcpy(texte,"En quoi le pion dois il etre promu?");


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

          texture=SDL_CreateTextureFromSurface(pRenderer,texte_sdl);
          SDL_RenderCopy(pRenderer, texture, NULL, &position_texte);
          SDL_FreeSurface(texte_sdl);

          SDL_RenderPresent(pRenderer);
          free(texte);
          SDL_DestroyTexture(texture);
    	}


    }



    SDL_Event events;

    float isOpen=1;

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

        afficher_message(1,1);

        SDL_Delay(20);
    }


    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}








/*
SDL_Rect echec= { 0,0, 0,0};
SDL_Rect position= { 230,200, 230,200};
SDL_Rect position1= { 330,200, 330,200};
SDL_Rect position2= { 270,200, 270,200};
SDL_Rect position3= { 100,200, 100,200};
SDL_Rect position4= { 200,200, 200,200};
*/

/*
SDL_Texture* tab[6];

SDL_Surface* pion_b = IMG_Load("pieces/pion_blanc.png");
SDL_Surface* tour_b = IMG_Load("pieces/tour_blanc.png");
SDL_Surface* cavalier_b = IMG_Load("pieces/cavalier_blanc_og.png");
SDL_Surface* fou_b = IMG_Load("pieces/fou_blanc_og.png");
SDL_Surface* roi_b = IMG_Load("pieces/roi_blanc_og.png");
SDL_Surface* reine_b = IMG_Load("pieces/reine_blanc_og.png");
SDL_Surface* echequier = IMG_Load("echec_local.png"); */








/*
    tab[0]=SDL_CreateTextureFromSurface(pRenderer,pion_b);
    tab[1]=SDL_CreateTextureFromSurface(pRenderer,tour_b);
    tab[2]=SDL_CreateTextureFromSurface(pRenderer,cavalier_b);
    tab[3]=SDL_CreateTextureFromSurface(pRenderer,fou_b);
    tab[4]=SDL_CreateTextureFromSurface(pRenderer,roi_b);
    tab[5]=SDL_CreateTextureFromSurface(pRenderer,reine_b);
    tab[6]=SDL_CreateTextureFromSurface(pRenderer,echequier);


    SDL_FreeSurface(pion_b);
    SDL_FreeSurface(tour_b);
    SDL_FreeSurface(cavalier_b);
    SDL_FreeSurface(fou_b);
    SDL_FreeSurface(roi_b);
    SDL_FreeSurface(reine_b);
    SDL_FreeSurface(echequier);*/



/*
position.x = WIDTHSCREEN / 2 - position.w / 2;
position.y = (HEIGHTSCREEN - 200) - (position.h / 2);

SDL_RenderCopy(pRenderer, tab[6], NULL, NULL); // valeurs pour test
SDL_RenderCopy(pRenderer, tab[0], NULL, &position);
SDL_RenderCopy(pRenderer, tab[1], NULL, &position);
SDL_RenderCopy(pRenderer, tab[2], NULL, &position);
SDL_RenderCopy(pRenderer, tab[3], NULL, &position);
SDL_RenderCopy(pRenderer, tab[4], NULL, &position);
SDL_RenderCopy(pRenderer, tab[5], NULL, &position); // valeurs pour test*/




// SDL_Surface* text = NULL;
// SDL_Surface* buffer = NULL; // Crée un surface qui contient le texte
//  SDL_Surface* final = SDL_CreateRGBSurface(0, WIDTHSCREEN, HEIGHTSCREEN, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);



/*SDL_Surface* echequier = IMG_Load("echec.jpg");
SDL_BlitSurface(echequier,NULL,final,&echec);
SDL_FreeSurface(echequier); */
  /* position.x = WIDTHSCREEN / 2 - position.w / 2;
  position.y = (HEIGHTSCREEN - 200) - (position.h / 2);
  position.w=pion_b ->w;
  position.h=pion_b ->h;
  SDL_BlitSurface(tab[0],NULL,final,NULL);
  SDL_FreeSurface(pion_b);
  SDL_Surface* pion_n = IMG_Load("pieces/pion_noir.png");
  position1.x = WIDTHSCREEN / 2 - position1.w / 2;
  position1.y = (HEIGHTSCREEN - 150 ) - (position1.h / 2)  ;
  position1.w=pion_n->w;
  position1.h=pion_n->h;
  SDL_BlitSurface(pion_n,NULL,final,&position1);
  SDL_FreeSurface(pion_n);
  SDL_Surface* tour_n = IMG_Load("pieces/tour_noir.png");
  position2.x = WIDTHSCREEN / 2 - position2.w / 2;
  position2.y = (HEIGHTSCREEN - 100) - (position2.h  / 2);
  position2.w=tour_n->w;
  position2.h=tour_n->h;
  SDL_BlitSurface(tour_n,NULL,final,&position2);
  SDL_FreeSurface(tour_n);
  SDL_Surface* tour_b = IMG_Load("pieces/tour_blanc.png");
  position3.x = WIDTHSCREEN / 2 - position3.w / 2;
  position3.y = (HEIGHTSCREEN - 50) - (position3.h / 2);
  position3.w=tour_b->w;
  position3.h=tour_b->h;
  SDL_BlitSurface(tour_b,NULL,final,&position3);
  SDL_FreeSurface(tour_b);
  text=TTF_RenderText_Blended(font1, "Chess",color);
  position4.x = WIDTHSCREEN / 2  - position4.w / 2;
  position4.y = HEIGHTSCREEN / 15 - position4.h / 15;
  position4.w=text->w;
  position4.h=text->h;
  SDL_BlitSurface(text,NULL,final,&position4);
  SDL_FreeSurface(text); */
