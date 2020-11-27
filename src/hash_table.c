#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash_table.h"

void _insert_cell(table_t *, cell_t *);


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
        // compute the hash for the current value
        cell_t *next_cell = cell;
        while (cell != NULL) {
            next_cell = cell->next;
            cell->next = NULL;
            _insert_cell(table, cell);
            cell = next_cell;
        }
        /* while (cell != NULL) { */
        /*     insert(table, cell->val); */
        /*     cell = cell->next; */
        /* } */
    }
    free(old_cells);
}

void _insert_cell(table_t *table, cell_t *new_cell) {
    const uint32_t index = hash(new_cell->val);
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
    _insert_cell(table, new_cell); 
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

void clear(table_t *table) {
    
    for (uint32_t i = 0; i < table->total_size; ++i) {
        cell_t *cell = table->cells[i];
        cell_t *next_cell = cell;
        while (cell != NULL) {
            next_cell = cell->next;
            free(cell);
            cell = next_cell; 
        }
    }    
    free(table->cells);
    table->count = 0;
    table->total_size = 0;
}

