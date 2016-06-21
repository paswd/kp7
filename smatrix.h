#ifndef _SMATRIX_H_
#define _SMATRIX_H_

#include <stdbool.h>

typedef double complex Item;

typedef struct _smatrix Smatrix;

Smatrix *smatrix_create();
void smatrix_destroy(Smatrix **matrix); 



#endif
