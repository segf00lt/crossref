typedef unsigned int line_t;

typedef struct {
    unsigned int count;
    line_t* lines;
    char* data;
}word;

typedef struct {
    unsigned int len;
    word* ptr;
}word_array;

const int MIN_LINE_LEN = 64;
const size_t CHARSIZE = sizeof(char);
const size_t STRSIZE = sizeof(char*);
const size_t UINTSIZE = sizeof(unsigned int);
const size_t LINESIZE = sizeof(line_t);
const size_t WORDSIZE = sizeof(word);

char** tmp_str_arr(unsigned int len);
void sort(int low, int high, word* w_ptr, char** tmp);
int search(word* w_ptr, int begin, int end, char* w);
void add_occur(word* w_ptr, int w_pos, line_t line);
void add_word(word_array* w_arr, char* w, unsigned int line);
void cleanup(word_array w_arr);

char** tmp_str_arr(unsigned int len) {
}

void sort(int low, int high, word* w_ptr, char** tmp) {
    if(low < high) {
        inline void merge(int low, int mid, int high) {
            int low_1 = low, low_2 = mid + 1, i = low;

            for(low_1, low_2, i;low_1 <= mid && low_2 <= high;++i) {
                if(strcmp(w_ptr[low_1].data, w_ptr[low_2].data) >= 0)
                    tmp[i] = w_ptr[low_1++].data;
                else
                    tmp[i] = w_ptr[low_2++].data;
            }
            while(low_1 <= mid)
                tmp[i++] = w_ptr[low_1++].data;

            while(low_2 <= high)
                tmp[i++] = w_ptr[low_2++].data;

            for(i = 0; i <= high;++i)
                w_ptr[i].data = tmp[i];
        }
        int mid = (low + high) / 2;

        sort(low, mid, w_ptr, tmp);
        sort(mid + 1, high, w_ptr, tmp);

        merge(low, mid, high);
    } else 
        return;
}

int search(word* w_ptr, int begin, int end, char* w) {
    if (end >= begin) {
        int mid = (begin + end) / 2;
        int lookup = strcmp(w_ptr[mid].data, w);

        if (lookup == 0)
            return mid;

        if (lookup > 0)
            return search(w_ptr, begin, mid - 1, w);

        return search(w_ptr, mid + 1, end, w);
    }

    return -1;
}

void add_occur(word* w_ptr, int w_pos, line_t line) {
    w_ptr->lines = (line_t*)realloc(++w_ptr->count * LINESIZE);
    w_ptr->lines[w_ptr->count - 1];
}

void add_word(word_array* w_arr, char* w, line_t line) {
    word new_w = { .count = 1, .lines = (line_t*)malloc(LINESIZE), .data = w };
    if(new_w.lines == NULL) {
        fprintf(stderr, "error: bad alloc in add_word\n");
        exit(1);
    } else
        new_w.lines[0] = line;

    w_arr->ptr = (word*)realloc(w_arr->ptr, (++w_arr->len * WORDSIZE));
    w_arr->ptr[(w_arr->len) - 1] = new_w;
}

void cleanup(word_array w_arr) {
    for(unsigned int i = 0; i < w_arr.len;++i) {
        line_t* l = (w_arr.ptr[i]).lines;
        if(l != NULL)
            free(l);
        l = NULL;
    }

    if(w_arr.ptr != NULL)
        free(w_arr.ptr);
    w_arr.ptr = NULL;
}
