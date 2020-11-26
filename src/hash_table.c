#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

void insert(table_t *, const uint32_t);


table_t * create_table() {
    table_t *table = malloc(sizeof(table));
    table->cells = NULL;
    table->total_size = 0;
    table->count = 0;
    return table;
}

/**
 * The below function is from the hash-prospector project:
 * https://github.com/skeeto/hash-prospector
 */
uint32_t hash(uint32_t x) {
    x ^= x >> 15;
    x *= UINT32_C(0x2c1b3c6d);
    x ^= x >> 12;
    x *= UINT32_C(0x297a2d39);
    x ^= x >> 15;
    return x;
}

void _initialise_table(table_t *table) {
    // make sure to 0 initialise the cells so that we do not 
    // think there are more cells because of a non-null next pointer
    cell_t **cells = calloc(DEFAULT_TABLE_SIZE, sizeof(cell_t));
    if (cells == NULL) {
        return;
    }
    table->cells = cells;
    table->total_size = DEFAULT_TABLE_SIZE;
}

/**
 * Doubles the size of the current hash table
 * and makes sure to copy the linked list pointers over
 * from the current array.
 */
void _resize(table_t *table) {
    cell_t **new_cells = calloc(2 * table->total_size, sizeof(cell_t));
    cell_t **old_cells = table->cells;
    table->cells = new_cells;
    table->total_size = 2 * table->total_size;
    table->count = 0;
    for (int i = 0; i < table->total_size; ++i) {
        cell_t *cell = old_cells[i];
        while (cell != NULL) {
            insert(table, cell->val);
            cell = cell->next;
        }
    }
    free(old_cells);
}

void insert(table_t *table, const uint32_t element) {
    if (table->total_size == 0) {
        _initialise_table(table);
    }
    else if (((double) table->count) / ((double) table->total_size) > RESIZE_THRESHOLD) {
        _resize(table);
    }
    cell_t *new_cell = malloc(sizeof(cell_t));
    if (new_cell == NULL) {
        return;
    }
    new_cell->val = element;
    new_cell->next = NULL;
    
    const uint32_t index = hash(element);
    cell_t *cell = table->cells[index % table->total_size];
    cell_t *prev = cell;
    while (cell != NULL) {
        prev = cell;
        cell = cell->next;
    }
    if (prev != NULL) {
        prev->next = new_cell;
    }
    else {
        table->cells[index % table->total_size] = new_cell;
    }
    table->count++;
}

bool contains(table_t *table, const uint32_t element) {
    const uint32_t index = hash(element);
    cell_t *cell = table->cells[index % table->total_size];
    while (cell != NULL) {
        if (cell->val == element) {
            return true;
        }
        cell = cell->next;
    }
    return false; 
}

int main() {

    table_t *table = create_table();
    const uint32_t max_value = 100000000;
    clock_t start = clock();
    for (uint32_t i = 0; i < max_value; ++i) {
        insert(table, i);
    }
    clock_t end = clock();
    printf("Time for %d inserts: %f\n", max_value, ((double) (end - start)) / CLOCKS_PER_SEC);
    
    start = clock();
    for (uint32_t i = 0; i < max_value; ++i) {
        bool val = contains(table, i);
        if (!val) {
            printf("Error: Expected to find %d but didn't\n", i);
            return -1;
        }
    }
    end = clock();
    printf("Time for %d reads: %f\n", max_value, ((double) (end - start)) / CLOCKS_PER_SEC);
}
