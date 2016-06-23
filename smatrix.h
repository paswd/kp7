#ifndef _SMATRIX_H_
#define _SMATRIX_H_

#include <stdbool.h>
#include "complex.h"

//typedef Complex Item;

//typedef struct _note Note;
typedef struct _smatrix Smatrix;

Smatrix *smatrix_create();
void smatrix_destroy(Smatrix **matrix); 

void smatrix_fill(Smatrix *matrix);
void smatrix_print_mach(Smatrix *matrix);
void smatrix_print_basic(Smatrix *matrix);

void smatrix_div_on_nearests(Smatrix *matrix, Complex num);

#endif
