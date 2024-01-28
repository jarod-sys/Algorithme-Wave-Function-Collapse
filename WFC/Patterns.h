#ifndef PATTERNS_H_INCLUDED
#define PATTERNS_H_INCLUDED

#include "Utils_wfc.h"



/*
-------------------------DESCRIPTION--------------------

Structure qui represente une matrice de tuiles

--------------------------CHAMPS------------------------

int height_p        : Longeur de la matrice de tuiles
int width_p         : Largueur de la matrice de tuiles
int size_tile_w     : Largueur  des tuiles
int size_tile_h     : Longeur  des tuiles
Tile* tile          : pointeur vers la Matrice de tuiles

*/
typedef struct {
    int height_p;
    int width_p;
    int size_tile_h;
    int size_tile_w;
    Tile* tile;
}Patterns;

//----------------------------------------------------------------------------------------

/*
-------------------------DESCRIPTION---------------------

Vider la mémoire tempon de la machine

*/
void ViderBuffer();
/*
-------------------------DESCRIPTION---------------------

Affiche tous les caractéristiques de la tuile "*patterns"

--------------------------ARGUMENTS----------------------

patterns   : pointe vers la tuile à afficher


*/
void Affiche_AllTile(Patterns *patterns);
/*
-------------------------DESCRIPTION---------------------

Affiche tous les tuiles de la strutures patterns

--------------------------ARGUMENTS------------------------

patterns   : pointe vers la matrice de tuiles


*/
void Affiche_AllRule_Pat(Patterns *patterns);
/*
-------------------------DESCRIPTION---------------------
Lire une chaine de caractère en entrée de longueur au plus "longueur"

--------------------------ARGUMENTS------------------------

chaine   : pointe vers une chaine de caractère
longueur : longueur maximale de la chaine "*chaine"

--------------------------VALEURS------------------------
1  : Si la lecture s'est bieb passée
0  : sinon

*/
int Lire(char *chaine, int longueur);
/*
-------------------------DESCRIPTION---------------------

Calcule le nombre d'occurrence de chaque tuile de "*patterns"

--------------------------ARGUMENTS------------------------

patterns   : pointe vers une structure Pattern
longueur : longueur maximale de la chaine "*chaine"

*/
void PoidsTile(Patterns* patterns);

/*
-------------------------DESCRIPTION---------------------
Compare deux couleur

--------------------------ARGUMENTS------------------------

color1   : pointe vers la première couleur
color2   : pointe vers la deuxième couleur

--------------------------VALEURS------------------------
1  : Si les couleurs sont identiques
0  : sinon

*/
bool Same_color(Color *color1, Color *color2);
/*
-------------------------DESCRIPTION---------------------

Compare les matrices de couleurs de deux structures de Tiles

--------------------------ARGUMENTS-----------------------

tile1                       : pointe vers une chaine de caractère
tile2                       : longueur maximale de la chaine "*chaine"
(size_tile_h,size_tile_w)   : Taille de la matrice de couleur commune

--------------------------VALEURS------------------------
1  : Si les couleurs sont identiques
0  : sinon

*/
bool CompareTile(Tile *tile1,Tile *tile2,int size_tile_h,int size_tile_w);
/*
-------------------------DESCRIPTION---------------------
Sauvegarde tous les tuiles de la structure "*patterns"

--------------------------ARGUMENTS------------------------

patterns   : pointe vers une matrice de Tile


*/
void Sauvegarde_P(Patterns *patterns);
/*
-------------------------DESCRIPTION---------------------

Ajoute à chaque tuile de la matrice de tuiles "*patterns"
ses tuiles voisins

--------------------------ARGUMENTS------------------------

patterns   : pointe vers une matrice de tuiles


*/
void ContraintesTile(Patterns* patterns);
/*
-------------------------DESCRIPTION---------------------

Ajoute à chaque tuile de la matrice de tuiles "*patterns"
les voisins de tous les autres tuiles de même couleur

--------------------------ARGUMENTS------------------------

patterns   : pointe vers une matrice de tuile

*/
void Mise_AJC_voisin(Patterns* patterns);
/*
-------------------------DESCRIPTION---------------------

Active le champ "Classe" de la tuile "tile" selon
qu'il represente d'autres tuiles ou non

--------------------------ARGUMENTS------------------------

tile   : pointe vers une structure de Tile
a      : True ou False

--------------------------VALEURS------------------------

tile->classe : True, si c'est un représentant
             : False, sinon

*/
void Active(Tile *tile,bool a);
/*
-------------------------DESCRIPTION---------------------

Ajoute le voisin de "direction" de la tuile de coordonnées
(a,b) dans la matrice de tuiles "*patterns"

--------------------------ARGUMENTS------------------------

patterns  : pointe vers une  matrice de tuiles
(a,b)     : Position de la tuile dans "*patterns"
direction : 0 Haut
            1 droite
            2 bas
            3 gauche
            4 haut-gauche
            5 haut-droite
            6 bas-droite
            7 bas-gauche

*/
void VoisinTile(Patterns*patterns, int a, int b,int direction);
/*
-------------------------DESCRIPTION---------------------

Initialise la tuile "*t" avec la taille "size_tile_h,size_tile_w"
et son identifiant "id_tile"

--------------------------ARGUMENTS------------------------

t   : pointe vers une structure de Tile
id_tile : taille de la matrice de couleur t->tile_Color

--------------------------VALEURS------------------------

Creation de la matrice de couleur
t->tile_Color,avec la taille "id_tile"
t->classe =true;
t->id     =id_tile;
t->poid   =1;

*/
void New_Tile(Tile *t, int size_tile_h,int size_tile_w, int id_tile);

/*
-------------------------DESCRIPTION---------------------

Initialise la matrice de tuiles "*patterns"

--------------------------ARGUMENTS------------------------

patterns : pointe vers la matrice de tuile
height   : Largeur de la matrice de tuiles
width    : Longueur de la matrice de tuiles

--------------------------VALEURS------------------------
patterns->tile    pointe vers une matrice de tuiles
patterns->height= height
patterns->width = width

*/
void Init_patterns(Patterns *patterns, int height,int width);
/*
-------------------------DESCRIPTION---------------------

Récupère le bloc de couleurs dans la matrice de couleur "*cimg"
pour tous les tuiles de "*patterns" correspondants

*/
void InitColorPatterns(Patterns *patterns, ColorImage *cimg);
/*
-------------------------DESCRIPTION---------------------

Récupère un bloc de couleurs de la taile de "*tile"
dans la matrice de couleur "*cimg" à partir du point
(height,width)

--------------------------ARGUMENTS------------------------
Cimg             : pointe vers une matrice de couleur

(height,width)   : positionnement dans la matrice de couleur
                   "*Cimg"
*colordefault    : Couleur par defaut si (height,width)  depasse les marges
                   "*Cimg"
tile             : pointe vers une structure Tile

--------------------------VALEURS------------------------

tile->tile_Color : Contient la couleur escomptée.

*/
void Color_Tile(Tile *tile,ColorImage *cimg, Color *colordefault,int height, int width);
/*
-------------------------DESCRIPTION---------------------

Compte le nombre de tuiles distincts dans
la matrice de tuiles "*patterns"

--------------------------ARGUMENTS------------------------

patterns        : pointe vers une matrice de tuiles
TileclassActive : pointe vers une structure de Rule vide

--------------------------VALEURS------------------------

TileclassActive : pointe vers une structure de Rule
                  qui contient les id et les poids des tuiles
                  qui représentent les autres
*/
void Counter_class(Patterns* patterns,Rule *TileclassActive);
/*
-------------------------DESCRIPTION---------------------

Supprime les éléments de la structure "*t"

*/
void Tile_free(Tile *t);
/*
-------------------------DESCRIPTION---------------------

Supprime la matrice de tuiles *pattern

*/
void Free_Patterns(Patterns *pattern);

#endif // PATTERNS_H_INCLUDED
