#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "complex.h"

#define STR_SIZE_BASIC 1024

bool is_space(char sym)
{
	if (sym == ' ' || sym == '\0' || sym == '\t')
		return true;
	return false;
}

int CharToInt(char sym)
{
	return sym - '0';
}
int StrToInt(char *str, int start)
{
	int num = 0;
	int i = start;
	while (!is_space(str[i])) {
		num += num * 10 + CharToInt(str[i]);
		i++;
	}

	return num;
}
double d_abs(double num)
{
	if (num < 0.0)
		num = -num;
	return num;
}

Complex *complex_create()
{
	Complex *nw = (Complex *) calloc(1, sizeof(Complex));
	nw->re = 0;
	nw->im = 0;
	return nw;
}
void complex_destroy(Complex **num)
{
	free(*num);
	*num = NULL;
}

Complex complex_summ(Complex num1, Complex num2)
{
	Complex res;
	res.re = num1.re + num2.re;
	res.im = num1.im + num2.im;
	return res;
}
Complex complex_composition(Complex num1, Complex num2)
{
	Complex res;
	res.re = num1.re * num1.im - num2.re * num2.im;
	res.im = num1.re * num2.im + num2.re * num1.im;
	return res;
}
Complex complex_quotient(Complex num1, Complex num2)
{
	Complex res;
	res.re = (num1.re * num2.re + num1.im * num2.im) / (num2.re * num2.re + num2.im * num2.im);
	res.im = (num2.re * num1.im - num2.im * num2.re) / (num2.re * num2.re + num2.im * num2.im);
	return res;
}

double complex_distance(Complex num1, Complex num2)
{
	return sqrt((num1.re - num2.re) * (num1.re - num2.re) + (num1.im - num2.im) * (num1.im - num2.im)); 
}

void complex_print(Complex num)
{
	if (num.re == 0 && num.im == 0) {
		printf("0\n");
		return;
	}
	//printf("%.2lf+%.2lfi", num.re, num.im);
	if (num.re != 0)
		printf("%.2lf", num.re);
	if (num.im == 0) {
		//printf("\n");
		return;
	}
	if (num.im > 0 && num.re != 0)
		printf("+");
	printf("%.2lfi", num.im);
}

Complex complex_set_value(char *str, int start)
{
	//printf("%s\n", str);
	Complex res;
	res.re = 0;
	res.im = 0;
	bool is_re_minus = false;
	bool is_im_minus;
	bool is_re = true;
	char *tmp = (char *) calloc(STR_SIZE_BASIC, sizeof(char));
	int i = start;
	int pos = 0;
	int cnt = 0;

	while (str[i] != EOF && str[i] != '\0' && !is_space(str[i])) {
		//printf("%d\n", cnt);
		cnt++;
		if (str[i] == '-') {
			if (i == start)
				is_re_minus = true;
			else {
				is_im_minus = true;
				tmp[pos] = '\0';
				res.re = StrToInt(tmp, 0);
				is_re = false;
			}
			pos = 0;
			i++;
			continue;
		}
		if (str[i] == '+') {
			tmp[pos] = '\0';
			pos = 0;
			res.re = StrToInt(tmp, 0);
			is_re = false;
			i++;
			continue;
		}
		if (str[i] == 'i' || str[i] == 'I') {
			tmp[pos] = '\0';
			res.im = StrToInt(tmp, 0);
			if (res.im == 0)
				res.im = 1;
			is_re = false;
		}
		tmp[pos] = str[i];
		pos++;
		i++; 
	}
	if (is_re) {
		res.re = StrToInt(tmp, 0);
	}
	if (is_re_minus)
		res.re = -res.re;
	if (is_im_minus)
		res.im = -res.im;
	free(tmp);
	return res;
}

bool complex_is_zero(Complex num)
{
	return num.re == 0 && num.im == 0;
}
