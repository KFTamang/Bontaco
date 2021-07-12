#ifndef __SCI_HEADER__
#define __SCI_HEADER__

char sci_put_1byte(unsigned char c);
static char *parseFormat(char *str, void *value);
short sci_printf(char *str, ...);

#endif
