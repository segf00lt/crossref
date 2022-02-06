#include <stdlib.h>
#include <string.h>
#include "vector.h"

void*
_header_to_vector(vector_header_t* h) {
	return (void*)(h + 1);
}

vector_header_t*
_vector_to_header(void* v) {
	return (vector_header_t*)v - 1;
}

void*
_vector_alloc(size_t cap, size_t stride) {
	size_t vector_size = cap * stride;
	vector_header_t* h = (vector_header_t*)malloc(VECTOR_HEADER_SIZE + vector_size);

	h->cap = cap;
	h->len = 0;
	h->stride = stride;

	return _header_to_vector(h);
}

void*
_vector_resize(void* v) {
	vector_header_t* h = _vector_to_header(v);
	size_t newcap = VECTOR_HEADER_SIZE + (h->cap * h->stride * VECTOR_RESIZE_FACTOR);
	h = (vector_header_t*)realloc(h, newcap);
	h->cap = newcap;

	return _header_to_vector(h);
}

void
_vector_free(void* v) {
	free(_vector_to_header(v));
}

int
_vector_push(void** v, void* elem) {
	if(elem == NULL)
		return 0;

	vector_header_t* h = _vector_to_header(*v);

	if(h->len == h->cap) {
		*v = _vector_resize(*v);
		h = _vector_to_header(*v);
	}

	size_t offset = h->len * h->stride;
	memcpy((unsigned char*)(*v) + offset, elem, h->stride);

	++h->len;

	return 1;
}

int
_vector_pop(void** v, void* dest) {
	vector_header_t* h = _vector_to_header(*v);

	if(h->len == 0)
		return 0;

	size_t offset = h->len * h->stride;
	if(dest != NULL)
		memcpy(dest, (unsigned char*)(*v) + offset, h->stride);

	--h->len;

	return 1;
}

void
_vector_cpy(void* dest, void* src) {
	memcpy(dest, src, vector_cap(src) * vector_stride(src));
}
