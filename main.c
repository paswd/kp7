#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "complex.h"

int main()
{
	Complex a;
	Complex b;
	char *str = (char *) calloc(1024, sizeof(char));
	int sym;
	int i = 0;
	while ((sym = getchar()) != '\n') {
		str[i] = sym;
		i++;
		printf("1:%d\n", i);
	}
	str[i] = '\0';
	a = complex_set_value(str, 0);
	printf("Point\n");
	i = 0;
	while ((sym = getchar()) != '\n') {
		str[i] = sym;
		i++;
		printf("2:%d\n", i);
	}
	str[i] = '\0';
	b = complex_set_value(str, 0);
	complex_print(a);
	printf("\n");
	complex_print(b);
	printf("\n");
	complex_print(complex_summ(a, b));
	printf("\n");
	complex_print(complex_composition(a, b));
	printf("\n");
	return 0;
}