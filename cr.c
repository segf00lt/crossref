/* organize words in document by number of occurences and
 * print each word followed by the line number of those
 * occurences in order */

/*
 * PLANNING:
 *
 * parse(): read file line by line:
 * 	process(): replace punctuation and other stuff
 * 	with whitespace.
 * 	
 * 	strtok(): tokenize line separating words by whitespace.
 *
 * 	map_in(): lookup word in noise table:
 * 		if word is in noise table: continue
 *
 * 	map_in(): lookup word in table:
 * 		if word is not in table: add word to table.
 *
 * 		append line number to table item.
 *
 * 	map_items(): return list of items in table.
 *
 * 	qsort() or msort(): sort list returned by map_items().
 *
 * 	return list.
 *
 * print_words(): print words in list and corresponding line numbers on
 * which they occur.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lib/vector/vector.h"
#include "lib/unordered_map/map.h"

#define LINE_LEN 255
#define NOISE_WORDS 13

Item* parse(FILE* fp);
void print_report(Item* arr);

Item*
parse(FILE* fp) {
	//word_array w_arr = mk_word_array(0);

	char* line_buf[LINE_LEN];
	//line_t line = 0;
	unsigned int line = 0;

	char* str_buf = NULL;
	const char* filter = " {}[]()\"&^@!#$%-=+`~<>/|.,\n";

	const char* NOISE[NOISE_WORDS] = {
		"a", "and", "be",
		"have", "i", "it",
		"of", "on", "that",
		"the", "to", "with",
		"you"
	};

	Map* noise = map_prealloc(NOISE_WORDS, char);

	/* populate noise word map */
	for(int i = 0; i < NOISE_WORDS; ++i)
		map_add(noise, NOISE[i]);

	while(fgets(line_buf, LINE_LEN, fp) != NULL) {

		if(line_buf[strlen(line_buf) - 1] == '\n') {
			++line;
			continue;
		}

		for(str_buf = strtok(line_buf, filter); str_buf != NULL; str_buf = strtok(NULL, delims)) {
			str_buf = lower(str_buf);

			if(search(NOISE_ARR.ptr, 0, 12, str_buf) >= 0)
				continue;

			if((w_pos = search(w_arr.ptr, 0, (w_arr.len - 1), str_buf)) == -1) {
				append_word(&w_arr, str_buf, line);
				resize(&tmp, 1);
				sort(0, (w_arr.len - 1), w_arr.ptr, tmp.ptr, 1);
			} else
				add_occur(w_arr.ptr, w_pos, line);
		}
	}

	str_buf = NULL;
	if(line_buf != NULL)
		free(line_buf);
	line_buf = NULL;
	cleanup(&tmp, 0);
	cleanup(&NOISE_ARR, 1);

	return w_arr;
}

void print_report(word_array w_arr) {
	word_array tmp = mk_word_array(w_arr.len);
	sort(0, (w_arr.len - 1), w_arr.ptr, tmp.ptr, 0);
	cleanup(&tmp, 0);
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
