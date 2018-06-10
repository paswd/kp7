#ifndef _NOTE_H_
#define _NOTE_H_

#include <stdbool.h>
#include "complex.h"

typedef Complex Numeral;

typedef struct {
	int col_num;
	union Value {
		Numeral num;
		int row_num;
	} value;
	bool is_first_el;
} Note;


#endif
