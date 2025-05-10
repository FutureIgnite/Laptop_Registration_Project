#ifndef TC_H
#define TC_H

/*#include <sys/ioctl.h>*/
#define TC_NRM "\x1B[0m"
#define TC_RED "\x1B[1;31m"
#define TC_GRN "\x1B[1;32m"
#define TC_YEL "\x1B[1;33m"
#define TC_BLU "\x1B[1;34m"
#define TC_MAG "\x1B[1;35m"
#define TC_CYN "\x1B[1;36m"
#define TC_WHT "\x1B[1;37m"

#define TC_B_RED "\x1B[0m"
#define TC_B_GRN "\x1B[1;32m"
#define TC_B_YEL "\x1B[1;33m"
#define TC_B_BLU "\x1B[1;34m"
#define TC_B_MAG "\x1B[1;35m"
#define TC_B_CYN "\x1B[1;36m"
#define TC_B_WHT "\x1B[1;37m"

#define TC_BG_NRM "\x1B[40m"
#define TC_BG_RED "\x1B[41m"
#define TC_BG_GRN "\x1B[42m"
#define TC_BG_YEL "\x1B[43m"
#define TC_BG_BLU "\x1B[44m"
#define TC_BG_MAG "\x1B[45m"
#define TC_BG_CYN "\x1B[46m"
#define TC_BG_WHT "\x1b[47m"

#define move_cursor(X, Y) printf ("\033[%d;%dH", Y, X)

/*void get_cols_rows (int*, int*);

void get_cols_rows (int *cols, int *rows){
   struct winsize size;
   ioctl (1, TIOCGWINSZ, &size);
   *cols = size.ws_col;
   *rows = size.ws_row;
}*/

#endif 
