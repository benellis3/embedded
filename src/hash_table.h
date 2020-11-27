#ifndef _HASH_TABLE
#define _HASH_TABLE

#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_TABLE_SIZE 8
#define RESIZE_THRESHOLD 0.75


typedef struct CELL {
    struct CELL *next;
    uint32_t val;
} cell_t;


typedef struct TABLE {
    uint32_t count;
    uint32_t total_size;
    cell_t **cells;
} table_t;

table_t *create_table();
void insert(table_t *, const uint32_t);
uint32_t hash(uint32_t);
bool contains(table_t *, const uint32_t);
void clear(table_t *);
#endif
