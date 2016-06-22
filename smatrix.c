#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "smatrix.h"
#include "complex.h"
#include "queue.h"
#include "note.h"

struct _smatrix {
	Note *arr;
	size_t size;
	size_t max_width;
};

Smatrix *smatrix_create(void) {
	Smatrix *nw = (Smatrix *) calloc(1, sizeof(Smatrix));
	nw->arr = NULL;
	nw->size = 0;
	nw->max_width = 0;
	return nw;
}
void smatrix_destroy(Smatrix **matrix)
{
	free((*matrix)->arr);
	free(*matrix);
	*matrix = NULL;
}

void smatrix_fill(Smatrix *matrix)
{
	int sym;
	char tmp_str[2048];
	size_t i = 0;
	Queue *queue = queue_create();
	Note tmp;
	tmp.col_num = 0;
	//tmp.is_first_el = true;
	tmp.value.row_num = 1;
	queue_push(queue, tmp);
	size_t queue_cnt = 1;
	size_t col = 1;
	size_t row = 1;
	Complex tmp_complex;
	matrix->max_width = 0;

	while ((sym = getchar()) != EOF) {
		if (sym == ' ' || sym == '\n') {
			tmp_str[i] = '\0';
			tmp_complex = complex_set_value(tmp_str, 0);
			i = 0;
			if (!complex_is_zero(tmp_complex)) {
				tmp.col_num = col;
				//tmp.is_first_el = false;
				tmp.value.num = tmp_complex;
				queue_push(queue, tmp);
				queue_cnt++;
				if (tmp.col_num > matrix->max_width)
					matrix->max_width = tmp.col_num;
			}
			col++;
			if (sym == '\n') {
				col = 1;
				row++;
				tmp.col_num = 0;
				//tmp.is_first_el = true;
				tmp.value.row_num = row;
				queue_push(queue, tmp);
				queue_cnt++;
			}
			continue;
		}
		tmp_str[i] = sym;
		i++;
	}
	matrix->size = queue_cnt;
	matrix->arr = (Note *) calloc(matrix->size, sizeof(Note));
	for (i = 0; i < queue_cnt; i++) {
		matrix->arr[i] = queue_pop(queue);
		if (i == queue_cnt - 1) {
			matrix->arr[i].col_num = 0;
			matrix->arr[i].value.row_num = 0;
			//matrix->arr[i].is_first_el = true;
		}
	}
	queue_destroy(&queue);
}

void smatrix_print_mach(Smatrix *matrix)
{
	for (size_t i = 0; i < matrix->size; i++) {
		printf("%lu ", matrix->arr[i].col_num);
		if (matrix->arr[i].col_num == 0)
			printf("%lu", matrix->arr[i].value.row_num);
		else
			complex_print(matrix->arr[i].value.num);
		printf("\n");
	}
}
/*void smatrix_print_basic(Smatrix *matrix)
{
	size_t pos = 1;
	size_t prev_pos = 0;
	for (size_t i = 0; i < matrix->size; i++) {
		if (matrix->arr[i].col_num == 0)
	}
}*/
