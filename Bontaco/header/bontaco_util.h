#ifndef BONTACO_UTIL_H
#define BONTACO_UTIL_H

#include <stdarg.h>
#include "../iodefine.h"

char sci_put_1byte(unsigned char c);
static char *parseFormat(char *str,void *value);
short sci_printf(char *str , ...);
void check_battery();

#endif