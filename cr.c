/* organize words in document by number of occurences and
 * print each word followed by the line number of those
 * occurences in order */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cr.h"

const int MIN_LINE_LEN = 256;

word_array fparse(FILE* fp);
void print_report(word_array w_arr);

word_array fparse(FILE* fp) {
	word_array w_arr = mk_word_array(0);

	char* line_buf = (char*)malloc(MIN_LINE_LEN * CHARSIZE);
	line_t line = 1;

	char* str_buf = NULL;
	const char* delims = " .\n";

	int w_pos = 0;
	word_array tmp = mk_word_array(0);

	while((fgets(line_buf, MIN_LINE_LEN, fp)) != NULL) {

		for(str_buf = strtok(line_buf, delims); str_buf != NULL; str_buf = strtok(NULL, delims)) {
			if((w_pos = search(w_arr.ptr, 0, (w_arr.len - 1), str_buf)) == -1) {
				append_word(&w_arr, str_buf, line);
				resize(&tmp, 1);
				sort(0, (w_arr.len - 1), w_arr.ptr, tmp.ptr);
			} else
				add_occur(w_arr.ptr, w_pos, line);
		}
		++line;
	}

	str_buf = NULL;
	if(line_buf != NULL)
		free(line_buf);
	line_buf = NULL;
	cleanup(&tmp, 0);

	return w_arr;
}

void print_report(word_array w_arr) {
	for(int i = 0; i < w_arr.len; ++i) {
		printf("%s [%i] : { ", (w_arr.ptr[i]).data, (w_arr.ptr[i]).count);
		for(int j = 0; j < w_arr.ptr[i].count; ++j)
			printf("%i, ", w_arr.ptr[i].lines[j]);
		printf("}\n");
	}
}

int main(int argc, char* argv[]) {
	if(argc == 1) {
		fprintf(stderr, "error: no file given\n");
		exit(1);
	}
	if(argc > 2) {
		fprintf(stderr, "error: too many arguments\n");
		exit(1);
	}

	FILE* fp = fopen(argv[1], "r");

	word_array w_arr = fparse(fp);

	print_report(w_arr);

	cleanup(&w_arr, 1);
	fclose(fp);

	return 0;
}
