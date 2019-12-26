#pragma once

#include <stddef.h>

// The data type representing a vector.
struct vec_t 
{
    // The current number of elements in the vector.
    size_t len;

    // The size in bytes of each element.
    size_t elem_size;

    // The max elements that can be held without call to realloc.
    size_t capacity;

    // The data stored in the vector.
    unsigned char *data;
};

// Intialise a vec_t with given data, length and element size. Returns -1 on
// error, 0 on success.
int vec_init(struct vec_t *v, const void *data, size_t len, size_t elem_size);

// Append an element to *v. (sizeof(*elem) must be v->elem_size). Returns -1 on
// error, 0 on success.
int vec_append(struct vec_t *v, const void *elem);

// Insert an element in *v at index. (sizeof(*elem) must be v->elem_size).
// Returns -1 on error, 0 on success.
int vec_insert(struct vec_t *v, size_t index, const void *elem);

// Set an element in *v at index to *data. (sizeof(*elem) must be v->elem_size)
void vec_set(struct vec_t *v, size_t index, const void *data);

// Get an element in *v at index.
void *vec_get(struct vec_t *v, size_t index);

// Remove an element in *v at index.
void vec_remove(struct vec_t *v, size_t index);

// Free *v. Becomes a zero-capacity, zero-length, NULL data vec_t.
void vec_free(struct vec_t *v);

// Copy contents of *source to *dest. (*dest must be empty) Returns -1 on
// error, 0 on success. source->capacity isn't necessarily respected.
int vec_copy(struct vec_t *dest, const struct vec_t *source);
