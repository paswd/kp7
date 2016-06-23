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
	printf("----------\n");
	smatrix_print_basic(matrix);
	printf("==========\n");
	int sym;
	char str[2048];
	int i = 0;
	while ((sym = getchar()) != EOF) {
		if (i >= 2046) {
			str[2047] = '\0';
			break;
		}
		if (sym == 'i' || sym == 'I') {
			str[i] = sym;
			str[i + 1] = '\0';
			break;
		}
		str[i] = sym;
		i++;
	}
	printf("%s\n", str);
	printf("----------\n");
	smatrix_div_on_nearests(matrix, complex_set_value(str, 0));
	smatrix_print_mach(matrix);
	printf("----------\n");
	smatrix_print_basic(matrix);
	smatrix_destroy(&matrix);
	return 0;
}
