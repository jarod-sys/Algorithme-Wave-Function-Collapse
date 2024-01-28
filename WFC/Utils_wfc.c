#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "Utils_wfc.h"
#include "utils.h"
#define A 21
#define B 35
#define C 4

void Copy_tile(Tile *from, Tile* to)
{
    int i,j;
    Color color;
    Color colordefault;
    Color_set(&colordefault,10,45,5,255);

    if(from!=NULL && to!=NULL)
    {
       for(i=0; i<from->tile_color.height;  i++)
        {
        for(j=0; j<from->tile_color.width;  j++)
         {
            get_color_at(&color,&from->tile_color,i,j,&colordefault);
            set_color_at(&color,&to->tile_color,i,j);
         }
        }
        Copy_rule(&from->rule_up, &to->rule_up);
        Copy_rule(&from->rule_right, &to->rule_right);
        Copy_rule(&from->rule_down,&to->rule_down);
        Copy_rule(&from->rule_left, &to->rule_left);
        Copy_rule(&from->rule_UL, &to->rule_UL);
        Copy_rule(&from->rule_UR, &to->rule_UR);
        Copy_rule(&from->rule_DR, &to->rule_DR);
        Copy_rule(&from->rule_DL, &to->rule_DL);
        to->poid=from->poid;
        to->id=from->id;
        if(from->classe){to->classe=true;}
        else{to->classe=false;}
    }
    else{ON_ERROR_EXIT(from==NULL || to==NULL," element a  copier vide\n");}
}

int ajust(int i,int a)
{
    int valeur;
    if(i<0)
    {
         valeur=(i+a)%a;
    }
    else if (a<=i)
    {
         valeur=i%a;
    }
    else
    {
        valeur=i;
    }
return valeur;
}

void update_name(char*name,int id)
{
    if(name!=NULL)
    {
        sprintf(name, "tile\\Tile%d.png", id);

    }else{ON_ERROR_EXIT(1,"Pas d'espace pour le nom du tile!");}

}
void Name_free(char *name)
{
    if(name!=NULL)
    {
         free(name);
         name=NULL;
    }
    else{printf("Espace deje vide");}
}

void Append_rule(Rule *rule1, Rule *rule2)
{
    int i;
    if(rule1!=NULL && rule2!=NULL ){
    for(i=0 ; i<rule2->length; i++)
    {

        Rule_append(rule1,rule2->rule[i],rule2->poids[i]);

    }}else{ON_ERROR_EXIT(rule1==NULL || rule2==NULL ,"");}
}

void Rule_append(Rule *rule, int id, int poid)
{
    int i;
    bool bl;
    Rule copie;
    copie.poids=NULL;
    copie.rule=NULL;
    bl=RechercheElement(*rule,id);
    if(!bl){
    if(rule->poids!=NULL && rule->rule!=NULL){
    if(rule->length==1 && rule->poids[0]==0 && rule->rule[0]==-1)
    {
        rule->poids[0]=poid;
        rule->rule[0]=id;
    }
    else
    {
     Copy_rule(rule,&copie);
     Free_Rule(rule);
     rule->rule=calloc(copie.length+1,sizeof(int));
     rule->poids=calloc(copie.length+1,sizeof(int));
    if(rule->poids!=NULL && rule->rule!=NULL)
    {
    rule->length=copie.length+1;
    for(i=0; i<rule->length-1;i++)
    {
        rule->poids[i]=copie.poids[i];
        rule->rule[i]=copie.rule[i];
    }
    rule->poids[rule->length-1]=poid;
    rule->rule[rule->length-1]=id;
    }else{ON_ERROR_EXIT(rule->poids==NULL || rule->rule==NULL,"Echec de la copie\n");}
    Free_Rule(&copie);
    }}else{ON_ERROR_EXIT(rule->poids==NULL || rule->rule==NULL,"Attention impossible d'ajouter\n");}
    }

}

bool RechercheElement(Rule rule, int id)
{
    int i, compteur=0;

    bool bl;
    if(rule.rule!=NULL){
    for(i=0; i<rule.length; i++)
    {
        bl=(rule.rule[i]==id);
        if(bl)
        {
            compteur++;
            break;
        }
        else{continue;}
    }
    if(compteur){bl=true;}
    else{bl=false;}
    }else{ON_ERROR_EXIT(rule.rule==NULL,"Echec Recherche");}

    return bl;
}


void Copy_rule(Rule*from,Rule*to)
{
        int i;
        if(from!=NULL && from->poids!=NULL && from->rule!=NULL)
        {
        if(to->poids!=NULL && to->rule!=NULL){Free_Rule(to);}
        to->rule=calloc(from->length,sizeof(int));
        to->poids=calloc(from->length,sizeof(int));
        if(to->rule!=NULL && to->poids!=NULL)
        {
        to->length=from->length;
        for(i=0; i<to->length; i++)
        {
            to->rule[i]=from->rule[i];
            to->poids[i]=from->poids[i];
        }
        }else{ON_ERROR_EXIT(to->rule==NULL || to->poids==NULL,"Copie echouee\n");}
        }else{ON_ERROR_EXIT(from==NULL || from->poids!=NULL || from->rule!=NULL," element a  copier vide\n");}
}

void Free_Rule(Rule *rules)
{
        if(rules->poids!=NULL && rules->rule!=NULL){
        free(rules->poids);
        free(rules->rule);
        rules->poids=NULL;
        rules->rule=NULL;}
}

void New_Rule(Rule *rule)
{
    if(rule!=NULL){
    if(rule->poids!=NULL && rule->rule!=NULL)
    {
        free(rule->poids);
        free(rule->rule);
    }
    rule->poids=calloc(1,sizeof(int));
    rule->rule=calloc(1,sizeof(int));
    if(rule->poids!=NULL && rule->rule!=NULL)
    {
        rule->length=1;
        rule->poids[0]=0;
        rule->rule[0]=-1;

    }else{ON_ERROR_EXIT(rule->poids==NULL || rule->rule==NULL,"");}
    }else{ON_ERROR_EXIT(rule==NULL ,"");}
}

void Affiche_Rule(Rule *rule)
{
    int i;
    for(i=0; i<rule->length; i++){
    printf("Tile: [%d], Poid:[%d]\n",rule->rule[i],rule->poids[i]);}
}

int P_IdMasseHopRule(Rule *rule)
{
    int i,j,indice,cmp=0;

    if(rule->poids!=NULL && rule->rule!=NULL){
    for(j=0; j<rule->length; j++)
    {

        for(i=0; i<rule->length; i++)
        {
            if(rule->poids[i]<=rule->poids[j]){cmp++;}
            else{continue;}
        }

        if(cmp==rule->length)
        {
            indice=j;
            break;
        }
        else
        {
        cmp=0;
        continue;
        }
    }
    }else{ON_ERROR_EXIT(rule->rule==NULL || rule->poids==NULL,"");}

    return indice;
}

int nombrePseudoAleatoire(int a)
{
    static int i=0;
    static int x[10000];
    if(i==0)
    {
        srand(time(NULL));
        x[i]=rand();
        FILE* fichier = NULL;
        fichier = fopen("Graines.txt", "w+");
        fprintf(fichier,"%u\n",x[i]);
        fclose(fichier);

    }
    x[i+1]=xorshift(x[i],A,B,C);
    i++;
    return abs(x[i]%a);

}

void IntersectionRule(Rule rule1,Rule rule2, Rule*rule3)
{
    int i,j,compteur=0;
    bool bl;
    //On compte le nombre d'element en commun
    if(rule1.rule!=NULL && rule2.rule!=NULL)
    {
        for(i=0; i<rule2.length; i++)
        {
            for(j=0; j<rule1.length; j++)
            {
                bl=(rule2.rule[i]==rule1.rule[j]);
                if(bl)
                {
                    compteur++;
                    break;
                }
                else{continue;}
            }
        }


    if(compteur!=0)
    {
        if(rule3->poids!=NULL && rule3->rule!=NULL){Free_Rule(rule3);}
        rule3->rule=calloc(compteur,sizeof(int));
        rule3->poids=calloc(compteur,sizeof(int));
        if((rule3->rule!=NULL) && (rule3->poids!=NULL))
        {
            rule3->length=compteur;
            compteur=0;
            for(i=0; i<rule2.length; i++)
            {
                for(j=0; j<rule1.length; j++)
                {
                    bl=(rule2.rule[i]==rule1.rule[j]);
                    if(bl)
                    {
                        rule3->rule[compteur]=rule2.rule[i];
                        rule3->poids[compteur]=rule2.poids[i];
                        compteur++;
                        break;

                    }
                    else{continue;}
                }
            }
        }else{ON_ERROR_EXIT((rule3->rule==NULL) || (rule3->poids==NULL),"Memoire non alloue\n");}

    }
    else // Aucun element en commun
    {
        if(rule3->poids!=NULL && rule3->rule!=NULL){Free_Rule(rule3);}
        rule3->rule=calloc(1,sizeof(int));
        rule3->poids=calloc(1,sizeof(int));
        if(rule3->rule!=NULL && rule3->poids!=NULL)
        {
        rule3->length=1;
        rule3->rule[0]=-1;
        rule3->poids[0]=0;

        }else{ON_ERROR_EXIT(rule3->rule==NULL || rule3->poids==NULL,"Espace intersection rule et poids non alloue\n");}
    }

    }else{ON_ERROR_EXIT(rule1.rule==NULL || rule2.rule==NULL,"Aucune regles etaient allouees!\n");}
}

void Color_sortie(ColorImage *cimg,Tile *t,Color *colordefault, int a, int b)
{
    int i,j;
    Color color;

    for(i=a*t->tile_color.height; i< (a+1)*t->tile_color.height;  i++)
    {
        for(j=b*t->tile_color.width; j<(b+1)*t->tile_color.width;  j++)
         {
             get_color_at(&color,&t->tile_color,i-a*t->tile_color.height,j-b*t->tile_color.width,colordefault);
             set_color_at(&color,cimg,i,j);
         }

    }
}

void Color_sortie_pad(ColorImage *cimg, int size_tile_h,int size_tile_w, int a, int b,Color *colordefault)
{
    int i,j;
    for(i=a*size_tile_h; i< (a+1)*size_tile_h;  i++)
    {
        for(j=b*size_tile_w; j<(b+1)*size_tile_w;  j++)
         {
             set_color_at(colordefault,cimg,i,j);

         }
    }
}


float Log2(float n)
{
    return ((float)log(n))/ ((float)log(2));
}

float Entropy(Rule *rule)
{
    int i;
    float tmp=0,sum=0;
    if(rule!=NULL){
    if(rule->rule!=NULL && rule->poids!=NULL)
    {
        for(i=0; i<rule->length;  i++)
        {
            ON_ERROR_EXIT(rule->poids[i]==0, "Error on weight");
            sum=sum+rule->poids[i];
        }
        for(i=0; i<rule->length;  i++)
        {
           tmp=tmp-(rule->poids[i]/sum)*Log2(rule->poids[i]/sum);
        }

    }
    else
    {
        ON_ERROR_EXIT(rule->rule==NULL || rule->poids==NULL,"Erreur dans le calcul de l'entropie: rule et poids null");
    }
    }else{ON_ERROR_EXIT(rule==NULL,"Erreur dans le calcul de l'entropie...");}

    return tmp;
}

void Affiche_TileRule_t(Tile *tile)
{
    int j=0;
    if(tile!=NULL){
    for(j=0; j<4; j++)
    {
      Affiche_Tile_d(tile,j);
    }}else{ON_ERROR_EXIT(1,"");}
}

void AfficheTile(Tile *tile)
{

 printf("Tile: [%d], Poid:[%d]\n",tile->id,tile->poid);

}

void Affiche_Tile_d(Tile *pattern, int j)
{
     int i;

     switch(j)
       {
            case 0:
            if(((pattern)->rule_UL.rule!=NULL) && ((pattern)->rule_UL.poids!=NULL))
            {
            printf("UL:\n");
            for(i=0; i<(pattern)->rule_UL.length;  i++)
            {
                printf("%d poid: %d\n",pattern->rule_UL.rule[i],pattern->rule_UL.poids[i]);
            }
            }else{printf("UL:\nRAS\n");}

            if(((pattern)->rule_up.rule!=NULL) && ((pattern)->rule_up.poids!=NULL))
            {
            printf("Up:\n");
            for(i=0; i<(pattern)->rule_up.length;  i++)
            {
                printf("%d poid: %d\n",pattern->rule_up.rule[i],pattern->rule_up.poids[i]);
            }
            }else{printf("Up:\nRAS\n");}
             break;


            case 1:

            if(((pattern)->rule_UR.rule!=NULL) && ((pattern)->rule_UR.poids!=NULL))
            {
            printf("UR:\n");
            for(i=0; i<(pattern)->rule_UR.length;  i++)
            {
                printf("%d poid: %d\n",pattern->rule_UR.rule[i],pattern->rule_UR.poids[i]);
            }
            }else{printf("UR:\nRAS\n");}
            if(((pattern)->rule_right.rule!=NULL) && ((pattern)->rule_right.poids!=NULL))
            {
            printf("Right:\n");
            for(i=0; i<(pattern)->rule_right.length;  i++)
            {
                printf("%d poid: %d\n",pattern->rule_right.rule[i],pattern->rule_right.poids[i]);
            }
            }else{printf("Right:\nRAS\n");}
             break;

            case 2:
            if(((pattern)->rule_DR.rule!=NULL) && ((pattern)->rule_DR.poids!=NULL))
            {
            printf("DR:\n");
            for(i=0; i<(pattern)->rule_DR.length;  i++)
            {
                printf("%d poid: %d\n",pattern->rule_DR.rule[i],pattern->rule_DR.poids[i]);
            }
            }else{printf("DR:\nRAS\n");}

            if(((pattern)->rule_down.rule!=NULL) && ((pattern)->rule_down.poids!=NULL))
            {
            printf("Down:\n");
            for(i=0; i<(pattern)->rule_down.length;  i++)
            {
                printf("%d poid: %d\n",pattern->rule_down.rule[i],pattern->rule_down.poids[i]);
            }
            }else{printf("Down:\nRAS\n");}
             break;

            case 3:

            if(((pattern)->rule_DL.rule!=NULL) && ((pattern)->rule_DL.poids!=NULL))
            {
            printf("DL:\n");
            for(i=0; i<(pattern)->rule_DL.length;  i++)
            {
                printf("%d poid: %d\n",pattern->rule_DL.rule[i],pattern->rule_DL.poids[i]);
            }
            }else{printf("DL:\nRAS\n");}

            if(((pattern)->rule_left.rule!=NULL) && ((pattern)->rule_left.poids!=NULL))
            {
            printf("Left:\n");
            for(i=0; i<(pattern)->rule_left.length;  i++)
            {
                printf("%d poid: %d\n",pattern->rule_left.rule[i],pattern->rule_left.poids[i]);
            }
            }else{printf("Left:\nRAS\n");}
             break;

            default:
                 break;
        }
}


unsigned int xorshift(unsigned int x,unsigned int a1,unsigned int a2,unsigned int a3){
    x=x^(x>>a1);
    x=x^(x<<a2);
    x=x^(x>>a3);
    return x;
}
