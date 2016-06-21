#ifndef _SMATRIX_H_
#define _SMATRIX_H_

#include <stdbool.h>

bool is_space(char sym);

int CharToInt(char sym);
int StrToInt(char *str, size_t start);

//typedef double complex Item;
typedef double Element;

typedef struct {
	Element re;
	Element im;
} Complex;

Complex *complex_create();
void complex_destroy(Complex **num);

Complex complex_summ(Complex num1, Complex num2);
Complex complex_composition(Complex num1, Complex num2);
void complex_print(Complex num);

Complex complex_set_value(char *str, size_t start);


#endif
