/* organize words in document by number of occurences and
 * print each word followed by the line number of those
 * occurences in order */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned int count;
	unsigned int* lines;
	char* data;
}word;

const int MIN_LINE_LEN = 64;
const size_t CHARSIZE = sizeof(char);
const size_t WORDSIZE = sizeof(word);

word* parsef(FILE* fp);

void addword(word* w_arr, size_t w_arr_size, char* w);

int search(word* w_arr, int begin, int end, char* w);

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

	fclose(fp);

	return 0;
}

word* parsef(FILE* fp) {
	char* line_buf = (char*)malloc(MIN_LINE_LEN * CHARSIZE);
	word* w_arr = NULL;
	unsigned int line = 1;

	while((fgets(line_buf, MIN_LINE_LEN, fp)) != EOF) {
		if(line_buf[0] == '\n')
			continue;

		unsigned int col = 0;
		char c_buf = '\0';
		char* word_buf = NULL;

		while((c_buf = tolower(buf[col++])) != '\0') {
			if('a' <= c_buf && 'z' >= c_buf || c_buf == '-' || c_buf == '\'') {
				size_t word_buf_size = sizeof(word_buf);

				word_buf = (char*)realloc(word_buf, (word_buf_size + CHARSIZE));
				word_buf[(word_buf_size / CHARSIZE) - 1] = c_buf;
			}
			if(word_buf != NULL) {
				size_t w_arr_size = sizeof(w_arr);
				w_arr = (word*)realloc(w_arr_size + WORDSIZE);

				free(word_buf);
				word_buf = NULL;
			}
		}
		if(line_buf[strlen(line_buf) - 1] == '\n')
			++line;
	}

	free(line_buf);
	line_buf = NULL;
}

void addword(word* w_arr, size_t w_arr_size, chr* w) {
}

int search(word* w_arr, int begin, int end, char* w) {
	if (end >= begin) {
		int mid = (begin + end) / 2;

		if (strcmp(w_arr[mid].data, w) == 0)
			return mid;

		if (strcmp(w_arr[mid].data, w) > 0)
			return bin_search(w_arr, begin, mid - 1, w);

		return bin_search(w_arr, mid + 1, end, w);
	}

	return -1;
}
