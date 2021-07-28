typedef unsigned int line_t;

typedef struct {
	int count;
	line_t* lines;
	char* data;
}word;

typedef struct {
	int len;
	word* ptr;
}word_array;

const size_t CHARSIZE = sizeof(char);
const size_t STRSIZE = sizeof(char*);
const size_t UINTSIZE = sizeof(unsigned int);
const size_t LINESIZE = sizeof(line_t);
const size_t WORDSIZE = sizeof(word);

void sort(int low, int high, word* w_ptr, word* tmp);
int search(word* w_ptr, int begin, int end, char* w);
word_array mk_word_array(int len);
void add_occur(word* w_ptr, int w_pos, line_t line);
void resize(word_array* w_arr, int increment);
void append_word(word_array* w_arr, char* w, line_t line);
void cleanup(word_array* w_arr, unsigned int flag);

void sort(int low, int high, word* w_ptr, word* tmp) {
	if(low < high) {
		inline void merge(int low, int mid, int high) {
			int low_1 = low, low_2 = mid + 1, i = low;

			for(;low_1 <= mid && low_2 <= high;++i) {
				if(strcmp(w_ptr[low_1].data, w_ptr[low_2].data) <= 0)
					tmp[i] = w_ptr[low_1++];
				else
					tmp[i] = w_ptr[low_2++];
			}
			while(low_1 <= mid)
				tmp[i++] = w_ptr[low_1++];

			while(low_2 <= high)
				tmp[i++] = w_ptr[low_2++];

			for(i = 0; i <= high;++i)
				w_ptr[i] = tmp[i];
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

word_array mk_word_array(int len) {
	if(len == 0) {
		word_array w_arr = { .len = 0, .ptr = NULL };
		return w_arr;
	}
	word* ptr = (word*)malloc(WORDSIZE * len);
	if(ptr != NULL) {
		word_array w_arr = { .len = len, .ptr = ptr };
		return w_arr;
	}
	fprintf(stderr, "error: bad alloc in mk_word_array\n");
	exit(1);
}

void add_occur(word* w_ptr, int w_pos, line_t line) {
	word* w = w_ptr + w_pos;
	w->lines = (line_t*)realloc(w->lines, ++w->count * LINESIZE);
	w->lines[w->count - 1] = line;
}

void resize(word_array* w_arr, int increment) {
	w_arr->len = w_arr->len + increment;
	w_arr->ptr = (word*)realloc(w_arr->ptr, w_arr->len * WORDSIZE);
}

void append_word(word_array* w_arr, char* w, line_t line) {
	word new_w = {
		.count = 1,
		.lines = (line_t*)malloc(LINESIZE),
		.data = NULL
	};

	if(new_w.lines == NULL) {
		fprintf(stderr, "error: bad alloc in append_word\n");
		exit(1);
	} else
		new_w.lines[0] = line;

	new_w.data = strdup(w);

	resize(w_arr, 1);
	w_arr->ptr[(w_arr->len) - 1] = new_w;
}

void cleanup(word_array* w_arr, unsigned int flag) {
	for(int i = 0; i < w_arr->len;++i) {
		line_t* l = (w_arr->ptr[i]).lines;
		char* w = (w_arr->ptr[i]).data;
		if(l != NULL && flag == 1)
			free(l);
		l = NULL;
		if(w != NULL && flag == 1)
			free(w);
		w = NULL;
	}

	if(w_arr->ptr != NULL)
		free(w_arr->ptr);
	w_arr->ptr = NULL;
	w_arr->len = 0;
}
