#pragma once

#include "Image.h"
#include <stdlib.h>
#include <stdint.h>

/*
A struct representing a color in RBGA format.

Fields:
- `uint8_t red` red component
- `uint8_t green` green component
- `uint8_t blue` blue component
- `uint8_t alpha` alpha component (transparency)

*/
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} Color;



typedef struct {
    Color *colors;
    int size;
} ColorDict;

/*
Set the content of `color` to the rgba color `(r,g,b,a)`.

PRE:
- `color` is allocated
POST:
- `color`'s data is updated to `(r,g,b,a)`
*/
void Color_set(Color *color, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/*
Set the Color `c` to the transparent color

PRE:
- `color` is allocated

POST:
- `color`'s data is updated to (0,0,0,0)
*/
void Color_transparent(Color *c);

/*
Set the Color `c` to pure black

PRE:
- `color` is allocated

POST:
- `color`'s data is updated to (0,0,0,255)
*/
void Color_black(Color *c);

/*
Set the color `c` to pure white

PRE:
- `color` is allocated

POST:
- `color`'s data is updated to (255,255,255,255)
*/
void Color_white(Color *c);

/*
Copy the Color `from` into the Color `to`

PRE:
- `from` and `to` are allocated

POST:
- the contents of `from` have been copied to `to`
*/
void Color_copy(Color *from, Color *to);


/*
Interpolate between colors `c1` and `c2` and store the result in `c`

PRE:
- `c`, `c1` and `c2` are allocated

POST:
- `c` is updated so that "c = t*c1 + (1-t)*c2"
*/
void Color_interpolate(Color *c, Color *c1, Color *c2, float t);

/*
Compute `x + t*y` and store the result in `x`

PRE:
- `x` and `y` are allocated

POST:
- `x` is updated so that "x = x + t*y"
*/
void Color_muladd(Color *x, Color *y, float t);


