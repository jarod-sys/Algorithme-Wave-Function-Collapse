#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "utils.h"
#include "Utils_wfc.h"

#include "Color.h"
#include "Image.h"
#include "ColorImage.h"

#include "Patterns.h"
#include "Grille.h"
#define T 100

//.............................................DEBUT PROGRAMME.................................................


int main(int argc, char *argv[])
{
    //-------------------------------VARIABLES--------------------------------------------

    Image img;
    ColorImage cimg;
    char chaine[T]="";


    int taille_Img_h,taille_Img_w,EM,ER;
    taille_Img_h=0;
    taille_Img_w=0;


    int h_gril,w_gril;
    int alea_t,alea_g1,alea_g2,position;
    alea_t=0;
    alea_g1=0;
    alea_g2=0;
    position=0;

    Grille grille;
    grille.cellules=NULL;

    Patterns patterns;
    patterns.tile=NULL;

    Rule TileclassActive;
    TileclassActive.rule=NULL;
    TileclassActive.poids=NULL;
    TileclassActive.length=0;

    //-------------------------------------------------------------------------------------------

    //----------------------------------IMAGE D'ENTREE-------------------------------------------


    Image_load(&img,"images//Disk.png");
    ON_ERROR_EXIT(img.data == NULL, "Error in loading the image");
    // Convertion de l'image en matrice de pixels.
    Image_to_ColorImage(&img, &cimg);

    //------------------------------------------------------------------------------------------


    //-----------------------------CREATION DES PATTERNS----------------------------------------

    do
    {
        printf("\nEntrez la taille du motif...\n");
        printf("Celle-ci doit etre plus petit que %d et %d:\n",cimg.height,cimg.width);
        printf("Largeur:");
        if(Lire(chaine,T)){
        sscanf(chaine, "%d",&patterns.size_tile_h);
        }else{ON_ERROR_EXIT(1,"Erreur de lecture");}
        printf("Longueur:");
        if(Lire(chaine,T)){
        sscanf(chaine, "%d",&patterns.size_tile_w);
        }else{ON_ERROR_EXIT(1,"Erreur de lecture");}
    }while((cimg.height<=patterns.size_tile_h) ||(patterns.size_tile_w<=0) || (patterns.size_tile_h<=0)  || (cimg.width<=patterns.size_tile_w));

    //Creation des motifs d'image.
    Init_patterns(&patterns,cimg.height,cimg.width);
    InitColorPatterns(&patterns,&cimg);


    //Calcule des poids et mise à jour des conatraintes.
    PoidsTile(&patterns);
    ContraintesTile(&patterns);
    Mise_AJC_voisin(&patterns);

    //Extraction des motifs classifiés.
    Counter_class(&patterns,&TileclassActive);
    //Sauvegarde_P(&patterns);
    printf("Les [%d] motifs  ont ete bien enregistres.\nTaille matrice_P:[%d,%d]", TileclassActive.length,patterns.height_p,patterns.width_p);
    //--------------------------------------------------------------------------------------------

    //---------------------------CREATION DE LA GRILLE--------------------------------------------

    while((2*patterns.size_tile_h>=taille_Img_h))
    {

        printf("\nEntrez la largeur de l'image de sortie...\n");
        printf("Celle-ci doit etre plus grande que %d :\n",2*patterns.size_tile_h);
        if(Lire(chaine,T)){
        sscanf(chaine, "%d",&taille_Img_h);
        }else{ON_ERROR_EXIT(1,"");}
    }

    while((2*patterns.size_tile_w>=taille_Img_w))
    {
        printf("\nEntrez  la longueur de l'image de sortie...\n");
        printf("Celle-ci doit etre plus grande que %d :\n",2*patterns.size_tile_w);
        if(Lire(chaine,T)){
        sscanf(chaine, "%d",&taille_Img_w);
        }else{ON_ERROR_EXIT(1,"");}
    }

    h_gril= (int) taille_Img_h/patterns.size_tile_h;
    w_gril= (int) taille_Img_w/patterns.size_tile_w;


    //Initialisation de la grille avec le motif de plus grande-proba.
    Init_grille(&grille,&TileclassActive,h_gril,w_gril);


    printf("---------------TUILE INITIALISEE--------------------\n");
    InitialiseGrille(&grille,&alea_t,&alea_g1,&alea_g2,&position);
    printf("-------------------EN-ATTENTE-----------------------\n");


    //--------------------------------WFC----------------------------------------------------
    while(Uncollapse(&grille)){
    PropagationContrainte_Locale(&grille,&patterns,&ER);
    //if(ER==-1){break;}
    PropagationEntropie_Locale(&grille);
    Collapse_Local(&grille,&alea_t,&alea_g1,&alea_g2,&position,&EM);
    if(EM==-2){break;}
    }
    printf("-----------------------FIN---------------------------\n");

    //--------------------------------IMAGE DE SORTIE---------------------------------------

    ImprimeImage(&grille,&patterns);

    //----------------------------------------------------------------------------------------

    Image_free(&img);
    ColorImage_free(&cimg);
    Free_grille(&grille);
    Free_Patterns(&patterns);

    //-----------------------------------------------------------------------------------------
    return 0;
    }


