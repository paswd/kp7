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
	int size;
	int max_width;
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
	int i = 0;
	Queue *queue = queue_create();
	Note tmp;
	tmp.col_num = 0;
	//tmp.is_first_el = true;
	tmp.value.row_num = 1;
	queue_push(queue, tmp);
	int queue_cnt = 1;
	int col = 1;
	int row = 1;
	Complex tmp_complex;
	matrix->max_width = 0;
	int prev_sym = EOF;

	while ((sym = getchar()) != EOF) {
		if (sym == '\n' && prev_sym == '\n')
			break;
		prev_sym = sym;
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
	for (int i = 0; i < matrix->size; i++) {
		printf("%d ", matrix->arr[i].col_num);
		if (matrix->arr[i].col_num == 0)
			printf("%d", matrix->arr[i].value.row_num);
		else
			complex_print(matrix->arr[i].value.num);
		printf("\n");
	}
}
void smatrix_print_basic(Smatrix *matrix)
{
	//int pos = 0;
	int prev_pos = 0;
	for (int i = 0; i < matrix->size; i++) {
		//printf("%d:", i);
		if (matrix->arr[i].col_num == 0) {
			if (matrix->arr[i].value.row_num == 1) {
				continue;
			}
			for (int j = 0; j < matrix->max_width - prev_pos; j++)
				printf("0 ");
			printf("\n");
			prev_pos = 0;
			continue;
		}
		//printf("(%d:%d)", matrix->arr[i].col_num, prev_pos);
		//printf("(%d)", matrix->arr[i].col_num - prev_pos);
		int cnt = 0;
		for (int j = 0; j < matrix->arr[i].col_num - prev_pos - 1; j++) {
			//printf("Pnt");
			printf("0 ");
			cnt++;
		}
		complex_print(matrix->arr[i].value.num);
		printf(" ");
		prev_pos = matrix->arr[i].col_num;
	}
}

void smatrix_quotient(Smatrix *matrix, Complex num, int curr_row, int curr_col)
{
	int col = 0;
	int row = 0;
	for (int i = 0; i < matrix->size; i++) {
		if (matrix->arr[i].col_num == 0) {
			col = 1;
			row = matrix->arr[i].value.row_num;
			continue;
		}
		if (col == curr_col || row == curr_row)
			matrix->arr[i].value.num = complex_quotient(matrix->arr[i].value.num, num);
		col++;
	}
}
void smatrix_div_on_nearests(Smatrix *matrix, Complex num)
{
	//Complex ths_complex;
	//ths_complex.re = 0;
	//ths_complex.im = 0;
	int tmp_col = 0;
	int tmp_row = 0;
	double min = -1.0;
	double tmp_min;
	for (int i = 0; i < matrix->size; i++) {
		if (matrix->arr[i].col_num == 0) {
			tmp_col = 1;
			tmp_row = matrix->arr[i].value.row_num;
			continue;
		}
		if ((tmp_min = complex_distance(num, matrix->arr[i].value.num)) < min || min == -1.0) {
			min = tmp_min;
			//ths_complex = matrix->arr[i].value.num;
		}
		tmp_col++;
	}
	tmp_col = 0;
	tmp_row = 0;
	for (int i = 0; i < matrix->size; i++) {
		if (matrix->arr[i].col_num == 0) {
			tmp_col = 1;
			tmp_row = matrix->arr[i].value.row_num;
			continue;
		}
		if (complex_distance(num, matrix->arr[i].value.num) == min)
			smatrix_quotient(matrix, matrix->arr[i].value.num, tmp_row, tmp_col);

		tmp_col++;
	}
	//return ths_complex;
}
