#include "Grille.h"
#include "utils.h"
#include "Utils_wfc.h"






void Init_grille(Grille *grille, Rule * listeRule ,int height,int width)
{
     int i, j;

     grille->cellules=(Cellule*) calloc(height*width,sizeof(Cellule));
     if(grille->cellules!=NULL)
     {
         grille->height_g=height;
         grille->wigth_g=width;

     }else{ON_ERROR_EXIT(1,"");}

     for(i=0; i<height; i++)
     {

         for(j=0; j<width; j++)
         {
             New_Cell(grille->cellules+i*width+j,listeRule);
         }
     }



}


void New_Cell(Cellule *cell, Rule *listeRule)
{
    cell->collapse=0;
    cell->etat=true;
    cell->id=-1;
    cell->entropie=10000;
    cell->rule.poids=NULL;
    cell->rule.rule=NULL;
    New_Rule(&(cell->rule));
    Append_rule(&(cell->rule), listeRule);

}


void EtatDeLaGrille(Grille*grille)
{
     int i,j;
     int ref=0;
     bool bl;
     if(grille->cellules!=NULL){
     for(i=0; i<grille->height_g;  i++)
        {
           for(j=0; j<grille->wigth_g;  j++)
           {
                ref=i*grille->wigth_g+j;
                bl=grille->cellules[ref].etat;
                printf("Position (%d,%d): %d. ",i,j,bl);
           }
           printf("\n");
        }
        }else{ON_ERROR_EXIT(grille->cellules==NULL,"");}
}

void IdCelluleGrille(Grille* grille)
{

    int i;
    if(grille->cellules!=NULL){
    for(i=0; i<grille->height_g*grille->wigth_g;i++)
    {
        printf("---------------Cellule [%d]---------------\n",i);
        printf("ETAT:%d <-> ID:%d.\n",grille->cellules[i].etat,grille->cellules[i].id);
        printf("Entropie:%f\n",grille->cellules[i].entropie);
    }
    }else{ON_ERROR_EXIT(grille->cellules==NULL,"");}



}

void AfficheRuleCelluleGrille(Grille* grille)
{
    int i,taille;
    taille=grille->height_g*grille->wigth_g;
    for(i=0; i<taille ;i++)
    {
        printf("------------Cellule:[%d]------------------\n",i);
        Affiche_Rule(&grille->cellules[i].rule);
    }
}

void InitialiseGrille(Grille *grille,int *alea_t,int *alea_g1,int *alea_g2,int *position)
{
    int index,poid;


    *alea_g1=nombrePseudoAleatoire(grille->height_g);
    *alea_g2=nombrePseudoAleatoire(grille->wigth_g);
    *position=(*alea_g1)*grille->wigth_g+(*alea_g2);
    index=P_IdMasseHopRule(&(grille->cellules[*position].rule));
    ON_ERROR_EXIT(index>=grille->cellules[*position].rule.length,"");
    *alea_t=grille->cellules[*position].rule.rule[index];
    ON_ERROR_EXIT(*alea_t==-1,"");
    poid=grille->cellules[*position].rule.poids[index];
    grille->cellules[*position].id=*alea_t;
    grille->cellules[*position].etat=false;
    grille->cellules[*position].collapse=1;
    grille->cellules[*position].entropie=0;
    MiseAJ_Rule_Cellule(grille->cellules+(*position),*alea_t,poid);

}


void MiseAJ_Rule_Cellule(Cellule *cell, int id, int poid)
{
    if(cell!=NULL){
    Free_Rule(&cell->rule);
    New_Rule(&cell->rule);
    Rule_append(&cell->rule,id,poid);}
    else{ON_ERROR_EXIT(cell==NULL,"");}

}


bool Uncollapse(Grille *grille)
{
    int i,taille_g,compteur=0;
    taille_g=grille->height_g*grille->wigth_g;
    for(i=0; i<taille_g;i++)
    {
        if(grille->cellules[i].etat){compteur++;}
        else{continue;}
    }
    if(compteur!=0){return true;}
    else{return false;}
}


void Neutral_Intersection(Grille* grille, Patterns* patterns,int a, int b)
{
    int i,id,ind=0;
    int position[8];

    int h_gril,w_gril,Cu_Id;
    h_gril=grille->height_g;
    w_gril=grille->wigth_g;

    Rule copie;
    copie.poids=NULL;
    copie.rule=NULL;
    copie.length=0;

    Cu_Id=ajust(a,h_gril)*w_gril+ajust(b,w_gril);
    ON_ERROR_EXIT(Cu_Id==-1,"");
    position[0]=ajust(a-1,h_gril)*w_gril+ajust(b,w_gril);
    position[1]=ajust(a,h_gril)*w_gril+ajust(b+1,w_gril);
    position[2]=ajust(a+1,h_gril)*w_gril+ajust(b,w_gril);
    position[3]=ajust(a,h_gril)*w_gril+ajust(b-1,w_gril);
    position[4]=ajust(a-1,h_gril)*w_gril+ajust(b-1,w_gril);
    position[5]=ajust(a-1,h_gril)*w_gril+ajust(b+1,w_gril);
    position[6]=ajust(a+1,h_gril)*w_gril+ajust(b+1,w_gril);
    position[7]=ajust(a+1,h_gril)*w_gril+ajust(b-1,w_gril);


    bool in[8];
    in[0]=In_grille(grille,a-1,b);
    in[1]=In_grille(grille,a,b+1);
    in[2]=In_grille(grille,a+1,b);
    in[3]=In_grille(grille,a,b-1);
    in[4]=In_grille(grille,a-1,b-1);
    in[5]=In_grille(grille,a-1,b+1);
    in[6]=In_grille(grille,a+1,b+1);
    in[7]=In_grille(grille,a+1,b-1);

    for(i=0; i<8 ; i++)
    {
        if(!grille->cellules[position[i]].etat && grille->cellules[position[i]].id==-1){ind++;}
        else{continue;}
    }

    //ind=0;
    if(ind==0){
    if(!grille->cellules[position[0]].etat && grille->cellules[position[0]].id!=-1 && in[0])
    {
        id=grille->cellules[position[0]].id;
        IntersectionRule(grille->cellules[Cu_Id].rule,(patterns->tile+id)->rule_down,&copie);
        Copy_rule(&copie,&grille->cellules[Cu_Id].rule);
        Free_Rule(&copie);
    }

    if(!grille->cellules[position[4]].etat && grille->cellules[position[4]].id!=-1 && in[4])
    {
        id=grille->cellules[position[4]].id;
        IntersectionRule(grille->cellules[Cu_Id].rule,(patterns->tile+id)->rule_DR,&copie);
        Copy_rule(&copie,&grille->cellules[Cu_Id].rule);
        Free_Rule(&copie);
    }
    //----------------------------------------------------------------------

    if(!grille->cellules[position[1]].etat && grille->cellules[position[1]].id!=-1 && in[1])
    {
        id=grille->cellules[position[1]].id;
        IntersectionRule(grille->cellules[Cu_Id].rule,(patterns->tile+id)->rule_left,&copie);
        Copy_rule(&copie,&grille->cellules[Cu_Id].rule);
        Free_Rule(&copie);
    }

    if(!grille->cellules[position[5]].etat && grille->cellules[position[5]].id!=-1  && in[5])
    {
        id=grille->cellules[position[5]].id;
        IntersectionRule(grille->cellules[Cu_Id].rule,(patterns->tile+id)->rule_DL,&copie);
        Copy_rule(&copie,&grille->cellules[Cu_Id].rule);
        Free_Rule(&copie);
    }
    //----------------------------------------------------------------------
    if(!grille->cellules[position[2]].etat  && grille->cellules[position[2]].id!=-1  && in[2])
    {
        id=grille->cellules[position[2]].id;
        IntersectionRule(grille->cellules[Cu_Id].rule,(patterns->tile+id)->rule_up,&copie);
        Copy_rule(&copie,&grille->cellules[Cu_Id].rule);
        Free_Rule(&copie);

    }

    if(!grille->cellules[position[6]].etat && grille->cellules[position[6]].id!=-1  && in[6])
    {
        id=grille->cellules[position[6]].id;
        IntersectionRule(grille->cellules[Cu_Id].rule,(patterns->tile+id)->rule_UL,&copie);
        Copy_rule(&copie,&grille->cellules[Cu_Id].rule);
        Free_Rule(&copie);
    }
    //----------------------------------------------------------------------
    if(!grille->cellules[position[3]].etat && grille->cellules[position[3]].id!=-1  && in[3])
    {
        id=grille->cellules[position[3]].id;
        IntersectionRule(grille->cellules[Cu_Id].rule,(patterns->tile+id)->rule_right,&copie);
        Copy_rule(&copie,&grille->cellules[Cu_Id].rule);
        Free_Rule(&copie);

    }
    if(!grille->cellules[position[7]].etat && grille->cellules[position[7]].id!=-1 && in[7])
    {
        id=grille->cellules[position[7]].id;
        IntersectionRule(grille->cellules[Cu_Id].rule,(patterns->tile+id)->rule_UR,&copie);
        Copy_rule(&copie,&grille->cellules[Cu_Id].rule);
        Free_Rule(&copie);
    }
    //----------------------------------------------------------------------
    if(copie.poids!=NULL && copie.poids!=NULL){
    Free_Rule(&copie);}
    }else{New_Rule(&grille->cellules[Cu_Id].rule);}


}

void ImprimeImage(Grille* grille, Patterns* patterns)
{
    int i,j;
    int ref;
    int cible;
    bool bl;
    int h_gril,w_gril;
    h_gril=grille->height_g;
    w_gril=grille->wigth_g;

    Image  img_blurred;
    ColorImage cimg_sortie;
    Color transparent,colordefault;
    Color_set(&colordefault,0,250,250,125);
    Color_set(&transparent,10,45,5,255);
    ColorImage_create(&cimg_sortie,(patterns->size_tile_w)*w_gril,(patterns->size_tile_h)*h_gril);
    //reconstitution de l'image de sortie

      for(i=0; i<h_gril;  i++)
        {
           for(j=0; j<w_gril;  j++)
           {
             ref=i*w_gril+j;
             bl=grille->cellules[ref].etat;
             if(bl==false)
                 {
                     cible=grille->cellules[ref].id;
                     if(0<=cible){Color_sortie(&cimg_sortie, (patterns->tile+cible),&colordefault,i,j);}
                     else{Color_sortie_pad(&cimg_sortie,patterns->size_tile_h,patterns->size_tile_w,i,j,&transparent);}
                 }
             else{
               //ON_ERROR_EXIT(1,"");
                Color_sortie_pad(&cimg_sortie,patterns->size_tile_h,patterns->size_tile_w,i,j,&colordefault);}
           }
        }
        ColorImage_to_Image(&img_blurred,&cimg_sortie);
        Image_save(&img_blurred, "wfc.png");
        Image_free(&img_blurred);
        ColorImage_free(&cimg_sortie);

}

void PropagationContrainte_Locale(Grille* grille, Patterns* patterns,int *ER)
{
    int i,j,position=0;


    for(i=0; i<grille->height_g; i++)
    {
        for(j=0; j<grille->wigth_g; j++)
        {
            position=i*grille->wigth_g+j;
            if(grille->cellules[position].etat && TestVoisinageOff(grille,i,j)){
            Neutral_Intersection(grille,patterns,i,j);
            if(grille->cellules[position].rule.poids[0]==0&&grille->cellules[position].rule.rule[0]==-1&&grille->cellules[position].rule.length==1)
            {
                *ER=-1;
            grille->cellules[position].collapse=1;
            grille->cellules[position].etat=false;
            grille->cellules[position].entropie=0;
            grille->cellules[position].id=-1;
            //break;
            }
            }

        }
        //if(*ER==-1){break;}
    }

}


void PropagationEntropie_Locale(Grille* grille)
{
    int i,j,position;

    for(i=0; i<grille->height_g; i++)
    {
        for(j=0; j<grille->wigth_g; j++)
        {
            position=i*grille->wigth_g+j;
            if(grille->cellules[position].etat && TestVoisinageOff(grille,i,j))
            {
                grille->cellules[position].entropie=Entropy(&grille->cellules[position].rule);
            }

        }
    }
}


int NbreCelluleOnGrille(Grille* grille)
{
    int i,j,position;
    int compteur=0;

    for(i=0; i<grille->height_g; i++)
    {
        for(j=0; j<grille->wigth_g; j++)
        {
            position=i*grille->wigth_g+j;
            if(grille->cellules[position].etat)
            {
                compteur++;
            }

        }
    }

    return compteur;
}

int NbCelHaveVoisin(Grille *grille)
{
    int i,j,position;
    int compteur=0;

    for(i=0; i<grille->height_g; i++)
    {
        for(j=0; j<grille->wigth_g; j++)
        {
            position=i*grille->wigth_g+j;
            if(grille->cellules[position].etat && TestVoisinageOff(grille,i,j))
            {
                compteur++;
            }

        }
    }

    return compteur;
}


void Collapse_Local(Grille *grille, int *alea_t, int *alea_g1, int *alea_g2,int *position, int *EM)
{
    int i,j,ON,find=0;
    int poid, index;
    int position1;

    if(Uncollapse(grille)){
    ON=NbCelHaveVoisin(grille);
    //ON_ERROR_EXIT(ON==0,"Pas de voisin");
    for(i=0; i<grille->height_g; i++)
    {
        for(j=0; j<grille->wigth_g; j++)
        {
            if(grille->cellules[i*grille->wigth_g+j].etat && TestVoisinageOff(grille,i,j)){
            *alea_g1=i;
            *alea_g2=j;
            *EM=i*grille->wigth_g+j;
            if(FindPositionEntropieMin_Local(grille,i,j,ON))
            {

                find=1;
                break;
            }
            }
        }

        if(find){break;}
    }
    //ON_ERROR_EXIT(find==0,"Entropy min not Found\n");
    if(find){
    *position=(*alea_g1)*grille->wigth_g+(*alea_g2);
    index=nombrePseudoAleatoire(grille->cellules[(*position)].rule.length);
    //index=P_IdMasseHopRule(&(grille->cellules[*position].rule));
    *alea_t=grille->cellules[(*position)].rule.rule[index];
    ON_ERROR_EXIT(*alea_t==-1,"");
    poid=grille->cellules[(*position)].rule.poids[index];
    grille->cellules[*position].collapse=1;
    grille->cellules[*position].entropie=0;
    grille->cellules[*position].etat=false;
    grille->cellules[*position].id=*alea_t;
    MiseAJ_Rule_Cellule(grille->cellules+(*position),*alea_t,poid);
    }else{*EM=-2;}}
}

bool FindPositionEntropieMin_Local(Grille* grille,int a,int b,int ON)
{
    int i,j,cmp=0;

    for(i=0; i<grille->height_g; i++)
    {

        for(j=0; j<grille->wigth_g; j++)
        {
            if(grille->cellules[i*grille->wigth_g+j].etat && TestVoisinageOff(grille,i,j))
            {
            if(grille->cellules[a*grille->wigth_g+b].entropie <= grille->cellules[i*grille->wigth_g+j].entropie){cmp++;}
            else{continue;}
            }
        }

    }

    if(cmp==ON)
        {
        return true;
        }
    else
        {
        return false;
        }
}


void Free_grille(Grille* grille)
{
    int i,j;

    if(grille->cellules!=NULL)
    {

    for(i=0; i<grille->height_g; i++)
     {

         for(j=0; j<grille->wigth_g; j++)
         {
            Free_Rule(&grille->cellules[i*grille->wigth_g+j].rule);
         }
     }
    free(grille->cellules);
    grille->cellules=NULL;
    }else{ON_ERROR_EXIT(grille->cellules==NULL,"Impossible! la grille est deja vide!");}
}
bool TestVoisinageOff(Grille *grille, int a, int b)
{
    int h_gril,w_gril, i,ind=0;
    h_gril=grille->height_g;
    w_gril=grille->wigth_g;

    int position[8];
    position[0]=ajust(a-1,h_gril)*w_gril+ajust(b,w_gril);
    position[1]=ajust(a,h_gril)*w_gril+ajust(b+1,w_gril);
    position[2]=ajust(a+1,h_gril)*w_gril+ajust(b,w_gril);
    position[3]=ajust(a,h_gril)*w_gril+ajust(b-1,w_gril);
    position[4]=ajust(a-1,h_gril)*w_gril+ajust(b-1,w_gril);
    position[5]=ajust(a-1,h_gril)*w_gril+ajust(b+1,w_gril);
    position[6]=ajust(a+1,h_gril)*w_gril+ajust(b+1,w_gril);
    position[7]=ajust(a+1,h_gril)*w_gril+ajust(b-1,w_gril);


    //Pour l'image carrée
    bool in[8];
    in[0]=In_grille(grille,a-1,b);
    in[1]=In_grille(grille,a,b+1);
    in[2]=In_grille(grille,a+1,b);
    in[3]=In_grille(grille,a,b-1);
    in[4]=In_grille(grille,a-1,b-1);
    in[5]=In_grille(grille,a-1,b+1);
    in[6]=In_grille(grille,a+1,b+1);
    in[7]=In_grille(grille,a+1,b-1);

    for(i=0; i<8 ; i++)
    {
        if(!grille->cellules[position[i]].etat && grille->cellules[position[i]].id!=-1 && in[i]){ind++;}
        else{continue;}
    }

    if(ind){return true;}
    else{return false;}
}


bool In_grille(Grille *grille, int a, int b)
{
    if(-1<a && a<grille->height_g && -1<b && b<grille->wigth_g){return true;}
    else{return false;}
}

void Desactive(Grille *grille)
{
    int i,j;

    for(i=0; i<grille->height_g; i++)
    {
        for(j=0; j<grille->wigth_g; j++)
        {
            if(grille->cellules[i*grille->wigth_g+j].etat){grille->cellules[i*grille->wigth_g+j].etat=false;}
        }
    }
}
