# Algorithme-Wave-Function-Collapse

## Génération procédurale : Algorithme Wave Function Collapse(WFC)

***

L'algorithme WFC (Wave Function Collapse) est une méthode utilisée pour générer des structures à partir d'un ensemble de contraintes locales. Il est souvent utilisé dans le domaine de la génération procédurale, notamment pour la création de niveaux de jeux, de textures ou d'autres formes de contenu.


## Table de matières
1. [Informations générales]
2. [Compilation]
3. [Exécution]

***

## Informations générales

L'algorithme se décompose en plusieurs étapes :

1. Création des tuiles ("tiles") de l'image d'entrée de taille définie par l'utilisateur. 
   Il est important  de noter que la structure Patterns(avec le ´s´ à la fin) est en fait la 
   collection des tiles, `tileset´.

2. Mise-à-jour des contraintes d'adjacences.

3. Création de la grille pour la propagation qui contient des cellules dont chaque cellule à l'initialisation
   est dans un état de superposition de toutes les possibilités de tiles possible.

4. Effondrement (collapse), calculs d'entropie et propagation des contraintes.

Pour cela, nous avons implémenté des fichiers (en-tête et source) contenants des fonctions dont nous avons besoin pour chaque étape de l'algorithme

A. `Grille.h` et Grille.c`
Le fichier en-tête contient les structures `Grille` et `Cellule` ainsi que les prototypes des fonctions qui vont nous servir à manipuler la grille (collapse, propagation des contraintes, entropie minimale, impression de l'image...) et  et les cellules (création des cellules, mise-à-jour locales…).

B. `Patterns.h` et `Patterns.c`
Le fichier en-tête contient la structure `Patterns` qui est la collection des tiles avec les informations (poids, dimensions des tiles, et dimension de l'ensemble des tiles).
Le fichier source contient des fonctions (dont les prototypes sont dans le fichier en-tête) qui servent à la manipulation sur les tiles (sauvegarde, affichage, contraintes sur les tiles ...) 

C. `Utils_wfc.h` et `Utils_wfc.c`
Le fichier en-tête contient la structure `Tile` qui est les blocs de taille définie par l'utilisateur prise sur l'image d'entrée considéré comme un tore et la structure `Rule` qui contient les identifiants et les poids des tiles classifiées, c'est-à-dire les tiles sans doublons pour faciliter les utilisations comme la propagation, effondrement et l'étude statistique sur les tiles, calcul d'entropie.
Le fichier source contient des fonctions sur la manipulation de ses tiles (affichage, sauvegarde, calcul d'entropie, copie de tiles, comparaison...).
  

## Compilation

À cet effet, un Makefile a été créer pour faciliter la compilation du fichier ´main.c´ qui contient plusieurs en-têtes, notamment des en-têtes que nous avons nous-mêmes implémenté.
Pour la compilation :

1. Ouvrir le terminal : PowerShell, cmd, terminal intégré de l'éditeur comme celui de VS Code ou VSCodium.

2. Placez-vous dans le dossier `WFC` qui contient le fichier `main.c` et lancez la commande `make`.


## Exécution

1. Exécuter la commande `.\main.exe`.

2. Suivez les instructions de l'interface.

3. À la fin, l'image est dans le dossier WFC sous le nom 'wfc.png'.

lorsque l'image n'est pas terminée, elle contient en son sein trois zone distinctes:

Zone 1: Une partie de l'image constituée des cellules qui ont pu être collapsées et contenant les motifs de l'image d'entrée.

Zone 2: Une partie de l'image constituée des cellules non collapsées (ayant une couleur uniforme bleue)

Zone 3: Une bande séparant la Zone 1 et 2  de couleur verte indiquant qu'on a rencontré un obstacle dans la propagation des contraintes.

4.  Pour voir la première fois où on a rencontré un problème de propagation on peut modifier le
    code dans le programme que nous reprenons ci-dessous en décommentant la ligne 3 et en commentant la ligne 6:

    --------------------------------WFC-----------------------------------------------
    while(Uncollapse(&grille)){
    PropagationContrainte_Locale(&grille,&patterns,&ER);
    //if(ER==-1){break;} <----- la ligne 3
    PropagationEntropie_Locale(&grille);
    Collapse_Local(&grille,&alea_t,&alea_g1,&alea_g2,&position,&EM);
    if(EM==-2){break;} <----- la ligne 6
    }
    -----------------------------------------------------------------------------------

   Mais avant de faire cela, il faut d'abord décommenter toutes les lignes de la fonctions
   "void PropagationContrainte_Locale(Grille* grille, Patterns* patterns,int *ER)" qui se 
   trouve dans le fichier Grille.c.
   
5. Pour que l'image soit complètement générée quel que soit les problèmes de propagation 
   il faut d'abord décommenter la ligne 1 des instructions suivantes que l'on retrouve dans 
   la fonction  'void Neutral_Intersection(Grille* grille, Patterns* patterns,int a, int b)'
   du fichier Grille.c.

    -----------------------------------------------------------------------------------
    //ind=0; <----- la ligne 1
    if(ind==0){
    if(!grille->cellules[position[0]].etat && grille->cellules[position[0]].id!=-1 && in[0])
    {
        id=grille->cellules[position[0]].id;
        IntersectionRule(grille->cellules[Cu_Id].rule,(patterns->tile+id)->rule_down,&copie);
        Copy_rule(&copie,&grille->cellules[Cu_Id].rule);
        Free_Rule(&copie);
    }
   -----------------------------------------------------------------------------------

 6. le fichier 'Graines.txt' permet de retrouver la graine de chaque image. Si on veut générer  
    la même image il suffit de changer la graine de la fonction 'int nombrePseudoAleatoire(int a)'  
    (dans le fichier Utils_Wfc_h) par celle copiée dans le fichier 'Graines.txt'.


## Merci d'avoir utilisé notre programme.