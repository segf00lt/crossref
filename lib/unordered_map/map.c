#include <stdlib.h>
#include <string.h>
#include "map.h"

map_t*
_map_alloc(size_t cap, size_t stride) {
	map_t* m = (map_t*)malloc(sizeof(map_t));
	m->cap = cap;
	m->len = 0;
	m->stride = stride;
	m->data = (item_t*)calloc(cap, sizeof(item_t));

	return m;
}

map_t*
_map_rebalance(map_t* m) {
	if(m == NULL)
		return m;

	map_t* m_new = _map_alloc(m->len * MAP_RESIZE_FACTOR, m->stride);

	/* copy m to m_new */
	item_t* item = NULL;
	for(int i = 0; i < m->cap; ++i) {
		for(item = m->data + i; item != NULL && item->key != NULL; item = item->next)
			_map_set(&m_new, item->key, item->val);
	}

	_map_free(m);

	return m_new;
}

void
_map_free(map_t* m) {
	item_t* data = m->data;
	item_t* item = NULL;
	for(int i = 0; i < m->cap; ++i) {
		item = data + i;

		if(item->key == NULL)
			continue;

		/* free chain */
		for(item_t* cur = item->next; cur != NULL;) {
			item_t* next = cur->next;
			free(cur->key);
			if(cur->val != NULL)
				free(cur->val);

			free(cur);
			cur = next;
		}

		if(item->key != NULL)
			free(item->key);

		if(item->val != NULL)
			free(item->val);
	}

	free(m->data);
	free(m);
}

size_t
_map_hash(map_t* m, char* key) {
	size_t sum = 0;

	for(char* c = key; *c != '\0'; sum += *(c++));

	return sum % m->cap;
}

void
_map_set(map_t** mp, char* key, void* value) {
	map_t* m = *mp;
	item_t* item = m->data + _map_hash(m, key);

	size_t stride = 0;
	if(value != NULL)
		stride = m->stride;

	if(item->key != NULL) {
		item_t* prev = item;

		for(; item != NULL; prev = item, item = item->next) {
			if(strcmp(item->key, key) == 0) {
				if(item->val == NULL)
					item->val = malloc(stride);

				memcpy(item->val, value, stride);
				return;
			}
		}

		item = prev;

		item->next = (item_t*)malloc(sizeof(item_t));
		item = item->next;
		item->next = NULL;
	}

	item->key = (char*)malloc(strlen(key) + 1);
	strcpy(item->key, key);

	item->val = malloc(stride);

	memcpy(item->val, value, stride);

	++m->len;

	if(m->len >= m->cap) {
		m = _map_rebalance(m);
		*mp = m;
	}
}

int
_map_get(map_t* m, char* key, void* dest) {
	item_t* item = m->data + _map_hash(m, key);

	if(item->key == NULL)
		return 0;

	size_t stride = 0;
	if(dest != NULL)
		stride = m->stride;

	for(; item != NULL; item = item->next) {
		if(strcmp(item->key, key) == 0) {
			memcpy(dest, item->val, stride);
			return 1;
		}
	}

	return 0;
}

#ifdef MAP_ITEM_FUNCS

#include "../vector/vector.h"

char**
_map_keys(map_t* m) {
	char** keys = vector_prealloc(m->len, sizeof(char*));

	item_t* data = m->data;
	item_t* item = NULL;

	for(int i = 0; i < m->cap; ++i) {
		for(item = data + i; item != NULL && item->key != NULL; item = item->next)
			vector_push(keys, item->key);
	}

	return keys;
}

void**
_map_vals(map_t* m) {
	void** vals = vector_prealloc(m->len, m->stride);

	item_t* data = m->data;
	item_t* item = NULL;

	for(int i = 0; i < m->cap; ++i) {
		for(item = data + i; item != NULL && item->key != NULL; item = item->next)
			vector_push(vals, item->val);
	}

	return vals;
}

#endif
