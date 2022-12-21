#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#define NOT_FOUND -1

struct vector;


struct vector* create(size_t size);
int64_t get_item(struct vector* v, size_t index);
size_t get_capacity(struct vector* v) ;
size_t get_count(struct vector* v);
void set_capacity(struct vector* v, size_t new_capacity);
void add_back(struct vector* v, int64_t value);
void add_array_back(struct vector* v, int64_t* arr, size_t arr_size);
void delete(struct vector* v);
void print(struct vector* v, FILE* out);
int64_t find_first_index_by_value(struct vector* v, int64_t value);

#endif
