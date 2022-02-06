#ifndef HASH_H
#define HASH_H

struct map_item {
	char* key;
	void* val;
	struct map_item* next;
};

typedef struct map_item item_t;

typedef struct {
	size_t cap;
	size_t len;
	size_t stride;
	
	item_t* data;
} map_t;

map_t* _map_alloc(size_t cap, size_t stride);
map_t* _map_rebalance(map_t* m);
void _map_free(map_t* m);
size_t _map_hash(map_t* m, char* key);

void _map_set(map_t** mp, char* key, void* value);
int _map_get(map_t* m, char* key, void* dest);

/*
 * In order to use the functions defined within
 * MAP_ITEM_FUNCS you must include vector.h
 */

#ifdef MAP_ITEM_FUNCS
char** _map_keys(map_t* m);
void** _map_vals(map_t* m);
#endif

#define MAP_DEFAULT_CAP 10
#define MAP_RESIZE_FACTOR 2

#define map_alloc(sizeof_type) _map_alloc(MAP_DEFAULT_CAP, sizeof_type)
#define map_prealloc(cap, sizeof_type) _map_alloc(cap, sizeof_type)
#define map_free(m) _map_free(m)
#define map_set(m, key, value) _map_set(&m, key, (void*)(&value))
#define map_get(m, key, dest) _map_get(m, key, (void*)(&dest))
#define map_add(m, key) _map_set(&m, key, NULL)
#define map_in(m, key) _map_get(m, key, NULL)
#define map_len(m) m->len

#ifdef MAP_ITEM_FUNCS
#define map_keys(m) _map_keys(m)
#define map_vals(m) _map_vals(m)
#endif

#endif
