/* organize words in document by number of occurences and
 * print each word followed by the line number of those
 * occurences in order */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cr.h"

word_array fparse(FILE* fp);

word_array fparse(FILE* fp) {
    // NEEDS REFACTOR
	char* line_buf = (char*)malloc(MIN_LINE_LEN * CHARSIZE);
	unsigned int line = 1;

	while((fgets(line_buf, MIN_LINE_LEN, fp)) != EOF) {
		if(line_buf[0] == '\n')
			continue;

		unsigned int col = 0;
		char c_buf = '\0';
		char* word_buf = NULL;

		while((c_buf = tolower(buf[col++])) != '\0') {
			if('a' <= c_buf && 'z' >= c_buf || c_buf == '-' || c_buf == '\'') {

				word_buf = (char*)realloc(word_buf, (strlen(word_buf) * CHARSIZE));
				word_buf[(word_buf_size / CHARSIZE) - 1] = c_buf;
			}
			if(word_buf != NULL) {

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
