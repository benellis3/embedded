#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash_table.h"

#define ORDERED_MAX_VALUE 1000000

void time_ordered_insert(table_t *table) {
    clock_t start = clock();
    for (uint32_t i = 0; i < ORDERED_MAX_VALUE; ++i) {
        insert(table, i);
    }
    clock_t end = clock();
    printf("Time for %d inserts: %f\n", ORDERED_MAX_VALUE, ((double) (end - start)) / CLOCKS_PER_SEC);
}

void time_ordered_read(table_t *table) {
    clock_t start = clock();
    for (uint32_t i = 0; i < ORDERED_MAX_VALUE; ++i) {
        bool val = contains(table, i);
        if (!val) {
            printf("Error: Expected to find %d but didn't\n", i);
            return;
        }
    }
    clock_t end = clock();
    printf("Time for %d reads: %f\n", ORDERED_MAX_VALUE, ((double) (end - start)) / CLOCKS_PER_SEC);
}

void time_random(table_t *table, const long reads, const uint32_t writes) {
    // 1kB of integers
    uint32_t *values = malloc(writes * sizeof(uint32_t));
    uint32_t count = 0;
    clock_t start = clock();
    for (uint32_t i = 0; i < writes; ++i) {
        uint32_t number = random() % UINT32_MAX;
        values[i] = number;
        insert(table, number);
    }

    for (long i = 0; i < reads; ++i) {
        if (random() & 0x1) {
            if (!contains(table, values[random() % writes])) {
                printf("Expected to find value but didn't\n");
            }
        }
        else if (contains(table, random() % UINT32_MAX)) {
            count++;
        }
    }
    clock_t end = clock();
    printf("Time for %d writes and %ld reads: %f\n", writes, reads, ((double) (end - start)) / CLOCKS_PER_SEC);
    printf("Had %d occurrences of numbers where we didn't expect them\n", count);
}

int main() {

    table_t *table = create_table();
    printf("Testing Balanced ordered number insert!\n");
    printf("=========================================\n");
    time_ordered_insert(table); 
    time_ordered_read(table);
    clear(table);
    printf("Testing a read-heavy workload!\n");
    printf("================================\n");
    time_random(table, 10000000, 256);
    printf("Testing a write-heavy workload!\n");
    printf("=================================\n");
    time_random(table, 256, 1000000);
}
