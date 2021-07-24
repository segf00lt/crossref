/* organize words in document by number of occurences and
 * print each word followed by the line number of those
 * occurences in order */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cr.h"

word_array fparse(FILE* fp);
void print_report(word_array w_arr);

word_array fparse(FILE* fp) {
    word_array w_arr = { .len = 0, .ptr = NULL };

    char* line_buf = (char*)malloc(MIN_LINE_LEN * CHARSIZE);
    line_t line = 1;

    unsigned int col = 0;
    char c_buf = '\0';
    char* word_buf = NULL;
    int w_pos = 0;
    char** tmp = NULL;

    while((fgets(line_buf, MIN_LINE_LEN, fp)) != EOF) {

        while((c_buf = tolower(line_buf[col++])) != '\0') {

            if('a' <= c_buf && 'z' >= c_buf || c_buf == '-' || c_buf == '\'') {
                word_buf = (char*)realloc(word_buf, (strlen(word_buf) * CHARSIZE));
                word_buf[strlen(word_buf) - 1] = c_buf;

            } else if(word_buf != NULL) {
                if((w_pos = search(w_arr.ptr, 0, (w_arr.len - 1), word_buf)) < 0) {
                    add_word(&w_arr, word_buf, line);
                    // PROPERLY ALLOCATE TEMP STRING ARRAY
                    tmp = (char**)malloc(w_arr.len * STRSIZE);
                    sort(0, (w_arr.len - 1), w_arr.ptr, tmp);
                    if(tmp != NULL)
                        free(tmp);
                    tmp = NULL;
                } else
                    add_occur(&w_arr.ptr, w_pos, line);

                free(word_buf);
                word_buf = NULL;
            }
        }
        ++line;
    }

    if(word_buf != NULL)
        free(word_buf);
    word_buf = NULL;

    if(line_buf != NULL)
        free(line_buf);
    line_buf = NULL;
}

int main(int argc, char* argv[]) {
    switch(argc) {
        case (argc == 1):
            fprintf(stderr, "error: no file given\n");
            exit(1);
        case(argc > 2):
            fprintf(stderr, "error: too many arguments\n");
            exit(1);
    }

    FILE* fp = fopen(argv[1], "r");

    word_array w_arr = fparse(fp);

    fclose(fp);

    return 0;
}
