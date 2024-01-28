#ifndef UTILS_WFC_H_INCLUDED
#define UTILS_WFC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "ColorImage.h"
#include "Color.h"





/*
-------------------------DESCRIPTION---------------------

Structure qui representela liste des ID des tuiles et de leurs poids.

--------------------------VALEURS------------------------

int length  : Longueur de la liste
int *rule   : Liste des ID
int *poids  : Liste des poids

*/

typedef struct {
    int length;
    int *rule;
    int *poids;
}Rule;


/*
-------------------------DESCRIPTION---------------------

 Structure qui represente une tuile d'image.

--------------------------VALEURS------------------------
int id                    : identifiant de la tuile
int poid                  : Nombre d'occurrence de la tuile
bool classe               : True, si la tuile est le representant des autres semblables, False sinon
ColorImage tile_color     : Couleur de la tuile
Rule rule_up,...,rule_DL  : Comtraintes adjacentes

*/

typedef struct {
    int id;
    int poid;
    bool classe;
    ColorImage tile_color;
    Rule rule_up,rule_down,rule_right,rule_left ,rule_UR, rule_UL, rule_DR,rule_DL;
}Tile;

//----------------------------------------------------------------------------------------

/*
-------------------------DESCRIPTION---------------------
Affiche les contrainte adjacentes de la tuile "*tile"

*/
void Affiche_TileRule_t(Tile *tile);
/*
-------------------------DESCRIPTION---------------------

Affiche  l'id et le poid d'une tuile

*/

void AfficheTile(Tile *tile);
/*
-------------------------DESCRIPTION---------------------

Affiche les contrainte adjacentes de la tuile "*pattern"
dans la direction "j".


--------------------------ARGUMENTS------------------------

j : 0 Haut
    1 droite
    2 bas
    3 gauche
    4 haut-gauche
    5 haut-droite
    6 bas-droite
    7 bas-gauche

*/
void Affiche_Tile_d(Tile *pattern, int j);
/*
-------------------------DESCRIPTION---------------------

Renvoie le reste modulo "a" de "i"

*/
int ajust(int i,int a);
/*
-------------------------DESCRIPTION---------------------

Supprimer les caractères d'une chaine

--------------------------ARGUMENTS------------------------

name   : pointe vers le nom à supprimer
--------------------------VALEURS------------------------

name   : contient le pointeur "NULL"

*/
void Name_free(char *name);
/*
-------------------------DESCRIPTION---------------------

Copie une structure Rule dans une autre

--------------------------ARGUMENTS------------------------

from   : pointe vers la structure à copier
to     : pointe vers srtructure vide

--------------------------VALEURS------------------------

from   : Inchangé
to     : Contient les éléments de *from


*/
void Copy_rule(Rule*from,Rule*to);

/*
-------------------------DESCRIPTION---------------------
Supprimer les éléments d'une liste

*/
void Free_Rule(Rule *rules);
/*
-------------------------DESCRIPTION--------------------

Ajoute dans une chaine de caratére un nombe

--------------------------ARGUMENTS---------------------
name  : Pointe vers le nom à mettre à jour
id    : Nombre à insérer dans "name"

--------------------------VALEURS------------------------
Les derniers éléments de rule->rule et rule->poid sont id
et poid

*/
void update_name(char*name,int id);
/*
-------------------------DESCRIPTION--------------------

 Ajoute en fin de  liste les éléments id et le poid.

--------------------------ARGUMENTS---------------------
id    : Indentifiant de tuile
poid  : poid de tuile
rule  : Pointe vers une liste d'ID et de poids

--------------------------VALEURS------------------------
Les derniers éléments de rule->rule et rule->poid sont id
et poid

*/


void Rule_append(Rule *rule, int id, int poid);


/*
-------------------------DESCRIPTION--------------------

Concaténation: Ajoute à la suite de rule1, la liste rule2.

--------------------------ARGUMENTS---------------------
 rule1   : Liste1 d'ID
 rule2  : Liste2 d'ID

--------------------------VALEURS-----------------------
 rule1 contient la liste (rule1,rule2)

*/
void Append_rule(Rule *rule1, Rule *rule2);
/*
-------------------------DESCRIPTION--------------------

Initialise la liste rule

--------------------------ARGUMENTS----------------------
 rule    : Liste d'ID

---------------------------VALEURS-----------------------
rule.length :  1
rule.rule   : -1
rule.rule   :  0

*/
void New_Rule(Rule *rule);
/*
-------------------------DESCRIPTION---------------------

Recherche dans rule l'identifiant "id"

--------------------------ARGUMENTS----------------------
 id                    : identifiant à chercher dans rule
 rule                  : Liste d'ID

 --------------------------VALEURS-----------------------
True  : si id est dans rule
False : sinon

*/
bool RechercheElement(Rule rule, int id);


/*
-------------------------DESCRIPTION---------------------
Affiche les Id et leurs poids de la liste "*rule".

*/
void Affiche_Rule(Rule *rule);


/*
-------------------------DESCRIPTION---------------------

Retourne l'ID qui à le plus grand poid.


--------------------------ARGUMENTS----------------------

rule  : Pointeur vers la liste des ID et leurs poids

--------------------------VALEURS------------------------

Retourne le  plus grand poid.

*/
int P_IdMasseHopRule(Rule*rule);

/*
-------------------------DESCRIPTION---------------------

Retourne un nombre aléatoire entier entre 0 et un seuil fixé


--------------------------ARGUMENTS----------------------

 a   : seuil

--------------------------VALEURS------------------------

Retourne un nombre aléatoire entier entre 0 et a.

*/
int nombrePseudoAleatoire(int a);
unsigned int xorshift(unsigned int x,unsigned int a1,unsigned int a2,unsigned int a3);

/*
-------------------------DESCRIPTION---------------------

Fais l'intersection entre deux ensembles d'ID de tuiles:
considère le nombre d'ID en commun.


--------------------------ARGUMENTS----------------------

 rule1   : Liste1 d'ID
 rule2   : Liste2 d'ID
 rule3   : Liste vide

--------------------------VALEURS------------------------

 rule1   : Inchangée
 rule2   : Inchangée
 rule3   : Contient les ID en commun.

*/
void IntersectionRule(Rule rule1,Rule rule2, Rule*rule3);


/*
-------------------------DESCRIPTION---------------------

Remplir à partir du point (a,b) de l'image "cimg" les
pixels provenent de "t->tile_Color"

--------------------------ARGUMENTS----------------------

 cimg        : Pointeur vers une couleur d'image divisée
               en carré eventuellement en rectangle

 t           : Pointeur vers un Tuile

 (a,b)       : Coordonnées (Haut-gauche) d'un  sous bloc d'image de "*cimg"

 colordefault: Couleur par defaut

 --------------------------VALEURS------------------------

sous bloc d'image de "*cimg"  mis à jour.
*/
void Color_sortie(ColorImage *cimg,Tile *t,Color *colordefault, int a, int b);
/*
-------------------------DESCRIPTION---------------------

Remplir à partir du point (a,b) de l'image "cimg" le carré de
(eventuellement le rectangle) pixels par ceux de "colordefault"

--------------------------ARGUMENTS----------------------

 cimg        : Pointeur vers une couleur d'image divisée
               en carré de taille "size_tile"

 size_tile_h,
 size_tile_w : dimension de chaque sous bloc d'image de "*cimg"

 (a,b)       : Coordonnées d'un  sous bloc d'image de "*cimg"

 colordefault: Couleur à placer à la position (a,b) dans "*cimg"

 --------------------------VALEURS------------------------

sous bloc d'image de "*cimg" de taille "size_tile" mis à jour.


*/
void Color_sortie_pad(ColorImage *cimg, int size_tile_h, int size_tile_w, int a, int b,Color *colordefault);
/*
-------------------------DESCRIPTION---------------------

 Calcul l'entropie d'une liste de Tuile.

--------------------------ARGUMENTS----------------------

 rule  : Pointeur vers une liste de tuiles

 --------------------------VALEURS------------------------

 Retourne l'entropie de la liste

*/
float Entropy(Rule *rule);
/*
-------------------------DESCRIPTION---------------------

 Fonction logarithme en base 2.

--------------------------ARGUMENTS----------------------
 n  : Un réel
 --------------------------VALEURS------------------------

 Retourne le logarithme en base 2 de n


*/
float Log2(float n);

/*
-------------------------DESCRIPTION---------------------

 Copie la structure Tile de *from à *to.

--------------------------ARGUMENTS----------------------
 from  : tuile à copier
 to    : tuile vide

 --------------------------VALEURS------------------------
 from  : Inchangée
 to    : Contient la tuile from


*/
void Copy_tile(Tile *from, Tile* to);

#endif // UTILS_WFC_H_INCLUDED
