#include <stdbool.h>

//nom des pieces
typedef enum { ROI, DAME, TOUR, FOU, CAVALIER, PION, VIDE } names;
//couleur des pieces
typedef enum { BLANC, NOIR, NONE } color;
// valeur des pièces
int value [] = {0,9,5,3,3,1,77};
//Structure d'une piece
typedef struct {names n; color c; int v; bool bouge;} Piece;


void to_String(Piece p);
//unicode pieces blanches
wchar_t roi_bl = 0x2654;
wchar_t dame_bl = 0x2655;
wchar_t tour_bl = 0x2656;
wchar_t fou_bl = 0x2657;
wchar_t cavalier_bl = 0x2658;
wchar_t pion_bl = 0x2659;

//unicode pieces noires
wchar_t roi_n = 0x265A;
wchar_t dame_n=  0x265B;
wchar_t tour_n = 0x265C;
wchar_t fou_n=  0x265D;
wchar_t cavalier_n=  0x265E;
wchar_t pion_n = 0x265F;
