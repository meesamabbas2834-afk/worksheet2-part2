#ifndef DRIVER_FB_H
#define DRIVER_FB_H

#include "io.h"

/* Colors re-defined with new names */
#define COLOR_BLK    0
#define COLOR_BLU    1
#define COLOR_GRN    2
#define COLOR_CYN    3
#define COLOR_RED    4
#define COLOR_MAG    5
#define COLOR_BRN    6
#define COLOR_LGRY   7
#define COLOR_DGRY   8
#define COLOR_LBLU   9
#define COLOR_LGRN   10
#define COLOR_LCYN   11
#define COLOR_LRED   12
#define COLOR_LMAG   13
#define COLOR_LBRN   14
#define COLOR_WHT    15

/* Function prototypes */
void fb_clear();
void fb_write(char *text, unsigned int len, unsigned char color);
void fb_write_dec(unsigned int number, unsigned char color);

#endif
