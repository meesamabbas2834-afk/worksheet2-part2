#ifndef DRIVER_KB_H
#define DRIVER_KB_H

#include "type.h"

/* Functions to interface with keyboard driver */
u8int get_scancode(void);
u8int scancode_to_char(u8int code);

#endif
