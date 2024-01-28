#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Patterns.h"
#include "utils.h"
#include "Utils_wfc.h"
#include "Image.h"
#include"ColorImage.h"

#define S 1


void ViderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int Lire(char *chaine, int longueur)
{
char *positionEntree = NULL;
if (fgets(chaine, longueur, stdin) != NULL)
{
positionEntree = strchr(chaine, '\n');
if (positionEntree != NULL) {*positionEntree = '\0';}
return 1;
}
else{return 0;}
}


void InitColorPatterns(Patterns *patterns, ColorImage *cimg)
{
    int i,j,id;

    Color colordefault;
    Color_set(&colordefault,10,45,5,255);

    for(i=0; i<patterns->height_p;  i++)
    {
       for(j=0; j<patterns->width_p;  j++)
       {
           id=i*patterns->width_p+j;
           Color_Tile(patterns->tile+id,cimg,&colordefault,i,j);
       }
    }

}

void Init_patterns(Patterns *patterns, int height,int width)
{
    int i,j,id;
    if(patterns->tile==NULL)
    {
    patterns->height_p = (int) height;
    patterns->width_p  = (int) width;
    patterns->tile= (Tile*) calloc(patterns->height_p*patterns->width_p,sizeof(Tile));
    }else{ON_ERROR_EXIT(patterns->tile!=NULL,"");}

    if(patterns->tile!=NULL)
    {
        for(i=0; i<patterns->height_p;  i++)
        {
             for(j=0; j<patterns->width_p;  j++)
            {
                id=i*patterns->width_p+j;
                New_Tile(patterns->tile+id,patterns->size_tile_h,patterns->size_tile_w,id);
            }
        }
    }
    else{ON_ERROR_EXIT(patterns->tile==NULL,"Pattern is not created\n");}

}

void New_Tile(Tile *t, int size_tile_h,int size_tile_w, int id_tile)
{

    t->tile_color.data=NULL;
    ColorImage_create(&(t->tile_color),size_tile_w,size_tile_h);

    t->rule_up.rule=NULL;
    t->rule_down.rule=NULL;
    t->rule_left.rule=NULL;
    t->rule_right.rule=NULL;

    t->rule_up.poids=NULL;
    t->rule_down.poids=NULL;
    t->rule_left.poids=NULL;
    t->rule_right.poids=NULL;

    t->rule_UL.rule=NULL;
    t->rule_UR.rule=NULL;
    t->rule_DR.rule=NULL;
    t->rule_DL.rule=NULL;

    t->rule_UL.poids=NULL;
    t->rule_UR.poids=NULL;
    t->rule_DR.poids=NULL;
    t->rule_DL.poids=NULL;

    New_Rule(&(t->rule_up));
    New_Rule(&(t->rule_right));
    New_Rule(&(t->rule_down));
    New_Rule(&(t->rule_left));
    New_Rule(&(t->rule_UR));
    New_Rule(&(t->rule_UL));
    New_Rule(&(t->rule_DL));
    New_Rule(&(t->rule_DR));

    t->classe=true;
    t->id=id_tile;
    t->poid=1;

}


void Color_Tile(Tile *tile,ColorImage *cimg, Color *colordefault,int height, int width)
{
    int i,j;
    Color color;

    for(i=height; i< height+tile->tile_color.height;  i++)
    {
        for(j=width; j<width+tile->tile_color.width;  j++)
         {
            get_color_at(&color,cimg,ajust(i,cimg->height),ajust(j,cimg->width),colordefault);
            set_color_at(&color,&tile->tile_color,i-height,j-width);
         }
    }
}

void Sauvegarde_P(Patterns *patterns)
{
    int i,j,id;
    Image img_blurred;
    char *name=NULL;
    for(i=0; i<patterns->height_p;  i++)
    {
       for(j=0; j<patterns->width_p;  j++)
       {
        id=i*patterns->width_p+j;
        if(patterns->tile[id].classe)
        {
        ColorImage_to_Image(&img_blurred,&(patterns->tile[id].tile_color));
        name=malloc(120*sizeof(char));
        if(name!=NULL){
        update_name(name,id);
        Image_save(&img_blurred, name);
        Image_free(&img_blurred);
        Name_free(name);
        }else{ON_ERROR_EXIT(1,"Impossible de creer le nom du tile");}
        }else{continue;}
        }
    }
}

void PoidsTile(Patterns* patterns)
{
    int i,j,taille;
    bool bl;
    taille=patterns->height_p*patterns->width_p;

    for(i=0; i<taille-1;i++)
    {
        for(j=i+1; j<taille;j++)
        {
            bl=CompareTile(patterns->tile+i,patterns->tile+j,patterns->size_tile_h,patterns->size_tile_w);
            if(bl)
            {
                patterns->tile[i].poid++;
                patterns->tile[j].poid++;
            }
            else{continue;}
        }

    }
}

bool CompareTile(Tile *tile1,Tile *tile2,int size_tile_h,int size_tile_w)
{
    int i,j;
    bool bl;
    int cmpt=0;
    for(i=0; i<size_tile_h;i++)
    {
        for(j=0; j<size_tile_w;j++)
        {
            bl=Same_color(tile1->tile_color.data+i*size_tile_w+j,tile2->tile_color.data+i*size_tile_w+j);
            if(bl){cmpt++;}
            else{continue;}
        }
    }
    if(cmpt==size_tile_h*size_tile_w){return true;}
    else{return false;}
    cmpt=0;
}

bool Same_color(Color *color1, Color *color2)
{
    bool booleen=(abs(color1->red-color2->red)<S)&& (abs(color1->green-color2->green)<S) && (abs(color1->blue-color2->blue)<S)&& (abs(color1->alpha-color2->alpha)<S);
    if(booleen)
    {
        return true;
    }else{return false;}
}


void Affiche_AllRule_Pat(Patterns *patterns)
{
    int i,j;
    for(i=0; i<patterns->height_p; i++)
    {

        for(j=0; j<patterns->width_p;j++)
        {
            if(patterns->tile[i*patterns->width_p+j].classe)
            {
                printf("-------------Patterns [%d]------------\n",i*patterns->width_p+j);
               Affiche_TileRule_t(patterns->tile+i*patterns->width_p+j);
            }
        }

    }
}

void Affiche_AllTile(Patterns *patterns)
{
    int i,j;
    for(i=0; i<patterns->height_p; i++)
    {

        for(j=0; j<patterns->width_p;j++)
        {
            if(patterns->tile[i*patterns->width_p+j].classe)
            {
               AfficheTile(patterns->tile+i*patterns->width_p+j);
            }
        }

    }
}


void Active(Tile *tile,bool a)
    {
        if(a){tile->classe=true;}
        else{tile->classe=false;}
    }

void Mise_AJC_voisin(Patterns* patterns)
{
    int i,j;
    bool bl;
    int taille_tile_h,taille_tile_w,taille;
    taille_tile_h=patterns->size_tile_h;
    taille_tile_w=patterns->size_tile_w;
    taille=patterns->height_p*patterns->width_p;
    if(patterns->tile!=NULL){
    for(i=0; i<taille-1;i++)
    {
        for(j=i+1; j<taille;j++)
        {
            bl=CompareTile(patterns->tile+i,patterns->tile+j,taille_tile_h,taille_tile_w);
            if(bl && (patterns->tile+i)->classe)
            {
                Active(patterns->tile+j,false);
                Append_rule(&((patterns->tile+i)->rule_up),&( (patterns->tile+j)->rule_up) );
                Append_rule(&((patterns->tile+i)->rule_right),&( (patterns->tile+j)->rule_right) );
                Append_rule(&((patterns->tile+i)->rule_down),&( (patterns->tile+j)->rule_down) );
                Append_rule(&((patterns->tile+i)->rule_left),&( (patterns->tile+j)->rule_left) );
                Append_rule(&((patterns->tile+i)->rule_UL),&( (patterns->tile+j)->rule_UL) );
                Append_rule(&((patterns->tile+i)->rule_UR),&( (patterns->tile+j)->rule_UR) );
                Append_rule(&((patterns->tile+i)->rule_DR),&( (patterns->tile+j)->rule_DR) );
                Append_rule(&((patterns->tile+i)->rule_DL),&( (patterns->tile+j)->rule_DL) );
            }

        }
        }
    } else{ON_ERROR_EXIT(patterns->tile==NULL,"");}
}


void ContraintesTile(Patterns* patterns)
{
    int i,j;

    for(i=0; i<patterns->height_p; i++)
    {
        for(j=0; j<patterns->width_p; j++)
        {
            VoisinTile(patterns,i,j,0);
            VoisinTile(patterns,i,j,1);
            VoisinTile(patterns,i,j,2);
            VoisinTile(patterns,i,j,3);
            VoisinTile(patterns,i,j,4);
            VoisinTile(patterns,i,j,5);
            VoisinTile(patterns,i,j,6);
            VoisinTile(patterns,i,j,7);
        }
    }

}

void VoisinTile(Patterns*patterns, int a, int b,int direction)
{
    bool bl;
    int taille,taille_tile_h,taille_tile_w,h,w,id_pattern,i,in;
    int position[8];
    h=(*patterns).height_p;
    w=(*patterns).width_p;
    taille_tile_h=(*patterns).size_tile_h;
    taille_tile_w=(*patterns).size_tile_w;
    taille=(*patterns).height_p*(*patterns).width_p;

    id_pattern=ajust(a,h)*w+ajust(b,w);
    position[0]=ajust(a-taille_tile_h,h)*w+ajust(b,w);
    position[1]=ajust(a,h)*w+ajust(b+taille_tile_w,w);
    position[2]=ajust(a+taille_tile_h,h)*w+ajust(b,w);
    position[3]=ajust(a,h)*w+ajust(b-taille_tile_w,w);
    position[4]=ajust(a-taille_tile_h,h)*w+ajust(b-taille_tile_w,w);
    position[5]=ajust(a-taille_tile_h,h)*w+ajust(b+taille_tile_w,w);
    position[6]=ajust(a+taille_tile_h,h)*w+ajust(b+taille_tile_w,w);
    position[7]=ajust(a+taille_tile_h,h)*w+ajust(b-taille_tile_w,w);



    switch(direction)
    {
    case 0:

        for (i=0; i<taille;i++)
        {
            if(1){
            bl=CompareTile(patterns->tile+position[0],patterns->tile+i,taille_tile_h,taille_tile_w);
            if(bl){
                in=i;
                break;}
        }}
        Rule_append(&(patterns->tile+id_pattern)->rule_up,(patterns->tile+in)->id,(patterns->tile+in)->poid);

    break;

    case 1:
        for (i=0; i<taille;i++)
        {
            if(1){
            bl=CompareTile(patterns->tile+position[1],patterns->tile+i,taille_tile_h,taille_tile_w);
            if(bl){
                in=i;
                break;}
        }}

        Rule_append(&(patterns->tile+id_pattern)->rule_right,(patterns->tile+in)->id,(patterns->tile+in)->poid);
    break;




    case 2:
        for (i=0; i<taille;i++)
        {
            if(1){
            bl=CompareTile(patterns->tile+position[2],patterns->tile+i,taille_tile_h,taille_tile_w);
            if(bl){
                in=i;
                break;}
        }}

        Rule_append(&(patterns->tile+id_pattern)->rule_down,(patterns->tile+in)->id,(patterns->tile+in)->poid);
    break;


    case 3:
        for (i=0; i<taille;i++)
        {
            if(1){
            bl=CompareTile(patterns->tile+position[3],patterns->tile+i,taille_tile_h,taille_tile_w);
            if(bl){
                in=i;
                break;}
        }}

        Rule_append(&(patterns->tile+id_pattern)->rule_left,(patterns->tile+in)->id,(patterns->tile+in)->poid);
    break;
    case 4:

    for (i=0; i<taille;i++)
        {
            if(1){
            bl=CompareTile(patterns->tile+position[4],patterns->tile+i,taille_tile_h,taille_tile_w);
            if(bl){
                in=i;
                break;}
        }}

        Rule_append(&(patterns->tile+id_pattern)->rule_UL,(patterns->tile+in)->id,(patterns->tile+in)->poid);
    break;

    case 5:
        for (i=0; i<taille;i++)
        {
        if(1){
        bl=CompareTile(patterns->tile+position[5],patterns->tile+i,taille_tile_h,taille_tile_w);
        if(bl){
            in=i;
            break;}
        }}

        Rule_append(&(patterns->tile+id_pattern)->rule_UR,(patterns->tile+in)->id,(patterns->tile+in)->poid);

    break;

        case 6:
        for (i=0; i<taille;i++)
        {
            if(1){
            bl=CompareTile(patterns->tile+position[6],patterns->tile+i,taille_tile_h,taille_tile_w);
            if(bl){
                in=i;
                break;}
        }}

        Rule_append(&(patterns->tile+id_pattern)->rule_DR,(patterns->tile+in)->id,(patterns->tile+in)->poid);

    break;

        case 7:

        for (i=0; i<taille;i++)
        {
            if(1){
            bl=CompareTile(patterns->tile+position[7],patterns->tile+i,taille_tile_h,taille_tile_w);
            if(bl){
                in=i;
                break;}
        }}

        Rule_append(&(patterns->tile+id_pattern)->rule_DL,(patterns->tile+in)->id,(patterns->tile+in)->poid);


    break;

    default:
        ON_ERROR_EXIT(direction>3,"Error on direction");
        break;
    }

}


void Counter_class(Patterns* patterns,Rule *TileclassActive)
{

    int i,compteur,taille;
    taille=patterns->height_p*patterns->width_p;
    compteur=0;

    for(i=0; i<taille; i++)
    {
        if((patterns->tile+i)->classe)
        {
            compteur++;
        }else{continue;}
    }
    if(TileclassActive->poids==NULL && TileclassActive->rule==NULL){
    TileclassActive->poids=malloc(compteur*sizeof(int));
    TileclassActive->rule=malloc(compteur*sizeof(int));}
    else{ON_ERROR_EXIT(1,"");}

    if(TileclassActive->rule!=NULL &&TileclassActive->poids!=NULL)
    {
        TileclassActive->length=compteur;
        compteur=0;
        for(i=0; i<taille; i++)
        {
            if((patterns->tile+i)->classe)
            {
                TileclassActive->rule[compteur]=patterns->tile[i].id;
                TileclassActive->poids[compteur]=patterns->tile[i].poid;
                compteur++;
            }else{continue;}
        }
    }else{ON_ERROR_EXIT(TileclassActive->rule==NULL || TileclassActive->poids==NULL,"");}
}


void Free_Patterns(Patterns *pattern)
{
    int i;
    for(i=0; i<pattern->width_p*pattern->height_p;  i++)
    {
        Tile_free(pattern->tile+i);
    }
    free(pattern->tile);
    pattern->tile=NULL;

}


void Tile_free(Tile *t)
{
    ColorImage_free(&t->tile_color);

    free(t->rule_up.poids);
    free(t->rule_down.poids);
    free(t->rule_right.poids);
    free(t->rule_left.poids);

    free(t->rule_up.rule);
    free(t->rule_down.rule);
    free(t->rule_right.rule);
    free(t->rule_left.rule);

    free(t->rule_UL.poids);
    free(t->rule_UR.poids);
    free(t->rule_DR.poids);
    free(t->rule_DL.poids);

    free(t->rule_UL.rule);
    free(t->rule_UR.rule);
    free(t->rule_DR.rule);
    free(t->rule_DL.rule);


    t->rule_up.rule=NULL;
    t->rule_down.rule=NULL;
    t->rule_left.rule=NULL;
    t->rule_right.rule=NULL;

    t->rule_up.poids=NULL;
    t->rule_down.poids=NULL;
    t->rule_left.poids=NULL;
    t->rule_right.poids=NULL;

    t->rule_UL.rule=NULL;
    t->rule_UR.rule=NULL;
    t->rule_DR.rule=NULL;
    t->rule_DL.rule=NULL;

    t->rule_UL.poids=NULL;
    t->rule_UR.poids=NULL;
    t->rule_DR.poids=NULL;
    t->rule_DL.poids=NULL;

}
