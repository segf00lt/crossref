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
    word_array w_arr = mk_word_array(0);

    char* line_buf = (char*)malloc(MIN_LINE_LEN * CHARSIZE);
    line_t line = 1;

    unsigned int col = 0;
    char c_buf = '\0';
    char* str_buf = "";

    int w_pos = 0;
    word_array tmp = { .len = 0, .ptr = NULL };

    while((fgets(line_buf, MIN_LINE_LEN, fp)) != EOF) {

        while((c_buf = tolower(line_buf[col++])) != '\0') {

            if('a' <= c_buf && 'z' >= c_buf || c_buf == '-' || c_buf == '\'')
                str_buf = strcat(str_buf, &c_buf, 1);

            else if(str_buf != NULL) {
                if((w_pos = search(w_arr.ptr, 0, (w_arr.len - 1), str_buf)) < 0) {
                    append_word(&w_arr, str_buf, line);
                    tmp = mk_word_array(w_arr.len);
                    sort(0, (w_arr.len - 1), w_arr.ptr, tmp.ptr);
                    cleanup(&tmp);
                } else
                    add_occur(w_arr.ptr, w_pos, line);

                str_buf = "";
            }
        }
        if(line_buf[col] = '\n')
            ++line;
        col = 0;
        str_buf = "";
    }

    if(str_buf != NULL)
        free(str_buf);
    str_buf = NULL;

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
