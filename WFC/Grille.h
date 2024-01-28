#ifndef GRILLE_H_INCLUDED
#define GRILLE_H_INCLUDED

#include "ColorImage.h"
#include "Patterns.h"

/*
-------------------------DESCRIPTION--------------------

Structure qui represente une cellule d'une grille

--------------------------CHAMPS------------------------

int   id        : Identifiant de la cellule si etat=False
int   collapse  : 1 si Etat= True, 0 sinon
bool  etat      : True ou False
float entropie  : Entropie de la cellule
Rule  rule      : Liste courante d'identifiants de tuiles

*/
typedef struct {
    int id;
    int collapse;
    bool etat;
    float entropie;
    Rule rule;
}Cellule;


/*
-------------------------DESCRIPTION--------------------

Structure qui represente une matrice de cellules

--------------------------CHAMPS------------------------

int   height_g    : Largeur de la grille
int   wigth_g     : Longueur de la grille
Cellule *cellules : matrice de cellules
*/

typedef struct {
    int height_g;
    int wigth_g;
    Cellule *cellules;
}Grille;


/*
-------------------------DESCRIPTION--------------------

Initialise la cellule avec les identifiants de tuiles
contenus dans "*listeRule"

--------------------------ARGUMENTS------------------------

cell      : pointe vers une cellule
listeRule : pointe vers la liste d'indentifiants

--------------------------VALEURS------------------------

Mise à jour de "cell->rule" par "*listeRule"

*/
void New_Cell(Cellule *cell, Rule *listeRule);

/*
-------------------------DESCRIPTION--------------------

Initialise la grille de cellule "*grille" de taille "height"
et "width"

--------------------------ARGUMENTS------------------------

grille    : pointe vers une matrice de cellules
height    : pointe vers une cellule
width     : pointe vers la liste d'indentifiants
listeRule : pointe vers la liste d'indentifiants
--------------------------VALEURS------------------------

grille->height =height
grille->width  =width
Mise à jour de tous les "cell->rule" par "*listeRule"

*/
void Init_grille(Grille *grille, Rule *listeRule ,int height,int width);
/*
-------------------------DESCRIPTION--------------------

Affiche la grille avec les etats de cahque cellule

--------------------------VALEURS------------------------
0 : si l'etat de la cellule est False
1 : sinon

*/
void EtatDeLaGrille(Grille*grille);
/*
-------------------------DESCRIPTION--------------------

Initialise une cellule par la tuile ayant la plus
grande frequence

--------------------------VALEURS------------------------

alea_t            : retourne l'identifiant de la tuile
                    choisie
(alea_g1,alea_g2) : retourne les coordonnées de la cellule
                    choisie
position          : retourne la position dans la grille

*/
void InitialiseGrille(Grille *grille,int *alea_t,int *alea_g1,int *alea_g2,int *position);

/*
-------------------------DESCRIPTION--------------------
Affiche les indentifiants de chaque cellule

*/

void IdCelluleGrille(Grille* grille);

void AfficheRuleCelluleGrille(Grille* grille);

/*
-------------------------DESCRIPTION--------------------

Mettre à jour la cellule "cell->rule" par "(id,poid)"

--------------------------ARGUMENTS---------------------

cell   : pointe vers une cellule
id     : identifiant de la tuile de la cellule "*cell"
poid   : poid de la tuile "id"


--------------------------VALEURS-----------------------

Mise à jour de tous les "cell->rule" par "(id,poid)"

*/
void MiseAJ_Rule_Cellule(Cellule *cell, int id, int poid);
/*
-------------------------DESCRIPTION--------------------
Compte le nombre de cellule collapse

*/

bool Uncollapse(Grille *grille);

void Neutral_Intersection(Grille* grille, Patterns* patterns,int a, int b);

/*


-------------------------DESCRIPTION--------------------
Reconstitue une image à partie des identifiants de
tuiles de chaque cellule

*/




void ImprimeImage(Grille* grille, Patterns* patterns);



/*
-------------------------DESCRIPTION--------------------

Supprime les champs de la grille

*/

void Free_grille(Grille* grille);

/*
-------------------------DESCRIPTION--------------------
compte le nombre de cellule non collapse de la grille

*/
int NbreCelluleOnGrille(Grille* grille);
/*
-------------------------DESCRIPTION--------------------

compte le nombre de cellule non collapse de la grille
qui ont un  voision collapse

*/
int NbCelHaveVoisin(Grille *grille);
/*

-------------------------DESCRIPTION--------------------

teste si une cellule de coordonnées (a,b) de la grille
a un voisin collapse

*/
bool TestVoisinageOff(Grille *grille, int a, int b);

/*
-------------------------DESCRIPTION--------------------

Propage les contraintes dans la grille.

--------------------------VALEURS-----------------------

*ER  :-1, si une intersection est vide
     :0, sinon
*/

void PropagationContrainte_Locale(Grille* grille, Patterns* patterns,int* ER);
/*
-------------------------DESCRIPTION--------------------

Propage l'entropie dans la grille.
*/
void PropagationEntropie_Locale(Grille* grille);

/*
-------------------------DESCRIPTION--------------------

Chercher la cellule ayant l'entropie la plus faible

*/
void Collapse_Local(Grille *grille, int *alea_t, int *alea_g1, int *alea_g2,int *position,int *EM);

/*
-------------------------DESCRIPTION--------------------

Determine parmi le nombre "ON" de cellules si  la cellule
de coordonnée (a,b) dans  la grille a l'entropie la plus faible

*/
bool FindPositionEntropieMin_Local(Grille* grille,int a,int b,int ON);


/*
-------------------------DESCRIPTION--------------------

Astreint le point (a,b) à rester dans la grille

*/
bool In_grille(Grille *grille, int a, int b);
//void Desactive(Grille *grille);

#endif // GRILLE_H_INCLUDED
