#include "vector.h"

#include <inttypes.h>
#include <stdio.h>
#include <malloc.h>

struct vector {
  int64_t* array;
  size_t capacity;
  size_t count;
};


struct vector* create(size_t size) {
  struct vector* v = malloc(sizeof(struct vector));
  v->array = malloc(sizeof(int64_t) * size);
  v->capacity = size;
}

int64_t get_item(struct vector* v, size_t index) {
  if (index >= v->count || v < 0) return NOT_FOUND;
  return v->array[index];
}

size_t get_capacity(struct vector* v) {
  return v->capacity;
}

size_t get_count(struct vector* v) {
  return v->count;
}

void set_capacity(struct vector* v, size_t new_capacity) {
  if(new_capacity < v->count) {
    v->count = new_capacity;
  }
  v->array = realloc(v->array, sizeof(int64_t) * new_capacity);
  v->capacity = new_capacity;
}
  
void add_back(struct vector* v, int64_t value) {
  if(v->count == v->capacity) {
    set_capacity(v, v->capacity * 2);
  }
  v->array[v->count++] = value;
}

void add_array_back(struct vector* v, int64_t* arr, size_t arr_size) {
  if (v->count + arr_size > v->capacity) {
    set_capacity(v, v->count + arr_size);
  }
  for (size_t i = 0; i < arr_size; ++i) {
    v->array[v->count++] = arr[i];
  }
}

void delete(struct vector* v) {
  free(v->array);
  free(v);
}

int64_t find_first_index_by_value(struct vector* v, int64_t value) {
    for (int64_t i = 0; i < v->count; i++) {
        if (v->array[i] == value) return i;
    }

    return NOT_FOUND;
}



void print(struct vector* v, FILE* out) {
  for(size_t i = 0; i < v->count; ++i) {
    fprintf(out, "%" PRId64 " ", v->array[i]);
  }
    fprintf(out, "\n");
}
