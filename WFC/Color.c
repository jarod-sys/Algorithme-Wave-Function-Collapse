#include "Color.h"
#include "Image.h"
#include "utils.h"
#include <math.h>
#include <stdint.h>

void Color_set(Color *color, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    color->red = r;
    color->green = g;
    color->blue = b;
    color->alpha = a;
}

void Color_transparent(Color *color) {
    Color_set(color, 0, 0, 0,0);
}

void Color_black(Color *color) {
   /* Code goes here */
    Color_set(color,0,0,0,0);
}

void Color_white(Color *color) {
   /* Code goes here */
    Color_set(color,255,255,255,255);

}

void Color_copy(Color *from, Color *to) {
   /* Code goes here */

    Color_set(to,from->red,from->green,from->blue,from->alpha);


}

void Color_interpolate(Color *c, Color *c1, Color *c2, float t) {
   /* Code goes here */

    float x,y,z,t1;

    x=(1-t)*((float)c1->red)+ t*((float)c2->red);
    y=(1-t)*((float)c1->green) + t*((float)c2->green);
    z=(1-t)*((float)c1->blue) + t*((float)c2->blue);
    t1=(1-t)*((float)c1->alpha) + t*((float)c2->alpha);

    x=(int) x;
    y=(int) y;
    z=(int) z;
    t1=(int) t1;

    Color_set(c,x,y,z,t);

}

void Color_muladd(Color *x, Color *y, float t) {
   /* Code goes here */

    float a,b,c,d;

    a=((float)x->red) + t*((float)y->red);
    b=((float)x->green) + t*((float)y->green);
    c=((float)x->blue) + t*((float)y->blue);
    d=((float)x->alpha) + t*((float)y->alpha);

    a=(int) a;
    b=(int) b;
    c=(int) c;
    d=(int) d;

    Color_set(x,a,b,c,d);

}


