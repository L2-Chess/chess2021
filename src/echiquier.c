/**
 * \file echiquier.c
 * \brief Jeu échecs Algo.
 * \author Ayoub (conseils/aides : Bastien/Angel)
 * \version 1.00
 * \date 21.04.21
 *
 * Jeu échecs Algo.
 *
 */







#include <stdio.h>
#include <stdlib.h>
#include "../lib/pieces.h"
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

#define TAILLE 120
#define LIMITE 64

//detection du tour de jeu
bool white_pl = false;
bool black_pl = false;

//Variables pour gérer la prise en passant
char bl_last_move  [10];
char nr_last_move  [10];
char tmp_last_move [10];
int first_pos;
int new_pos;

//variable de sauvegarde
char nom_save [20];
char date_save [20];
char savefile [100];
char load [50];

//à qui le tour : 0 = Blanc, 1 = Noir
int role = 0;

//Variable permettant de controler le roque
bool bl_roque = false;
bool nr_roque = false;
bool roque = false;
char tour_to_roque [20];
int  pos_tour_to_roque;

//Plateau du jeu
Piece echiquier [LIMITE];

//Copie du plateau pour autoriser ou non un deplacement d'une piece ( voir si son deplacement expose le roi à une piece adverse )
Piece test_echiquier [LIMITE];

//Plateau pour l'affichage du deuxieme joueur
Piece mirror [LIMITE];

//positions demandées à l'utilisateur
char case_dep [10], case_arr [10], choix[10];
int indice_dep = 0;
int indice_arr = 0;

//tableau des pieces en jeu
Piece pieces_en_jeu [LIMITE];

//Pieces blanches
Piece b_roi = {ROI,BLANC,0,false};
Piece b_dame = {DAME,BLANC,9,false};
Piece b_tour = {TOUR,BLANC,5,false};
Piece b_fou = {FOU,BLANC,3,false};
Piece b_cavalier = {CAVALIER,BLANC,3,false};
Piece b_pion = {PION,BLANC,1,false};

//Pieces noires
Piece n_roi = {ROI,NOIR,0,false};
Piece n_dame = {DAME,NOIR,9,false};
Piece n_tour = {TOUR,NOIR,5,false};
Piece n_fou = {FOU,NOIR,3,false};
Piece n_cavalier = {CAVALIER,NOIR,3,false};
Piece n_pion = {PION,NOIR,1,false};

//case vide
Piece case_vide = {VIDE,NONE,0,false};

//tableau des deplacement possibles pour tester l'echec et mat
int deplacement_echec [LIMITE];

// Tableau dans lequel on stock les coups possibles pour une pièces selectionée
int possible_moves [TAILLE];

//Tableau pour stocker les cases menacées
int attacked[TAILLE];

// Tableau de 120 élément pour vérifier si les coups donnés sortent de l'echiquier ou pas
int mailbox [] = {
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1,  0,  1,  2,  3,  4,  5,  6,  7, -1,
  -1,  8,  9, 10, 11, 12, 13, 14, 15, -1,
  -1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
  -1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
  -1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
  -1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
  -1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
  -1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};


  // tableau de LIMITE element pour récupérer l'indice d'une case demandée et vérifier si elle sort de l'echiquier sur le tableau précédent
  // les valeurs contenues dans ce tableau correspondent aux indices des cases 0 à LIMITE sur le tableau de 120 element
  int tab64 []= {
    21, 22, 23, 24, 25, 26, 27, 28,
    31, 32, 33, 34, 35, 36, 37, 38,
    41, 42, 43, 44, 45, 46, 47, 48,
    51, 52, 53, 54, 55, 56, 57, 58,
    61, 62, 63, 64, 65, 66, 67, 68,
    71, 72, 73, 74, 75, 76, 77, 78,
    81, 82, 83, 84, 85, 86, 87, 88,
    91, 92, 93, 94, 95, 96, 97, 98
  };

  //nom des cases du plateau
  char coord [][4] =
  {"a8","b8","c8","d8","e8","f8","g8","h8",
  "a7","b7","c7","d7","e7","f7","g7","h7",
  "a6","b6","c6","d6","e6","f6","g6","h6",
  "a5","b5","c5","d5","e5","f5","g5","h5",
  "a4","b4","c4","d4","e4","f4","g4","h4",
  "a3","b3","c3","d3","e3","f3","g3","h3",
  "a2","b2","c2","d2","e2","f2","g2","h2",
  "a1","b1","c1","d1","e1","f1","g1","h1"};

//Tablaux des positions des pieces
int pos_fous [2];
int pos_tours [2];
int pos_cavaliers [2];
int pos_pions [8];

//Initialisation du plateau
void init_plateau(Piece plateau []){

  //pour des raisons pratiques on met toutes les cases à des cases vides
  for (int i=0; i<LIMITE; i++){
    plateau [i] = case_vide;
  }
  //position des pions
  for(int i=8; i<16;i++){
    plateau  [i] = n_pion;
  }
  for(int i=48; i<56;i++){
    plateau [i] = b_pion;
  }
  //position des tours
  plateau[0] = n_tour;
  plateau [7] = n_tour;
  plateau [56] = b_tour;
  plateau [63] = b_tour;

  //position des cavaliers
  plateau [1] = n_cavalier;
  plateau [6] = n_cavalier;
  plateau [57] = b_cavalier;
  plateau [62] = b_cavalier;

  //position des foux
  plateau [2] = n_fou;
  plateau [5] = n_fou;
  plateau [58] = b_fou;
  plateau [61] = b_fou;

  //position des dames
  plateau [3] = n_dame;
  plateau [59] = b_dame;

  //position des rois
  plateau [4] = n_roi;
  plateau [60] = b_roi;

}

void banner(char filename [50]){
  FILE *fptr;
  char c;
  fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        wprintf(L"Cannot open file \n");
        exit(0);
    }
  c = fgetc(fptr);
    while (c != EOF)
    {
        wprintf (L"%c", c);
        c = fgetc(fptr);
    }

    fclose(fptr);
  wprintf(L"\n");
}

//Dessiner une piece
void draw(int i){
  if (echiquier[i].n==5 ){
    if(echiquier[i].c==1) wprintf(L" %lc |",pion_n);
    else wprintf(L" %lc |",pion_bl);
  }
  if (echiquier[i].n==4 ){
    if(echiquier[i].c==1) wprintf(L" %lc |",cavalier_n);
    else wprintf(L" %lc |",cavalier_bl);
  }
  if (echiquier[i].n==3 ){
    if(echiquier[i].c==1) wprintf(L" %lc |",fou_n);
    else wprintf(L" %lc |",fou_bl);
  }
  if (echiquier[i].n==2 ){
    if(echiquier[i].c==1) wprintf(L" %lc |",tour_n);
    else wprintf(L" %lc |",tour_bl);
  }
  if (echiquier[i].n==1 ){
    if(echiquier[i].c==1) wprintf(L" %lc |",dame_n);
    else wprintf(L" %lc |",dame_bl);
  }
  if (echiquier[i].n==0 ){
    if(echiquier[i].c==1) wprintf(L" %lc |",roi_n);
    else wprintf(L" %lc |",roi_bl);
  }
  if (echiquier[i].n==6 ) wprintf(L"   |");

}

//Dessiner les bords du plateau
void draw_borders(int line){
  wprintf(L"\n    |___|___|___|___|___|___|___|___|\n");
  wprintf(L"    |   |   |   |   |   |   |   |   |\n %d  |",line);
}

//dessiner le plateau avec les pieces et les bords
void affiche_plateau (){
  int line =8;
  setlocale(LC_CTYPE,"");
  wprintf(L"     ___ ___ ___ ___ ___ ___ ___ ___\n");
  wprintf(L"    |   |   |   |   |   |   |   |   |\n %d  |",line);

  for (int i=0; i<8; i++){
    draw(i);
  }
  line--;
  draw_borders(line);

  for (int i=8; i<16; i++){
    draw(i);
  }
  line--;
  draw_borders(line);

  for (int i=16; i<24; i++){
    draw(i);
  }
  line--;
  draw_borders(line);

  for (int i=24; i<32; i++){
    draw(i);
  }
  line--;
  draw_borders(line);

  for (int i=32; i<40; i++){
    draw(i);
  }
  line--;
  draw_borders(line);

  for (int i=40; i<48; i++){
    draw(i);
  }
  line--;
  draw_borders(line);

  for (int i=48; i<56; i++){
    draw(i);
  }
  line--;
  draw_borders(line);

  for (int i=56; i<LIMITE; i++){
    draw(i);
  }
  wprintf(L"\n    |___|___|___|___|___|___|___|___|\n");
  wprintf(L"\n      a   b   c   d   e   f   g   h  \n");

}

//affichage mirroir
void affiche_plateau_mirroir (){
  int line =1;
  setlocale(LC_CTYPE,"");
  wprintf(L"     ___ ___ ___ ___ ___ ___ ___ ___\n");
  wprintf(L"    |   |   |   |   |   |   |   |   |\n %d  |",line);

  for (int i=63; i>55; i--){
    draw(i);
  }
  line++;
  draw_borders(line);

  for (int i=55; i>47; i--){
    draw(i);
  }
  line++;
  draw_borders(line);

  for (int i=47; i>39; i--){
    draw(i);
  }
  line++;
  draw_borders(line);

  for (int i=39; i>31; i--){
    draw(i);
  }
  line++;
  draw_borders(line);

  for (int i=31; i>23; i--){
    draw(i);
  }
  line++;
  draw_borders(line);

  for (int i=23; i>15; i--){
    draw(i);
  }
  line++;
  draw_borders(line);

  for (int i=15; i>7; i--){
    draw(i);
  }
  line++;
  draw_borders(line);

  for (int i=7; i>=0; i--){
    draw(i);
  }
  wprintf(L"\n    |___|___|___|___|___|___|___|___|\n");
  wprintf(L"\n      h   g   f   e   d   c   b   a  \n");

}

//initialiser le tableau des moves possibles
void init_array(int array[],int taille){
  for(int i=0; i<taille ; i++){
    array[i]= -2;
  }
}

//Fonction pour insérer une position dans le tableau des deplacement possibles
void insert_element(int tab [], int elem){
  //on insère un élément à la premiere case libre
  int x =0;
  while(tab[x]!=-2){
    x++;
  }
  tab[x]=elem;
}

//Copier le contenu d'un tableau vers un autre en éliminant les doublons
void cpy_plateau(Piece plat1[], Piece plat2[]){
  for(int i=0; i<LIMITE; i++){
    plat2[i]=plat1[i];
  }
}

//vérifier si un élément est dans un Tableau
bool is_in_array(int array [], int elem){
  for (int i=0; i<TAILLE; i++){
    if(array[i]==-2) return false;
    if(array[i]== elem) return true;
  }
}

//génère les coups possible pour un pion donné
void get_moves_pion(int ind_case, int couleur, int tab []){

  // en fonction de la couleur du pion (blanc ou noir) on lui génère les coups possibles
  // on sépare les couleurs pour distinguer les cases d'une piece du meme camps et du camps adverse
  switch (couleur) {
    case 0 :
        //en cas du premier move d'un pion Blanc
        // on reconnait le premier move si l'indice de la case appartient aux indices de la 2eme ligne
        // On specifie la couleur également car si il y'a un puon noir sur cette ligne il ne pourra avancer que de 1 vu que ce sera pas son premier move et pas la meme direction de jeu
        if (ind_case<56 && ind_case > 47 ){
          if(echiquier[ind_case-16].n==6) insert_element(tab,ind_case-16);
        }
        //on teste si la case de devant est libre et on 'lajoute si c'est vrai
        if(echiquier[ind_case-8].n==6) insert_element(tab,ind_case-8);
        //on teste si les cases diagonales sont prises par une piece adverse pour les attaquer et on l'ajoute
        if(echiquier[ind_case-7].c==1 && mailbox[tab64[ind_case-7]-1]!=-1) insert_element(tab,ind_case-7);
        if(echiquier[ind_case-9].c==1 && mailbox[tab64[ind_case-9]+1]!=-1) insert_element(tab,ind_case-9);
        //tester la prise en passant
        if (ind_case<32 && ind_case > 23 ){
          if(echiquier[ind_case-1].n==5 && echiquier[ind_case-9].n==6 && echiquier[ind_case-1].c==1 && strcmp(nr_last_move,coord[ind_case-1])==0){
            if(new_pos-16==first_pos) insert_element(tab,ind_case-9);
          }
          if(echiquier[ind_case+1].n==5 && echiquier[ind_case-7].n==6 && echiquier[ind_case+1].c==1 && strcmp(nr_last_move,coord[ind_case+1])==0){
            if(new_pos-16==first_pos) insert_element(tab,ind_case-7);
          }
        }

        break;

    case 1 :
      // on répète la meme chose mais cette fois ci pour les pièces noires
      if (ind_case<16 && ind_case > 7 ){
        if(echiquier[ind_case+16].n==6) insert_element(tab,ind_case+16);
      }
      if(echiquier[ind_case+8].n==6) insert_element(tab,ind_case+8);
      if(echiquier[ind_case+7].c==0 && mailbox[tab64[ind_case+7]+1]!=-1) insert_element(tab,ind_case+7);
      if(echiquier[ind_case+9].c==0 && mailbox[tab64[ind_case+9]-1]!=-1) insert_element(tab,ind_case+9);
      //tester la prise en passant
      if (ind_case<40 && ind_case > 31 ){
        if(echiquier[ind_case+1].n==5 && echiquier[ind_case+9].n==6 && echiquier[ind_case+1].c==0 && strcmp(bl_last_move,coord[ind_case+1])==0){
          if(new_pos+16==first_pos) insert_element(tab,ind_case+9);
        }
        if(echiquier[ind_case-1].n==5 && echiquier[ind_case+7].n==6 && echiquier[ind_case-1].c==0 && strcmp(bl_last_move,coord[ind_case-1])==0){
          if(new_pos+16==first_pos) insert_element(tab,ind_case+7);
        }
      }
      break;
  }
}

//génerer les coups pour un cavalier donné
void get_moves_cavalier(int ind_case, int couleur, int tab []){

  switch (couleur){

    case 0 :
    if(ind_case-6 <LIMITE && ind_case-6 >=0) {
      if(mailbox[tab64[ind_case-6]]!=-1 && mailbox[tab64[ind_case-6]-2]!=-1){
        if(echiquier[ind_case-6].n==6 || echiquier[ind_case-6].c==1) insert_element(tab,ind_case-6);
      }
    }
    if(ind_case+6 <LIMITE && ind_case+6 >=0) {
      if(mailbox[tab64[ind_case+6]]!=-1 && mailbox[tab64[ind_case+6]+2]!=-1){
        if(echiquier[ind_case+6].n==6 || echiquier[ind_case+6].c==1) insert_element(tab,ind_case+6);
      }
    }
    if(ind_case-10 <LIMITE && ind_case-10 >=0) {
      if(mailbox[tab64[ind_case-10]]!=-1){
        if(echiquier[ind_case-10].n==6 || echiquier[ind_case-10].c==1) insert_element(tab,ind_case-10);
      }
    }
    if(ind_case+10 <LIMITE && ind_case+10 >=0) {
      if(mailbox[tab64[ind_case+10]]!=-1){
        if(echiquier[ind_case+10].n==6 || echiquier[ind_case+10].c==1) insert_element(tab,ind_case+10);
      }
    }
    if(ind_case-15 <LIMITE && ind_case-15 >=0) {
      if(mailbox[tab64[ind_case-15]]!=-1){
        if(echiquier[ind_case-15].n==6 || echiquier[ind_case-15].c==1) insert_element(tab,ind_case-15);
      }
    }
    if(ind_case+15 <LIMITE  && ind_case+15 >=0){
      if(mailbox[tab64[ind_case+15]]!=-1){
        if(echiquier[ind_case+15].n==6 || echiquier[ind_case+15].c==1) insert_element(tab,ind_case+15);
      }
    }
    if(ind_case-17 <LIMITE  && ind_case-17 >=0){
      if(mailbox[tab64[ind_case-17]]!=-1){
        if(echiquier[ind_case-17].n==6 || echiquier[ind_case-17].c==1) insert_element(tab,ind_case-17);
      }
    }
    if(ind_case+17 <LIMITE  && ind_case+17 >=0){
      if(mailbox[tab64[ind_case+17]]!=-1){
        if(echiquier[ind_case+17].n==6 || echiquier[ind_case+17].c==1) insert_element(tab,ind_case+17);
      }
    }
      break;

    case 1:
      if(ind_case-6 >=0) {
        if(mailbox[tab64[ind_case-6]]!=-1 && mailbox[tab64[ind_case-6]-2]!=-1){
          if(echiquier[ind_case-6].n==6 || echiquier[ind_case-6].c==0) insert_element(tab,ind_case-6);
        }
      }
      if(ind_case+6 <LIMITE) {
        if(mailbox[tab64[ind_case+6]]!=-1 && mailbox[tab64[ind_case+6]+2]!=-1){
          if(echiquier[ind_case+6].n==6 || echiquier[ind_case+6].c==0) insert_element(tab,ind_case+6);
        }
      }
      if(ind_case-10 >=0) {
        if(mailbox[tab64[ind_case-10]]!=-1){
          if(echiquier[ind_case-10].n==6 || echiquier[ind_case-10].c==0) insert_element(tab,ind_case-10);
        }
      }
      if(ind_case+10 <LIMITE) {
        if(mailbox[tab64[ind_case+10]]!=-1){
          if(echiquier[ind_case+10].n==6 || echiquier[ind_case+10].c==0) insert_element(tab,ind_case+10);
        }
      }
      if(ind_case-15 >=0) {
        if(mailbox[tab64[ind_case-15]]!=-1){
          if(echiquier[ind_case-15].n==6 || echiquier[ind_case-15].c==0) insert_element(tab,ind_case-15);
        }
      }
      if(ind_case+15 <LIMITE){
        if(mailbox[tab64[ind_case+15]]!=-1){
          if(echiquier[ind_case+15].n==6 || echiquier[ind_case+15].c==0) insert_element(tab,ind_case+15);
        }
      }
      if(ind_case-17 >=0){
        if(mailbox[tab64[ind_case-17]]!=-1){
          if(echiquier[ind_case-17].n==6 || echiquier[ind_case-17].c==0) insert_element(tab,ind_case-17);
        }
      }
      if(ind_case+17 <LIMITE){
        if(mailbox[tab64[ind_case+17]]!=-1){
          if(echiquier[ind_case+17].n==6 || echiquier[ind_case+17].c==0) insert_element(tab,ind_case+17);
        }
      }
      break;
  }
}

//générer les coups possibles pour un fou
void get_moves_fou(int ind_case, int couleur, int tab []){
  int cpt =7 ;

  switch (couleur) {
    //Chaque case possède 4 diagonales, la diagonale haute droite se situe à -7 cases, haute gauche se situe à -9 cases, basse droite à +9 cases et basse gauche à +7 cases
    // Il faut donc tester chacune de ces 4 cases, et continuer sur la ligne diagonale jusqu'à ce qu'on touve un obstacle : une piece adverse, une piece alliée, ou les bords de l'echiquier
    case 0 :
      while(ind_case-cpt >=0){
        if(mailbox[tab64[ind_case-cpt]]!=-1 && mailbox[tab64[ind_case-cpt]-1]!=-1){
          if (echiquier[ind_case-cpt].c==0) break;
          if(echiquier[ind_case-cpt].c==1 ) {
            insert_element(tab,ind_case-cpt);
            break;
          }
          if(echiquier[ind_case-cpt].n==6 ){
             insert_element(tab,ind_case-cpt);
             cpt+=7;
          }
        }
        else break;
      }
      cpt = 7;
      while(ind_case+cpt <LIMITE){
        if(mailbox[tab64[ind_case+cpt]]!=-1 && mailbox[tab64[ind_case+cpt]+1]!=-1){
          if (echiquier[ind_case+cpt].c==0) break;
          if(echiquier[ind_case+cpt].c==1 ) {
            insert_element(tab,ind_case+cpt);
            break;
          }
          if(echiquier[ind_case+cpt].n==6 ){
             insert_element(tab,ind_case+cpt);
             cpt+=7;
          }
        }
        else break;
      }
      cpt = 9;
      while(ind_case+cpt <LIMITE){
        if(mailbox[tab64[ind_case+cpt]]!=-1 && mailbox[tab64[ind_case+cpt]-1]!=-1){
          if (echiquier[ind_case+cpt].c==0) break;
          if(echiquier[ind_case+cpt].c==1 ) {
            insert_element(tab,ind_case+cpt);
            break;
          }
          if(echiquier[ind_case+cpt].n==6 ){
             insert_element(tab,ind_case+cpt);
             cpt+=9;
          }
        }
        else break;
      }
      cpt=9;
      while(ind_case-cpt >=0){
        if(mailbox[tab64[ind_case-cpt]]!=-1 && mailbox[tab64[ind_case-cpt]+1]!=-1){
          if (echiquier[ind_case-cpt].c==0) break;
          if(echiquier[ind_case-cpt].c==1 ) {
            insert_element(tab,ind_case-cpt);
            break;
          }
          if(echiquier[ind_case-cpt].n==6 ){
             insert_element(tab,ind_case-cpt);
             cpt+=9;
          }
        }
        else break;
      }
      break;

    case 1 :
      while(ind_case-cpt >=0){
        if(mailbox[tab64[ind_case-cpt]]!=-1 && mailbox[tab64[ind_case-cpt]-1]!=-1){
          if (echiquier[ind_case-cpt].c==1) break;
          if(echiquier[ind_case-cpt].c==0 ) {
            insert_element(tab,ind_case-cpt);
            break;
          }
          if(echiquier[ind_case-cpt].n==6 ){
             insert_element(tab,ind_case-cpt);
             cpt+=7;
          }
        }
        else break;
      }
      cpt = 7;
      while(ind_case+cpt <LIMITE){
        if(mailbox[tab64[ind_case+cpt]]!=-1 && mailbox[tab64[ind_case+cpt]+1]!=-1){
          if (echiquier[ind_case+cpt].c==1) break;
          if(echiquier[ind_case+cpt].c==0 ) {
            insert_element(tab,ind_case+cpt);
            break;
          }
          if(echiquier[ind_case+cpt].n==6 ){
             insert_element(tab,ind_case+cpt);
             cpt+=7;
          }
        }
        else break;
      }
      cpt = 9;
      while(ind_case+cpt <LIMITE){
        if(mailbox[tab64[ind_case+cpt]]!=-1 && mailbox[tab64[ind_case+cpt]-1]!=-1){
          if (echiquier[ind_case+cpt].c==1) break;
          if(echiquier[ind_case+cpt].c==0 ) {
            insert_element(tab,ind_case+cpt);
            break;
          }
          if(echiquier[ind_case+cpt].n==6 ){
             insert_element(tab,ind_case+cpt);
             cpt+=9;
          }
        }
        else break;
      }
      cpt=9;
      while(ind_case-cpt >=0){
        if(mailbox[tab64[ind_case-cpt]]!=-1 && mailbox[tab64[ind_case-cpt]+1]!=-1){
          if (echiquier[ind_case-cpt].c==1) break;
          if(echiquier[ind_case-cpt].c==0 ) {
            insert_element(tab,ind_case-cpt);
            break;
          }
          if(echiquier[ind_case-cpt].n==6 ){
             insert_element(tab,ind_case-cpt);
             cpt+=9;
          }
        }
        else break;
      }
      break;
  }

}

//génère les coups possibles pour une tour
void get_moves_tour(int ind_case, int couleur, int tab []){
  //compteur pour les cases
  int cpt=1;

  switch(couleur) {

    case 0 :
      // déplacement horizontal à droite
      while(ind_case+cpt < LIMITE ){
        if(mailbox[tab64[ind_case+cpt]] !=-1 && mailbox[tab64[ind_case+cpt]-1] !=-1 ){
          if (echiquier[ind_case+cpt].c==0) break;
          if(echiquier[ind_case+cpt].c==1 ) {
            insert_element(tab,ind_case+cpt);
            break;
          }
          if(echiquier[ind_case+cpt].n==6 ){
             insert_element(tab,ind_case+cpt);
             cpt++;
          }
        }
        else break;
      }
      //déplacement horizontal à gauche
      cpt = 1;
      while(ind_case-cpt >= 0 ){
        if(mailbox[tab64[ind_case-cpt]] !=-1 && mailbox[tab64[ind_case-cpt]+1] !=-1 ){
          if (echiquier[ind_case-cpt].c==0) break;
          if(echiquier[ind_case-cpt].c==1 ) {
            insert_element(tab,ind_case-cpt);
            break;
          }
          if(echiquier[ind_case-cpt].n==6 ){
             insert_element(tab,ind_case-cpt);
             cpt++;
          }
        }
        else break;
      }
      //déplacement vertical vers le haut
      cpt =8;
      while(ind_case-cpt >= 0 ){
        if(mailbox[tab64[ind_case-cpt]] !=-1){
          if (echiquier[ind_case-cpt].c==0) break;
          if(echiquier[ind_case-cpt].c==1 ) {
            insert_element(tab,ind_case-cpt);
            break;
          }
          if(echiquier[ind_case-cpt].n==6 ){
             insert_element(tab,ind_case-cpt);
             cpt+=8;
          }
        }
        else break;
      }
      //déplacement vertical vers le bas
      cpt =8;
      while(ind_case+cpt < LIMITE ){
        if(mailbox[tab64[ind_case+cpt]] !=-1){
          if (echiquier[ind_case+cpt].c==0) break;
          if(echiquier[ind_case+cpt].c==1 ) {
            insert_element(tab,ind_case+cpt);
            break;
          }
          if(echiquier[ind_case+cpt].n==6 ){
             insert_element(tab,ind_case+cpt);
             cpt+=8;
          }
        }
        else break;
      }
      break;

    case 1 :
      // déplacement horizontal à droite
      while(ind_case+cpt < LIMITE ){
        if(mailbox[tab64[ind_case+cpt]] !=-1 && mailbox[tab64[ind_case+cpt]-1] !=-1 ){
          if (echiquier[ind_case+cpt].c==1) break;
          if(echiquier[ind_case+cpt].c==0 ) {
            insert_element(tab,ind_case+cpt);
            break;
          }
          if(echiquier[ind_case+cpt].n==6 ){
             insert_element(tab,ind_case+cpt);
             cpt++;
          }
        }
        else break;
      }
      //déplacement horizontal à gauche
      cpt = 1;
      while(ind_case-cpt >= 0 ){
        if(mailbox[tab64[ind_case-cpt]] !=-1 && mailbox[tab64[ind_case-cpt]+1] !=-1 ){
          if (echiquier[ind_case-cpt].c==1) break;
          if(echiquier[ind_case-cpt].c==0 ) {
            insert_element(tab,ind_case-cpt);
            break;
          }
          if(echiquier[ind_case-cpt].n==6 ){
             insert_element(tab,ind_case-cpt);
             cpt++;
          }
        }
        else break;
      }
      //déplacement vertical vers le haut
      cpt =8;
      while(ind_case-cpt >= 0 ){
        if(mailbox[tab64[ind_case-cpt]] !=-1){
          if (echiquier[ind_case-cpt].c==1) break;
          if(echiquier[ind_case-cpt].c==0 ) {
            insert_element(tab,ind_case-cpt);
            break;
          }
          if(echiquier[ind_case-cpt].n==6 ){
             insert_element(tab,ind_case-cpt);
             cpt+=8;
          }
        }
        else break;
      }
      //déplacement vertical vers le bas
      cpt =8;
      while(ind_case+cpt < LIMITE ){
        if(mailbox[tab64[ind_case+cpt]] !=-1){
          if (echiquier[ind_case+cpt].c==1) break;
          if(echiquier[ind_case+cpt].c==0 ) {
            insert_element(tab,ind_case+cpt);
            break;
          }
          if(echiquier[ind_case+cpt].n==6 ){
             insert_element(tab,ind_case+cpt);
             cpt+=8;
          }
        }
        else break;
      }
      break;
  }
}

//générer les coups possibles pour une dame donnée
void get_moves_dame(int ind_case, int couleur, int tab []){
  get_moves_fou(ind_case, couleur, tab);
  get_moves_tour(ind_case, couleur, tab);
}

//générer les coups possibles pour un roi
void get_moves_roi(int ind_case, int couleur, int tab []){
  switch(couleur){
    case 0 :
    //une case à droite
    if(ind_case+1 <LIMITE && mailbox[tab64[ind_case+1]] !=-1 && mailbox[tab64[ind_case+1]-1] !=-1 ){
      if(echiquier[ind_case+1].c==1 || echiquier[ind_case+1].n==6) insert_element(tab,ind_case+1);
    }
    //une case à gauche
    if(ind_case-1 >=0 && mailbox[tab64[ind_case-1]] !=-1 && mailbox[tab64[ind_case-1]+1] !=-1 ){
      if(echiquier[ind_case-1].c==1 || echiquier[ind_case-1].n==6) insert_element(tab,ind_case-1);
    }
    //une case devant
    if(ind_case-8 >=0 && mailbox[tab64[ind_case-8]] !=-1 ){
      if(echiquier[ind_case-8].c==1 || echiquier[ind_case-8].n==6) insert_element(tab,ind_case-8);
    }
    //une case en arrière
    if(ind_case+8 <LIMITE && mailbox[tab64[ind_case+8]] !=-1 ){
      if(echiquier[ind_case+8].c==1 || echiquier[ind_case+8].n==6) insert_element(tab,ind_case+8);
    }

    //une case en diago haut droite
    if(ind_case-7 >=0 && mailbox[tab64[ind_case-7]] !=-1  && mailbox[tab64[ind_case-7]-1] !=-1){
      if(echiquier[ind_case-7].c==1 || echiquier[ind_case-7].n==6) insert_element(tab,ind_case-7);
    }
    //une case en diago haut gauche
    if(ind_case-9 >=0 && mailbox[tab64[ind_case-9]] !=-1  && mailbox[tab64[ind_case-9]+1] !=-1){
      if(echiquier[ind_case-9].c==1 || echiquier[ind_case-9].n==6) insert_element(tab,ind_case-9);
    }
    //une case en diago bas gauche
    if(ind_case+7 <LIMITE && mailbox[tab64[ind_case+7]] !=-1  && mailbox[tab64[ind_case+7]+1] !=-1){
      if(echiquier[ind_case+7].c==1 || echiquier[ind_case+7].n==6) insert_element(tab,ind_case+7);
    }
    //une case en diago bas droite
    if(ind_case+9 <LIMITE && mailbox[tab64[ind_case+9]] !=-1  && mailbox[tab64[ind_case+9]-1] !=-1){
      if(echiquier[ind_case+9].c==1 || echiquier[ind_case+9].n==6) insert_element(tab,ind_case+9);
    }
    break;

    case 1 :
      //une case à droite
      if(ind_case+1 <LIMITE && mailbox[tab64[ind_case+1]] !=-1 && mailbox[tab64[ind_case+1]-1] !=-1 ){
        if(echiquier[ind_case+1].c==0 || echiquier[ind_case+1].n==6) insert_element(tab,ind_case+1);
      }
      //une case à gauche
      if(ind_case-1 >=0 && mailbox[tab64[ind_case-1]] !=-1 && mailbox[tab64[ind_case-1]+1] !=-1 ){
        if(echiquier[ind_case-1].c==0 || echiquier[ind_case-1].n==6) insert_element(tab,ind_case-1);
      }
      //une case devant
      if(ind_case-8 >=0 && mailbox[tab64[ind_case-8]] !=-1 ){
        if(echiquier[ind_case-8].c==0 || echiquier[ind_case-8].n==6) insert_element(tab,ind_case-8);
      }
      //une case en arrière
      if(ind_case+8 <LIMITE && mailbox[tab64[ind_case+8]] !=-1 ){
        if(echiquier[ind_case+8].c==0 || echiquier[ind_case+8].n==6) insert_element(tab,ind_case+8);
      }

      //une case en diago haut droite
      if(ind_case-7 >=0 && mailbox[tab64[ind_case-7]] !=-1  && mailbox[tab64[ind_case-7]-1] !=-1){
        if(echiquier[ind_case-7].c==0 || echiquier[ind_case-7].n==6) insert_element(tab,ind_case-7);
      }
      //une case en diago haut gauche
      if(ind_case-9 >=0 && mailbox[tab64[ind_case-9]] !=-1  && mailbox[tab64[ind_case-9]+1] !=-1){
        if(echiquier[ind_case-9].c==0 || echiquier[ind_case-9].n==6) insert_element(tab,ind_case-9);
      }
      //une case en diago bas gauche
      if(ind_case+7 <LIMITE && mailbox[tab64[ind_case+7]] !=-1  && mailbox[tab64[ind_case+7]+1] !=-1){
        if(echiquier[ind_case+7].c==0 || echiquier[ind_case+7].n==6) insert_element(tab,ind_case+7);
      }
      //une case en diago bas droite
      if(ind_case+9 <LIMITE && mailbox[tab64[ind_case+9]] !=-1  && mailbox[tab64[ind_case+9]-1] !=-1){
        if(echiquier[ind_case+9].c==0 || echiquier[ind_case+9].n==6) insert_element(tab,ind_case+9);
      }
      break;
  }
}

//recupérer la position d'un roi d'une couleur donnée
int get_pos_roi(){
  if (role==0){
    for (int i=0; i<LIMITE; i++){
      if (echiquier[i].n==0 && echiquier[i].c==0) return i;
    }
  }
  else{
    for (int i=0; i<LIMITE; i++){
      if (echiquier[i].n==0 && echiquier[i].c==1) return i;
    }
  }
}

//Récupérer la pos d'une dame
int get_pos_dame(){
  if (role==0){
    for (int i=0; i<LIMITE; i++){
      if (echiquier[i].n==1 && echiquier[i].c==0) return i;
    }
    return -2;
  }
  else{
    for (int i=0; i<LIMITE; i++){
      if (echiquier[i].n==1 && echiquier[i].c==1) return i;
    }
    return -2;
  }
}

//Récupérer la pos des tours
void get_pos_tours(){
  if (role==0){
    init_array(pos_tours,2);
    for (int i=0; i<LIMITE; i++){
      if (echiquier[i].n==2 && echiquier[i].c==0) insert_element(pos_tours,i);
    }
  }
  else{
    init_array(pos_tours,2);
    for (int i=0; i<LIMITE; i++){
      if (echiquier[i].n==2 && echiquier[i].c==1) insert_element(pos_tours,i);
    }
  }
}

//Récupérer la pos des fous
void get_pos_fous(){
  if (role==0){
    init_array(pos_fous,2);
    for (int i=0; i<LIMITE; i++){
      if (echiquier[i].n==3 && echiquier[i].c==0) insert_element(pos_fous,i);
    }
  }
  else{
    init_array(pos_fous,2);
    for (int i=0; i<LIMITE; i++){
      if (echiquier[i].n==3 && echiquier[i].c==1) insert_element(pos_fous,i);
    }
  }
}

//Récupérer la pos des fous
void get_pos_cavaliers(){
  if (role==0){
    init_array(pos_cavaliers,2);
    for (int i=0; i<LIMITE; i++){
      if (echiquier[i].n==4 && echiquier[i].c==0) insert_element(pos_cavaliers,i);
    }
  }
  else{
    init_array(pos_cavaliers,2);
    for (int i=0; i<LIMITE; i++){
      if (echiquier[i].n==4 && echiquier[i].c==1) insert_element(pos_cavaliers,i);
    }
  }
}

//Récupérer la pos des pions
void get_pos_pions(){
  if (role==0){
    init_array(pos_pions,8);
    for (int i=0; i<LIMITE; i++){
      if (echiquier[i].n==5 && echiquier[i].c==0) insert_element(pos_pions,i);
    }
  }
  else{
    init_array(pos_pions,8);
    for (int i=0; i<LIMITE; i++){
      if (echiquier[i].n==5 && echiquier[i].c==1) insert_element(pos_pions,i);
    }
  }
}

//Savoir si une case est menacée
bool is_attacked(int case_arrive, int couleur, Piece plateau []){
  int cpt =1;
  int testing_cavalier [LIMITE];
  init_array(testing_cavalier,LIMITE);
  switch (couleur){
    case 0 :
      //on vérifie la ligne droite
      while(case_arrive+cpt < LIMITE ){
        if(mailbox[tab64[case_arrive+cpt]] !=-1 && mailbox[tab64[case_arrive+cpt]-1] !=-1 ){
          if ( plateau [case_arrive+cpt].n!=0 && plateau [case_arrive+cpt].c==0) break;
          if (plateau [case_arrive+cpt].c==1 ) {
            if(cpt==1 && plateau [case_arrive+cpt].n==0)return true;
            if(plateau [case_arrive+cpt].n !=1  && plateau [case_arrive+cpt].n !=2 ) break;
            if(plateau [case_arrive+cpt].n == 1 || plateau [case_arrive+cpt].n == 2) return true;
          }
        }
        else break;
        cpt++;
      }
      cpt=1;
      //on vérifie la ligne gauche
      while(case_arrive-cpt >=0 ){
        if(mailbox[tab64[case_arrive-cpt]] !=-1 && mailbox[tab64[case_arrive-cpt]+1] !=-1 ){
          if (plateau [case_arrive-cpt].n!=0 && plateau [case_arrive-cpt].c==0) break;
          if(plateau [case_arrive-cpt].c==1 ) {
            if(cpt==1 && plateau [case_arrive-cpt].n==0) return true;
            if(plateau [case_arrive-cpt].n !=1 && plateau [case_arrive-cpt].n !=2 ) break;
            if(plateau [case_arrive-cpt].n == 1 || plateau [case_arrive-cpt].n == 2) return true;
          }
        }
        else break;
        cpt++;
      }
      cpt =8;
      //on vérifie la ligne du haut
      while(case_arrive-cpt >= 0 ){
        if(mailbox[tab64[case_arrive-cpt]] !=-1){
          if (plateau [case_arrive-cpt].n!=0 && plateau [case_arrive-cpt].c==0) break;
          if(plateau [case_arrive-cpt].c==1 ) {
            if(cpt==8 && plateau [case_arrive-cpt].n==0)return true;
            if(plateau [case_arrive-cpt].n != 1 && plateau [case_arrive-cpt].n != 2 ) break;
            if(plateau [case_arrive-cpt].n == 1 || plateau [case_arrive-cpt].n == 2)return true;
          }
        }
        else break;
        cpt+=8;
      }

      cpt=8;

      //on vérifie la ligne du bas
      while(case_arrive+cpt < LIMITE ){
        if(mailbox[tab64[case_arrive+cpt]] !=-1){
          if (plateau [case_arrive+cpt].n!=0 && plateau [case_arrive+cpt].c==0) break;
          if(plateau [case_arrive+cpt].c==1 ) {
            if(cpt==8 && plateau [case_arrive+cpt].n==0)return true;
            if(plateau [case_arrive+cpt].n !=1 && plateau [case_arrive+cpt].n !=2 ) break;
            if(plateau [case_arrive+cpt].n == 1 || plateau [case_arrive+cpt].n == 2)return true;
          }
        }
        else break;
        cpt+=8;
      }

      cpt = 7;
      //On vérifie la diagonale haute droite
      while(case_arrive-cpt >=0){
        if(mailbox[tab64[case_arrive-cpt]]!=-1 && mailbox[tab64[case_arrive-cpt]-1]!=-1){
          if (plateau [case_arrive-cpt].n!=0 && plateau [case_arrive-cpt].c==0) break;
          if(plateau [case_arrive-cpt].c==1 ) {
            if(cpt==7)
              if(plateau [case_arrive-cpt].n==0 || plateau [case_arrive-cpt].n==5)return true;
            if(plateau [case_arrive-cpt].n !=1 && plateau [case_arrive-cpt].n !=3 ) break;
            if(plateau [case_arrive-cpt].n == 1 || plateau [case_arrive-cpt].n == 3)return true;
          }
        }
        else break;
        cpt+=7;
      }
      cpt=7;
      //On vérifie la diagonale basse gauche
      while(case_arrive+cpt <LIMITE ){
        if(mailbox[tab64[case_arrive+cpt]]!=-1 && mailbox[tab64[case_arrive+cpt]+1]!=-1){
          if (plateau [case_arrive+cpt].n!=0 && plateau [case_arrive+cpt].c==0) break;
          if(plateau [case_arrive+cpt].c==1 ) {
            if(cpt==7 && plateau [case_arrive+cpt].n==0)return true;
            if(plateau [case_arrive+cpt].n !=1 && plateau [case_arrive+cpt].n !=3 ) break;
            if(plateau [case_arrive+cpt].n == 1 || plateau [case_arrive+cpt].n == 3)return true;
          }
        }
        else break;
        cpt+=7;
      }
      cpt=9;

      //On vérifie la diagonale basse droite
      while(case_arrive+cpt <LIMITE ){
        if(mailbox[tab64[case_arrive+cpt]]!=-1 && mailbox[tab64[case_arrive+cpt]-1]!=-1){
          if (plateau [case_arrive+cpt].n!=0 && plateau [case_arrive+cpt].c==0) break;
          if(plateau [case_arrive+cpt].c==1 ) {
            if(cpt==9 && plateau [case_arrive+cpt].n==0)return true;
            if(plateau [case_arrive+cpt].n !=1 && plateau [case_arrive+cpt].n !=3 ) break;
            if(plateau [case_arrive+cpt].n == 1 || plateau [case_arrive+cpt].n == 3)return true;
          }
        }
        else break;
        cpt+=9;
      }
      cpt=9;
      //On vérifie la diagonale haute gauche
      while(case_arrive-cpt >=0 ){
        if(mailbox[tab64[case_arrive-cpt]]!=-1 && mailbox[tab64[case_arrive-cpt]+1]!=-1){
          if (plateau [case_arrive-cpt].n!=0 && plateau [case_arrive-cpt].c==0) break;
          if(plateau [case_arrive-cpt].c==1 ) {
            if(cpt==9)
              if(plateau [case_arrive-cpt].n==0 || plateau [case_arrive-cpt].n==5)return true;

            if(plateau [case_arrive-cpt].n !=1 && plateau [case_arrive-cpt].n !=3 ) break;
            if(plateau [case_arrive-cpt].n == 1 || plateau [case_arrive-cpt].n == 3)return true;
          }
        }
        else break;
        cpt+=9;
      }

      cpt=0;
      //On vérifie si la case n'est pas menacée par un cavalier
      //On parcour l'plateau  case par case, quand on tombe sur un cavalier on génère ses moves possibles dans le tableau
      //quand on a les deplacements possibles des deux cavaliers adverses, on vérifie si la case d'arrivée qu'on a choisis correspond à une des cases possibles pour un cavaliers
      //si c'est le cas on ajout cette case au tableau attacked pour dire que cette case est menacée

      for(int i=0; i<LIMITE; i++){
        if(cpt==2)break;
        if (plateau [i].n==4 && plateau [i].c==1){
          get_moves_cavalier(i,1,testing_cavalier);
          cpt++;
        }
      }
      if(is_in_array(testing_cavalier,case_arrive)) return true;

      break;

    case 1 :
      //on vérifie la ligne droite
      while(case_arrive+cpt < LIMITE ){
        if(mailbox[tab64[case_arrive+cpt]] !=-1 && mailbox[tab64[case_arrive+cpt]-1] !=-1 ){
          if (plateau [case_arrive+cpt].n!=0 && plateau [case_arrive+cpt].c==1) break;
          if(plateau [case_arrive+cpt].c==0 ) {
            if(cpt==1 && plateau [case_arrive+cpt].n==0)return true;
            if(plateau [case_arrive+cpt].n !=1 && plateau [case_arrive+cpt].n !=2 ) break;
            if(plateau [case_arrive+cpt].n == 1 || plateau [case_arrive+cpt].n == 2)return true;
          }
        }
        else break;
        cpt++;
      }
      cpt=1;
      //on vérifie la ligne gauche
      while(case_arrive-cpt >=0 ){
        if(mailbox[tab64[case_arrive-cpt]] !=-1 && mailbox[tab64[case_arrive-cpt]+1] !=-1 ){
          if (plateau [case_arrive-cpt].n!=0 && plateau [case_arrive-cpt].c==1) break;
          if(plateau [case_arrive-cpt].c==0 ) {
            if(cpt==1 && plateau [case_arrive-cpt].n==0)return true;
            if(plateau [case_arrive-cpt].n !=1 && plateau [case_arrive-cpt].n !=2 ) break;
            if(plateau [case_arrive-cpt].n == 1 || plateau [case_arrive-cpt].n == 2)return true;
          }
        }
        else break;
        cpt++;
      }
      cpt =8;
      //on vérifie la ligne du haut
      while(case_arrive-cpt >= 0 ){
        if(mailbox[tab64[case_arrive-cpt]] !=-1){
          if (plateau [case_arrive-cpt].n!=0 && plateau [case_arrive-cpt].c==1) break;
          if(plateau [case_arrive-cpt].c==0 ) {
            if(cpt==8 && plateau [case_arrive-cpt].n==0)return true;
            if(plateau [case_arrive-cpt].n != 1 && plateau [case_arrive-cpt].n != 2 ) break;
            if(plateau [case_arrive-cpt].n == 1 || plateau [case_arrive-cpt].n == 2)return true;
          }
        }
        else break;
        cpt+=8;
      }

      cpt=8;

      //on vérifie la ligne du bas
      while(case_arrive+cpt < LIMITE ){
        if(mailbox[tab64[case_arrive+cpt]] !=-1){
          if (plateau [case_arrive+cpt].n!=0 && plateau [case_arrive+cpt].c==1) break;
          if(plateau [case_arrive+cpt].c==0 ) {
            if(cpt==8 && plateau [case_arrive+cpt].n==0)return true;
            if(plateau [case_arrive+cpt].n !=1  && plateau [case_arrive+cpt].n != 2 ) break;
            if(plateau [case_arrive+cpt].n == 1 || plateau [case_arrive+cpt].n == 2)return true;
          }
        }
        else break;
        cpt+=8;
      }

      cpt = 7;
      //On vérifie la diagonale haute droite
      while(case_arrive-cpt >=0){
        if(mailbox[tab64[case_arrive-cpt]]!=-1 && mailbox[tab64[case_arrive-cpt]-1]!=-1){
          if (plateau [case_arrive-cpt].n!=0 && plateau [case_arrive-cpt].c==1) break;
          if(plateau [case_arrive-cpt].c==0 ) {
            if(cpt==7 && plateau [case_arrive-cpt].n==0)return true;
            if(plateau [case_arrive-cpt].n !=1  && plateau [case_arrive-cpt].n != 3 ) break;
            if(plateau [case_arrive-cpt].n == 1 || plateau [case_arrive-cpt].n == 3)return true;
          }
        }
        else break;
        cpt+=7;
      }
      cpt=7;
      //On vérifie si on a pas de fou ou de dame sur la diagonale basse gauche
      while(case_arrive+cpt <LIMITE ){
        if(mailbox[tab64[case_arrive+cpt]]!=-1 && mailbox[tab64[case_arrive+cpt]+1]!=-1){
          if (plateau [case_arrive+cpt].n!=0 && plateau [case_arrive+cpt].c==1) break;
          if(plateau [case_arrive+cpt].c==0 ) {
            if(cpt==7)
              if(plateau [case_arrive+cpt].n==0 || plateau [case_arrive+cpt].n==5)return true;
            if(plateau [case_arrive+cpt].n !=1  && plateau [case_arrive+cpt].n != 3 ) break;
            if(plateau [case_arrive+cpt].n == 1 || plateau [case_arrive+cpt].n == 3)return true;
          }
        }
        else break;
        cpt+=7;
      }
      cpt=9;

      //On vérifie la diagonale basse droite
      while(case_arrive+cpt <LIMITE ){
        if(mailbox[tab64[case_arrive+cpt]]!=-1 && mailbox[tab64[case_arrive+cpt]-1]!=-1){
          if (plateau [case_arrive+cpt].n!=0 && plateau [case_arrive+cpt].c==1) break;
          if(plateau [case_arrive+cpt].c==0 ) {
            if(cpt==9)
              if(plateau [case_arrive+cpt].n==0 || plateau [case_arrive+cpt].n==5)return true;
            if(plateau [case_arrive+cpt].n != 1 && plateau [case_arrive+cpt].n != 3 ) break;
            if(plateau [case_arrive+cpt].n == 1 || plateau [case_arrive+cpt].n == 3)return true;
          }
        }
        else break;
        cpt+=9;
      }
      cpt=9;
      //On vérifie la diagonale haute gauche
      while(case_arrive-cpt >=0 ){
        if(mailbox[tab64[case_arrive-cpt]]!=-1 && mailbox[tab64[case_arrive-cpt]+1]!=-1){
          if (plateau [case_arrive-cpt].n!=0 && plateau [case_arrive-cpt].c==1) break;
          if(plateau [case_arrive-cpt].c==0 ) {
            if(cpt==9 && plateau [case_arrive-cpt].n==0)return true;
            if(plateau [case_arrive-cpt].n !=1  && plateau [case_arrive-cpt].n != 3 ) break;
            if(plateau [case_arrive-cpt].n == 1 || plateau [case_arrive-cpt].n == 3)return true;
          }
        }
        else break;
        cpt+=9;
      }
      //cases menacées par des cavaliers

      for(int i=0; i<LIMITE; i++){
        if(cpt==2)break;
        if (plateau [i].n==4 && plateau [i].c==0){
          get_moves_cavalier(i,0,testing_cavalier);
          cpt++;
        }
      }
      if(is_in_array(testing_cavalier,case_arrive)) return true;
      break;
  }
  return false;
}

//bouger une pièce sur l'échiquier
bool move_piece(int dep, int arr, Piece plateau[], int moves []){
  for(int i=0; i<TAILLE; i++){
    //si on arrive à une valeur -2 ça veut dire qu'on a parcourru les moves possibles et que la case demandée n'y figure pas
    // donc la case donnée est invalide, on affiche le message d'erreur et on quitte la boucle
    if(moves[i]==-2){
      system("clear");
      banner("../Utiles/banner.txt");
      wprintf(L"Déplacement impossible ! Entrez une case valide !\n\n");
      break;
    }
    if(arr == moves[i]){

      if(echiquier[arr].n==6 && echiquier[dep].c==0 && echiquier[dep].n==5){
        if(dep-9==arr || dep-7==arr){
          echiquier[arr+8]=case_vide;
        }
      }
      if(echiquier[arr].n==6 && echiquier[dep].c==1 && echiquier[dep].n==5){
        if(dep+9==arr || dep+7==arr){
          echiquier[arr-8]=case_vide;
        }
      }

      plateau [arr]=plateau [dep];
      plateau [dep]=case_vide;
      return true;
    }
  }
  return false;
}

//gérer le jeu à tour de role
bool gerer_tour(int role, int piece){
  if (role==0){
    if(echiquier[piece].c==0) return true;
    else {
      system("clear");
      banner("../Utiles/banner.txt");
      wprintf(L"C'est aux blancs de jouer !\n");
      return false;
    }
  }
  if (role==1){
    if(echiquier[piece].c==1) return true;
    else {
      system("clear");
      banner("../Utiles/banner.txt");
      wprintf(L"C'est aux noirs de jouer !\n");
      return false;
    }
  }
}

//sauvegarder une partie
void save_game(char date [20], char nom[20]){
  FILE *fp;
  strcpy(savefile, "Sauvegarde_le_");
  strcat(savefile, date);
  strcat(savefile, nom);
  strcat(savefile, ".txt");
  fp= fopen(savefile,"w");
  fprintf(fp,"%i\n",role);
  for(int i=0; i<LIMITE; i++){
    fprintf(fp,"%i %i %i\n",i,echiquier[i].n,echiquier[i].c);
  }
  fclose(fp);
}

//charger une partie
void load_game(char partie [100]){
/*  FILE *fp;
  strcpy(savefile,"");
  strcpy(savefile,"../Utiles/");
  fp= fopen(strcat(savefile,partie),"r");
  int pos;
  int type;
  int color;

  if (fp != NULL)
    {
        fscanf(fp, "%d %d %d", &pos, &type, &color);


        fclose(fichier);
    }*/
}

//permuter la place entre deux pieces
void permuter_piece(int piece_une, int piece_deux, Piece plateau []){
  Piece tmp  = plateau [piece_une];
  plateau [piece_une]=plateau [piece_deux];
  plateau [piece_deux]= tmp;
}

//Le roque
bool roquer(int position_tour){

  if(echiquier[position_tour].n!=2)
    wprintf(L"essayez avec une position valide !");
  else{
    if(role==0 && !bl_roque){
      switch(position_tour){
        case 63 :
          if(echiquier[62].n==6 && echiquier[61].n==6){
            if(!is_attacked(get_pos_roi(),0,echiquier) && !is_attacked( position_tour, 0, echiquier) && !is_attacked(62,0,echiquier) && !is_attacked(61,0,echiquier)){
              if(!echiquier[get_pos_roi()].bouge && !echiquier[position_tour].bouge){
                echiquier[62]=echiquier[60];
                echiquier[61]=echiquier[63];
                echiquier[60]=case_vide;
                echiquier[63]=case_vide;
                cpy_plateau(echiquier,test_echiquier);
                bl_roque = true;
                return true;
              }
              else return false;
            }
            else return false;
          }
          else return false;
          break;
        case 56 :
          if(echiquier[57].n==6 && echiquier[58].n==6 && echiquier[59].n==6){
            if(!is_attacked(get_pos_roi(),0,echiquier) && !is_attacked( position_tour, 0, echiquier) && !is_attacked(57,0,echiquier) && !is_attacked(58,0,echiquier) && !is_attacked(59,0,echiquier)){
              if(!echiquier[get_pos_roi()].bouge && !echiquier[position_tour].bouge){
                echiquier[58]=echiquier[60];
                echiquier[59]=echiquier[56];
                echiquier[56]=case_vide;
                echiquier[57]=case_vide;
                echiquier[60]=case_vide;
                cpy_plateau(echiquier,test_echiquier);
                bl_roque = true;
                return true;
              }
              else return false;
            }
            else return false;
          }
          else return false;
          break;
      }
    }
    if(role==1 && !nr_roque){
      switch(position_tour){
        case 7 :
          if(echiquier[5].n==6 && echiquier[6].n==6){
            if(!is_attacked(get_pos_roi(),1,echiquier) && !is_attacked( position_tour, 1, echiquier) && !is_attacked(5,1,echiquier) && !is_attacked(6,1,echiquier)){
              if(!echiquier[get_pos_roi()].bouge && !echiquier[position_tour].bouge){
                echiquier[6]=echiquier[4];
                echiquier[5]=echiquier[7];
                Piece case_vide = {VIDE,NONE,value[0],false};
                echiquier[4]=case_vide;
                echiquier[7]=case_vide;
                cpy_plateau(echiquier,test_echiquier);
                nr_roque =true;
                return true;
              }
              else return false;
            }
            else return false;
          }
          else return false;
          break;
        case 0 :
          if(echiquier[1].n==6 && echiquier[2].n==6 && echiquier[3].n==6){
            if(!is_attacked(get_pos_roi(),1,echiquier) && !is_attacked( position_tour, 1, echiquier) && !is_attacked(1,1,echiquier) && !is_attacked(2,1,echiquier) && !is_attacked(3,1,echiquier)){
              if(!echiquier[get_pos_roi()].bouge && !echiquier[position_tour].bouge){
                echiquier[3]=echiquier[2];
                echiquier[2]=echiquier[4];
                Piece case_vide = {VIDE,NONE,value[0],false};
                echiquier[0]=case_vide;
                echiquier[1]=case_vide;
                echiquier[4]=case_vide;
                cpy_plateau(echiquier,test_echiquier);
                nr_roque =true;
                return true;
              }
              else return false;
            }
            else return false;
          }
          else return false;
          break;
      }
    }
  }
}

//récupérer les indices à partir des cases fournies par l'utilisateur
void get_indices (){
  wprintf(L"\n\n Instruction 1 -> ");
  scanf("%s",case_dep);

  if(strcmp(case_dep,"exit")==0) exit(0);
  if(strcmp(case_dep,"save")==0){
    wprintf(L"\n\n Vous avez choisis de sauvegarder et quitter la partie ! ");
    wprintf(L"\n\n Entrez votre nom (Ex: Martin) -> ");
    scanf("%s",nom_save);
    wprintf(L"\n\n Entrez la date du jour (Ex: 25-03-2021) ->");
    scanf("%s",date_save);

    save_game(date_save,nom_save);
    wprintf(L"\n\n Votre partie a bien été enregistrée ! A la prochaine !");

    exit(0);
  }
  if(strcmp(case_dep,"roque")==0){
    wprintf(L"\nEntrez la case de la tour à roquer ->  ");
    scanf("%s",tour_to_roque);
    for(int i=0; i<LIMITE; i++){
      if(strcmp(tour_to_roque, coord[i])==0){
        pos_tour_to_roque = i;
      }
    }
  }
  else{
    wprintf(L"\nInstruction 2 ->  ");
    scanf("%s",case_arr);

    //if(strcmp(case_dep,"save")==0)save_game();
    for(int i=0; i<LIMITE; i++){
      if(strcmp(case_dep, coord[i])==0){
        indice_dep = i;
      }
      if(strcmp(case_arr,coord[i])==0){
        indice_arr = i;
        strcpy(tmp_last_move, case_arr);
      }

    }
  }
}

//switch les roles
void switch_role (){
  if(role==0)role=1;
  else role=0;
}

//appeller la bonne fonction d'affichage en fonction du role
void afficher(){
  if(role==0) affiche_plateau();
  else affiche_plateau_mirroir();
}

//détecter si le camp qui a le tour est en echec on renvoie true si on est en echec, sinon false
bool detect_echec( Piece plateau[] ){
  if (role == 0 ){
    if(is_attacked(get_pos_roi(),0,plateau)){
      return true;
    }
    else return false;
  }
  else{
    if(is_attacked(get_pos_roi(),1,plateau)){
      return true;
    }
    else return false;
  }
}

//tester si un deplacement met le roi en echec ou pas, pour savoir si il est permis
bool test_echec_after_move(int depart, int arrive, int moves []){
  if (move_piece(depart,arrive,test_echiquier, moves)){
    if (detect_echec(test_echiquier))
      return true;
    else
      return false;
  }
  else return false;
}

//gère le deplacement de la pièce sélectionnée
bool deplacement_piece(int indice_dep, int indice_arr){
  init_array(possible_moves,TAILLE);
  switch (echiquier[indice_dep].n) {
    case 0 :
      if(echiquier[indice_dep].c==0){
        if(!is_attacked(indice_arr,0,echiquier)){
          init_array(possible_moves,TAILLE);
          get_moves_roi(indice_dep,echiquier[indice_dep].c,possible_moves);
          if(move_piece(indice_dep,indice_arr,echiquier,possible_moves)){
            cpy_plateau(echiquier,test_echiquier);
            echiquier[indice_arr].bouge=true;
           return true;
          }
          else return false;

        }
        else {
          system("clear");
          banner("../Utiles/banner.txt");
          wprintf(L"Cette case est menacée! déplacement impossible !\n\n");
          return false;
        }
      }
      else{
        if(!is_attacked(indice_arr,1,echiquier)){
          get_moves_roi(indice_dep,echiquier[indice_dep].c,possible_moves);
          if(move_piece(indice_dep,indice_arr,echiquier,possible_moves)) {
            cpy_plateau(echiquier,test_echiquier);
            return true;
          }
          else return false;
        }
        else{
          system("clear");
          banner("../Utiles/banner.txt");
          wprintf(L"Cette case est menacée! déplacement impossible !\n\n");
          return false;
        }
      }
      break;

    case 1 :
      get_moves_dame(indice_dep,echiquier[indice_dep].c,possible_moves);
      if(test_echec_after_move(indice_dep,indice_arr,possible_moves)) {
        system("clear");
        banner("../Utiles/banner.txt");
        wprintf(L"Le roi est en echec, ce deplacement est impossible !\n\n");
        cpy_plateau(echiquier,test_echiquier);
        return false;
      }
      else{
        if(move_piece(indice_dep,indice_arr,echiquier,possible_moves)){
          cpy_plateau(echiquier,test_echiquier);
          return true;
        }
        else return false;
      }
      break;
    case 2 :
      get_moves_tour(indice_dep,echiquier[indice_dep].c,possible_moves);
      if(test_echec_after_move(indice_dep,indice_arr,possible_moves)) {
        system("clear");
        banner("../Utiles/banner.txt");
        wprintf(L"Le roi est en echec, ce deplacement est impossible !\n\n");
        cpy_plateau(echiquier,test_echiquier);
        return false;
      }
      else{
        if(move_piece(indice_dep,indice_arr,echiquier,possible_moves)){
          cpy_plateau(echiquier,test_echiquier);
          echiquier[indice_arr].bouge=true;
          return true;
        }
        else return false;
      }
      break;
    case 3 :
      init_array(possible_moves,TAILLE);
      get_moves_fou(indice_dep,echiquier[indice_dep].c,possible_moves);

      if(test_echec_after_move(indice_dep,indice_arr,possible_moves)) {
        system("clear");
        banner("../Utiles/banner.txt");
        wprintf(L"Le roi est en echec, ce deplacement est impossible !\n\n");
        cpy_plateau(echiquier,test_echiquier);
        return false;
      }
      else{
        if(move_piece(indice_dep,indice_arr,echiquier,possible_moves)){
          cpy_plateau(echiquier,test_echiquier);
          return true;
        }
        else return false;
      }
      break;
    case 4 :
      get_moves_cavalier(indice_dep,echiquier[indice_dep].c,possible_moves);
      if(test_echec_after_move(indice_dep,indice_arr,possible_moves)) {
        system("clear");
        banner("../Utiles/banner.txt");
        wprintf(L"Le roi est en echec, ce deplacement est impossible !\n\n");
        cpy_plateau(echiquier,test_echiquier);
        return false;
      }
      else{
        if(move_piece(indice_dep,indice_arr,echiquier,possible_moves)){
          cpy_plateau(echiquier,test_echiquier);
          return true;
        }
        else return false;
      }
      break;
    case 5 :
      get_moves_pion(indice_dep,echiquier[indice_dep].c,possible_moves);
      if(test_echec_after_move(indice_dep,indice_arr,possible_moves)) {
        cpy_plateau(echiquier,test_echiquier);
        system("clear");
        banner("../Utiles/banner.txt");
        wprintf(L"Le roi est en echec, ce deplacement est impossible !\n\n");
        return false;
      }
      else{
        if(move_piece(indice_dep,indice_arr,echiquier,possible_moves)){
          cpy_plateau(echiquier,test_echiquier);
          first_pos = indice_dep;
          new_pos = indice_arr;
          if(indice_arr<8 && indice_arr>=0){
            int choix =0;
            wprintf(L"Le pion est promu ! Tapez le numéro de votre choix : 1_ Dame || 2_ Tour || 3_fou || 4_Cavalier : ");
            scanf("%i",&choix);
            if(choix==1 && role==0) echiquier[indice_arr] = b_dame;
            if(choix==2 && role==0) echiquier[indice_arr] = b_tour;
            if(choix==3 && role==0) echiquier[indice_arr] = b_fou;
            if(choix==4 && role==0) echiquier[indice_arr] = b_cavalier;
          }
          if(indice_arr<64 && indice_arr>55){
            int choix =0;
            wprintf(L"Le pion est promu ! Tapez le numéro de votre choix : 1_ Dame || 2_ Tour || 3_fou || 4_Cavalier : ");
            scanf("%i",&choix);
            if(choix==1 && role==1) echiquier[indice_arr] = n_dame;
            if(choix==2 && role==1) echiquier[indice_arr] = n_tour;
            if(choix==3 && role==1) echiquier[indice_arr] = n_fou;
            if(choix==4 && role==1) echiquier[indice_arr] = n_cavalier;
          }

          cpy_plateau(echiquier,test_echiquier);
          return true;
        }
        else return false;
      }
      break;
  }
}

//echec et mat : fin du jeu
bool game_over (){
  int pos=0;
  bool can_save = false;
  //on detecte si on est en echec en premier lieu
  if(detect_echec(echiquier)){
    //on initialise le tableau sur lequel on va faire nos test
    init_array(deplacement_echec,LIMITE);
    //on recupère les moves du roi dans le tableau
    get_moves_roi(get_pos_roi(),role,deplacement_echec);
    //On verifie si une des cases possibles n'est pas attaquée, si on en troouve une alors le roi peut esquiver l'echec
    for(int i=0; i<LIMITE ; i++){
      if(deplacement_echec[i]==-2)break;
      if(!is_attacked(deplacement_echec[i],role, echiquier)) return false;
    }

    pos=get_pos_dame();
    if (get_pos_dame() != -2){
      init_array(deplacement_echec,LIMITE);
      get_moves_dame(pos,role,deplacement_echec);
      for(int i=0; i<LIMITE; i++){
        if(deplacement_echec[i]==-2)break;
        if(!test_echec_after_move(pos,deplacement_echec[i],deplacement_echec)){
          cpy_plateau(echiquier,test_echiquier);
          return false;
        }
        cpy_plateau(echiquier,test_echiquier);
      }
    }
    get_pos_tours();
    for(int j=0; j<2; j++){
      if (pos_tours[j] != -2){
        pos=pos_tours[j];
        init_array(deplacement_echec,LIMITE);
        get_moves_tour(pos,role,deplacement_echec);
        for(int i=0; i<LIMITE; i++){
          if(deplacement_echec[i]==-2)break;
          if(!test_echec_after_move(pos,deplacement_echec[i],deplacement_echec)){
            cpy_plateau(echiquier,test_echiquier);
            return false;
          }
          cpy_plateau(echiquier,test_echiquier);
        }
      }
    }
    get_pos_fous();
    for(int j=0; j<2; j++){
      if (pos_fous[j] != -2){
        pos=pos_fous[j];
        init_array(deplacement_echec,LIMITE);
        get_moves_fou(pos,role,deplacement_echec);
        for(int i=0; i<LIMITE; i++){
          if(deplacement_echec[i]==-2)break;
          if(!test_echec_after_move(pos,deplacement_echec[i],deplacement_echec)){
            cpy_plateau(echiquier,test_echiquier);
            return false;
          }
          cpy_plateau(echiquier,test_echiquier);
        }
      }
    }
    get_pos_cavaliers();
    for(int j=0; j<2; j++){
      if (pos_cavaliers[j] != -2){
        pos=pos_cavaliers[j];
        init_array(deplacement_echec,LIMITE);
        get_moves_cavalier(pos,role,deplacement_echec);

        for(int i=0; i<LIMITE; i++){
          if(deplacement_echec[i]==-2)break;
          if(!test_echec_after_move(pos,deplacement_echec[i],deplacement_echec)){
            cpy_plateau(echiquier,test_echiquier);
            return false;
          }
          cpy_plateau(echiquier,test_echiquier);
        }
      }
    }
    get_pos_pions();
    for(int j=0; j<8; j++){
      if (pos_pions[j] != -2){
        pos=pos_pions[j];
        init_array(deplacement_echec,LIMITE);
        get_moves_pion(pos,role,deplacement_echec);
        for(int i=0; i<LIMITE; i++){
          if(deplacement_echec[i]==-2)break;
          if(!test_echec_after_move(pos,deplacement_echec[i],deplacement_echec)){
            cpy_plateau(echiquier,test_echiquier);
            return false;
          }
          cpy_plateau(echiquier,test_echiquier);
        }
      }
    }
    //si on arrive à ce stade c'est que rien ne peut esquiver l'echec et donc c'est un echec et mat
    return true;
  }
  else return false;
}

//débuter un jeu
void start_game(){
  system("clear");
  init_plateau(echiquier);
  init_plateau(test_echiquier);
  while(true){
    if(game_over()) break;
    banner("../Utiles/banner.txt");
    afficher();
    get_indices();
    if(strcmp(case_dep,"roque")==0){
      if(!roquer(pos_tour_to_roque)){
        wprintf(L"Roque impossible, conditions insatisfaites!");
      }
      else{
        if(role==0) white_pl= true;
        else black_pl = true;
      }
    }
    else{
      //on s'assure que c'est le bon joueur qui joue et que le deplacement est valide
      while(!gerer_tour(role,indice_dep) || !deplacement_piece(indice_dep,indice_arr)){
        afficher();
        get_indices();
      }
      if(role==0){
        white_pl= true;
        strcpy(bl_last_move, tmp_last_move);
      }
      else{
        black_pl = true;
        strcpy(nr_last_move, tmp_last_move);
      }
    }
    system("clear");
    if(black_pl==true || white_pl==true){
      black_pl =false;
      white_pl =false;
      switch_role();
    }
  }
  system("clear");
  afficher ();
  if(role==1)banner("../Utiles/blanc.txt");
  else banner("../Utiles/noir.txt");
  exit(0);
}

void menu (){
  system("clear");
  banner("../Utiles/banner2.txt");
  char menu_option;
  do{
    wprintf(L"\n\n\n");
    wprintf(L"Menu du jeu : \n\n");
    wprintf(L"a. Commencer une nouvelle partie.\n");
    wprintf(L"b. Charger une partie.\n");
    wprintf(L"c. Afficher les parties sauvegardées .\n");
    wprintf(L"d. Quitter.\n\n");
    wprintf(L"Entrez votre choix : ");
    scanf("%c",&menu_option);

    switch(menu_option){

    case 'a':
        start_game();
        break;
    case 'b':
        wprintf(L"entrez le nom du fichier de votre sauvegarde");
        scanf("%s",load);
        load_game(load);
        break;
    case'c':
        //show_saved_games();
        break;
    case'd':
        break;

    default:
        wprintf(L"invalid input");
        break;
    }

  }
  while(menu_option !='d');

}

//Menu du jeu
int main (){
setlocale(LC_CTYPE, "");
menu();
return 0;
}
