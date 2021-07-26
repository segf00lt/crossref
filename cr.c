/* organize words in document by number of occurences and
 * print each word followed by the line number of those
 * occurences in order */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cr.h"

const int MIN_LINE_LEN = 64;

word_array fparse(FILE* fp);
void print_report(word_array w_arr);

word_array fparse(FILE* fp) {
	word_array w_arr = mk_word_array(0);

	char* line_buf = (char*)malloc(MIN_LINE_LEN * CHARSIZE);
	line_t line = 1;

	char* str_buf = NULL;
	const char* delims = " .\n";

	int w_pos = 0;
	word_array tmp = { .len = 0, .ptr = NULL };

	while((fgets(line_buf, MIN_LINE_LEN, fp)) != NULL) {

		for(str_buf = strtok(line_buf, delims); str_buf != NULL; str_buf = strtok(NULL, delims)) {
			if((w_pos = search(w_arr.ptr, 0, (w_arr.len - 1), str_buf)) < 0) {
				append_word(&w_arr, str_buf, line);
				tmp = mk_word_array(w_arr.len);
				sort(0, (w_arr.len - 1), w_arr.ptr, tmp.ptr);
			} else
				add_occur(w_arr.ptr, w_pos, line);
		}
		if(line_buf[strlen(line_buf) - 1] == '\n')
			++line;
	}

	str_buf = NULL;
	if(line_buf != NULL)
		free(line_buf);
	line_buf = NULL;

	return w_arr;
}

void print_report(word_array w_arr) {
	return;
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

	for(int i = 0; i < w_arr.len; ++i) {
		printf("%s\n", (w_arr.ptr[i]).data);
	}

	cleanup(&w_arr);
	fclose(fp);

	return 0;
}
