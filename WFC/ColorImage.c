#include "ColorImage.h"
#include "Image.h"
#include "Color.h"
#include "utils.h"

void ColorImage_create(ColorImage *cimg, int width, int height) {
    cimg->data = calloc(width*height, sizeof(Color));

    if (cimg->data != NULL)
    {
        cimg->width = width;
        cimg->height = height;
    }
    else{ON_ERROR_EXIT(cimg->data == NULL , "ColorImage_create: Couldn't allocate memory\n");}
}

void ColorImage_free(ColorImage *cimg) {
    if (cimg->data != NULL) {
        free(cimg->data);
        cimg->data = NULL;
        cimg->width = 0;
        cimg->height = 0;
    }
}

void get_color_at(Color *c, ColorImage *cimg, int i, int j, Color *pad) {
    /* Code goes here */
    if ((0 <= i) && (i< cimg->height) && (0 <= j)&& (j< cimg->width ))
    {
        int w, position;
        Color *p_sur_data=NULL;
        w=cimg->width;
        position=i*w+j;
        p_sur_data=cimg->data+position;
        if(p_sur_data!=NULL){Color_copy(p_sur_data,c);}
        else{ON_ERROR_EXIT(p_sur_data==NULL,"Echec l'hors de l'obtention de la couleur\n");}

    }
    else
    {

        Color_copy(pad,c);
    }


}

void set_color_at(Color *c, ColorImage *cimg, int i, int j)
{
    /* Code goes here */
    if ((0 <= i)&& (i< cimg->height) && (0 <= j)&& (j<cimg->width))
    {
        int w, position;
        Color *p_sur_data=NULL;
        w=cimg->width;
        position=i*w+j;
        p_sur_data=cimg->data+position;
        if(p_sur_data!=NULL){Color_copy(c, p_sur_data);}
        else{ON_ERROR_EXIT(p_sur_data==NULL,"Echec l'hors de copie de la couleur\n");}
    }

}

void Image_to_ColorImage(Image *img, ColorImage *cimg) {
    ON_ERROR_EXIT(!(img->allocation_ != NO_ALLOCATION && img->channels >= 3), "The input image must have at least 3 channels.");
    ColorImage_create(cimg, img->width, img->height);

    uint8_t *p;
    int i;
    for (p = img->data, i = 0; (p != img->data + img->size) && (i < cimg->width*cimg->height); p += img->channels, ++i) {
        if (img->channels == 4) {
            Color_set(cimg->data + i, *p, *(p+1), *(p+2), *(p+3));
        } else {
            Color_set(cimg->data + i, *p, *(p+1), *(p+2), UINT8_MAX);
        }
    }
}

void ColorImage_to_Image(Image *img, ColorImage *cimg)
{
    Image_create(img, cimg->width, cimg->height, 4, false);
    ON_ERROR_EXIT(img->data == NULL, "Error in creating the image");


    uint8_t *p;
    int i;
    for (p = img->data, i = 0; (p != img->data + img->size) && (i < cimg->width*cimg->height); p += img->channels, ++i) {
        *p = cimg->data[i].red;
        *(p+1) = cimg->data[i].green;
        *(p+2) = cimg->data[i].blue;
        *(p+3) = cimg->data[i].alpha;
    }
}
