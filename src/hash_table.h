#ifndef _HASH_TABLE
#define _HASH_TABLE

#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_TABLE_SIZE 8
#define RESIZE_THRESHOLD 0.5

// Want the cell values to be the size of a
// cache line, which on this pc is 64 bytes.
#define _CELL_SIZE 4
#define EMPTY UINT32_MAX

typedef struct CELL {
    struct CELL *next;
    // although we only store uint32_t types,
    // we need to indicate a cell as being empty
    uint32_t val[_CELL_SIZE];
    uint32_t count;
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
