#ifndef _NOTE_H_
#define _NOTE_H_

#include <stdbool.h>
#include "complex.h"

typedef Complex Numeral;

typedef struct {
	size_t col_num;
	union Value {
		Numeral num;
		size_t row_num;
	} value;
	//bool is_first_el;
} Note;


#endif
