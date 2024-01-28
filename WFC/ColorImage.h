#pragma once

#include "Image.h"
#include "Color.h"
#include <stdlib.h>
#include <stdint.h>

/*
A struct representing an image as an RGBA color matrix

Fields:
- `int width` image width in pixels
- `int height` image height in pixels
- `Color *data` An array containing the color data of the image in row major order
*/
typedef struct ColorImage_ {
    int width;
    int height;
    Color *data;

} ColorImage;

/*
Create a new empty ColorImage of size `(width,height)`

PRE:
- `cimg` is allocated
- `cimg->data` is unallocated

POST:
- `cimg->data` is allocated to a block of `width*height` elements
- `cimg->width == width`
- `cimg->height == height`
*/
void ColorImage_create(ColorImage *cimg, int width, int height);

/*
Safely free the memory allocated to a ColorImage

PRE:
- `cimg->data` is allocated

POST:
- `cimg->data` old memory is freed
- `cimg->data == NULL`
- `cimg->width == 0`
- `cimg->height == 0`
*/
void ColorImage_free(ColorImage *cimg);

/*
Get the color at row `i` and column `j` of a ColorImage.

If `(i,j)` is outside the bounds of the image, `pad` is returned instead.

PRE:
- `c`, `cimg` and `pad` are allocated

POST:
- If `0 <= i <= cimg->height` and `0 <= j <= cimg->width`, `c` contains the color at pixel `(i,j)` of `cimg`
- Else `c` is the same as `pad`
*/
void get_color_at(Color *c, ColorImage *cimg, int i, int j, Color *pad);

/*
Set the color at row `i` and column `j` of a ColorImage.

If `(i,j)` is outside the bounds of the image, nothing is done.

PRE:
- `c` and `cimg` are allocated

POST:
- If `0 <= i <= cimg->height` and `0 <= j <= cimg->width`, the pixel `(i,j)` of `cimg` is updated to `c`
- Else `cimg` remains unchanged
*/
void set_color_at(Color *c, ColorImage *cimg, int i, int j);


/*
Create a ColorImage from an Image

PRE:
- `img` is allocated
- `cimg` is unallocated

POST:
- `cimg->data` contains the same pixel data as `img`
- `cimg->width == img->width`
- `cimg->height == img->height`
*/
void Image_to_ColorImage(Image *img, ColorImage *cimg);

/*
Create an Image from a ColorImage

PRE:
- `img` is unallocated
- `cimg` is allocated

POST:
- `img` is allocated and contains the same pixel data as `cimg`
- `img->width == cimg->width`
- `img->height == cimg->height`
*/
void ColorImage_to_Image(Image *img, ColorImage *cimg);
