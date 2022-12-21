#ifndef MATH_LOG_1_HASH_MAP_H
#define MATH_LOG_1_HASH_MAP_H

#include <stdlib.h>
#include <stdint.h>

#define NOT_FOUND_CODE -1

//Map<String, Integer>
typedef struct Ht_item Ht_item;

// Define the Hash Table Item here
struct Ht_item {
    char* key;
    char* value;
};

typedef struct HashTable HashTable;

// Define the Hash Table here
struct HashTable {
    // Contains an array of pointers
    // to items
    Ht_item** items;
    int size;
    int count;
};


HashTable* create_table(int size);

void ht_insert_int(HashTable* table, char* key, int64_t value);

int64_t ht_search_int(HashTable* table, char* key);

void print_table(HashTable* table);
#endif
