/* organize words in document by number of occurences and
 * print each word followed by the line number of those
 * occurences in order */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STB_DS_IMPLEMENTATION
#define STBDS_SIPHASH_2_4
#include "stb_ds.h"

#define LENGTH(x) (sizeof(x) / sizeof(x[0]))

#define LINE_LEN 256

const char* delims = " \n,.!@`~#$%^&()_-=+[]{};:\"/?><";

char*
strtolower(char* s) {
	for(char* c = s; *c != '\0'; ++c)
		*c = tolower(*c);
	return s;
}

typedef struct { char* key; size_t* value; } WordTableEntrie;
typedef WordTableEntrie* WordTable;

int
entrieCompare(const void* a, const void* b) {
	WordTableEntrie* entrie_a = (WordTableEntrie*)a;
	WordTableEntrie* entrie_b = (WordTableEntrie*)b;

	int verdict = arrlen(entrie_a->value) <= arrlen(entrie_b->value);
	return verdict;
}

WordTable
tabulate(FILE* fp) {
	char buf[LINE_LEN];
	char* word = NULL;

	size_t line = 1;

	/* init word table with mem arena for keys */
	WordTable table = NULL;
	sh_new_arena(table);

	for(;fgets(buf, LENGTH(buf), fp) != NULL; ++line) {
		for(word = strtok(buf, delims); word != NULL; word = strtok(NULL, delims)) {
			word = strtolower(word);

			size_t* lines = shget(table, word);
			arrput(lines, line);
			shput(table, word, lines);
		}
	}

	return table;
}

void
report(WordTable table) {
	for(int i = 0; i < shlen(table); ++i) {
		char* word = table[i].key;
		size_t* lines = table[i].value;

		printf("%zu : %s [ ", arrlen(lines), word);

		size_t last = 0;
		for(int j = 0; j < arrlen(lines); ++j) {
			if(j == 0)
				printf("%zu ", lines[j]);
			if(lines[j] != last && last != 0)
				printf("%zu ", lines[j]);

			last = lines[j];
		}

		printf("]\n");
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

	WordTable table = tabulate(fp);

	qsort((void*)table, shlen(table), sizeof(WordTableEntrie), entrieCompare);

	report(table);

	for(int i = 0; i < shlen(table); ++i) {
		arrfree(table[i].value); 
	}
	shfree(table);

	fclose(fp);

	return 0;
}
