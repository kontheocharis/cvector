#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#include "vector.h"

static int alloc_problem()
{
    fprintf(stderr, "Allocation problem!");
    return -1;
}

int vec_init(struct vec_t *v, const void *data, size_t len, size_t elem_size)
{
    if (len != 0) {
        v->data = malloc(len * elem_size);

        if (v->data == NULL)
            return alloc_problem();

        memcpy(v->data, data, len * elem_size);
    }

    v->capacity = len;
    v->len = len;
    v->elem_size = elem_size;

    return 0;
}

static int vec_resize_inc(struct vec_t *v) 
{
    if (++v->len > v->capacity) {
        v->capacity = 2 * v->len;
        v->data = realloc(v->data, v->capacity * v->elem_size);

        if (v->data == NULL)
            return alloc_problem();
    }

    return 0;
}

int vec_append(struct vec_t *v, const void *elem)
{
    int status;
    if ((status = vec_resize_inc(v)) != 0)
        return status;

    if (elem)
        memcpy((v->data + (v->len - 1) * v->elem_size), elem, v->elem_size);

    return 0;
}

int vec_insert(struct vec_t *v, size_t index, const void *elem)
{
    int status;
    if ((status = vec_resize_inc(v)) != 0)
        return status;

    memmove(v->data + index * v->elem_size,
            v->data + (index - 1) * v->elem_size,
            (v->len - index) * v->elem_size);

    if (elem)
        memcpy((v->data + index * v->elem_size), elem, v->elem_size);

    return 0;
}

void vec_set(struct vec_t *v, size_t index, const void *data)
{
    memcpy(v->data + index * v->elem_size, data, v->elem_size);
}

void vec_remove(struct vec_t *v, size_t index)
{
    memmove(v->data + index * v->elem_size,
            v->data + (index + 1) * v->elem_size,
            (v->len - index - 1) * v->elem_size);
    --v->len;
}

void *vec_get(struct vec_t *v, size_t index)
{
    return v->data + index * v->elem_size;
}

void vec_free(struct vec_t *v)
{
    free(v->data);
    v->data = NULL;
    v->capacity = 0;
    v->len = 0;
    v->elem_size = 0;
}

int vec_copy(struct vec_t *dest, const struct vec_t *source)
{
    if (source->len != 0) {
        dest->data = malloc(source->len * source->elem_size);

        if (dest->data == NULL)
            return alloc_problem();

        memcpy(dest->data, source->data, source->len * source->elem_size);
    }

    dest->capacity = source->len;
    dest->len = source->len;
    dest->elem_size = source->elem_size;

    return 0;
}
