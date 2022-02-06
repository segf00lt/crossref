#ifndef VECTOR_H
#define VECTOR_H

/*
 * inspired by https://github.com/eignnx/dynarray
 */

typedef struct {
	size_t cap; /* vector capacity */
	size_t len; /* vector occupied length */
	size_t stride; /* size of type contained by vector */
} vector_header_t;

#define VECTOR_HEADER_SIZE sizeof(vector_header_t)

void* _header_to_vector(vector_header_t* h);
vector_header_t* _vector_to_header(void* v);

void* _vector_alloc(size_t cap, size_t stride);
void* _vector_resize(void* v);
void _vector_free(void* v);

int _vector_push(void** v, void* elem);
int _vector_pop(void** v, void* dest);
void _vector_cpy(void* dest, void* src);

#define VECTOR_DEFAULT_CAP 10
#define VECTOR_RESIZE_FACTOR 2

#define vector_alloc(sizeof_type) _vector_alloc(VECTOR_DEFAULT_CAP, sizeof_type)
#define vector_prealloc(cap, sizeof_type) _vector_alloc(cap, sizeof_type)
#define vector_free(v) _vector_free((void*)v)

#define vector_push(v, elem) _vector_push((void**)(&v), (void*)(&elem))
#define vector_pop(v, dest) _vector_pop((void**)(&v), (void*)(&dest))
#define vector_pop_nil(v) _vector_pop((void**)(&v), NULL)
#define vector_copy(dest, src) _vector_cpy(dest, src)

#define vector_cap(v) _vector_to_header((void*)v)->cap
#define vector_len(v) _vector_to_header((void*)v)->len
#define vector_stride(v) _vector_to_header((void*)v)->stride

#endif
