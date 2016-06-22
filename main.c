#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "complex.h"
#include "smatrix.h"
#include "note.h"

int main()
{
	Smatrix *matrix = smatrix_create();
	smatrix_fill(matrix);
	smatrix_print_mach(matrix);
	smatrix_destroy(&matrix);
	return 0;
}