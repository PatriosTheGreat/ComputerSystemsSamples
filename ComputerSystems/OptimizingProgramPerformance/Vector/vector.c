#include <stdio.h>

typedef long data_t;

typedef struct {
    long len;
    data_t *data;
} vec_rec, *vec_ptr;

#define IDENT 0
#define OP *

/* Create vector of specified length */
vec_ptr new_vec(long len)
{
    /* Allocate header structure */
    vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec));
    data_t *data = NULL;
    if (!result)
        return NULL; /* Couldn’t allocate storage */
    result->len = len;
    /* Allocate array */
    if (len > 0) {
        data = (data_t *)calloc(len, sizeof(data_t));
        if (!data) {
            free((void *) result);
            return NULL; /* Couldn’t allocate storage */
        }
    }
    /* Data will either be NULL or allocated array */
    result->data = data;
    return result;
}

void free_vec(vec_ptr v) {
    free(v->data);
    free(v);
}

/*
* Retrieve vector element and store at dest.
* Return 0 (out of bounds) or 1 (successful)
*/
int get_vec_element(vec_ptr v, long index, data_t *dest)
{
    if (index < 0 || index >= v->len)
        return 0;
    *dest = v->data[index];
    return 1;
}

/* Return length of vector */
long vec_length(vec_ptr v)
{
    return v->len;
}

data_t *get_vec_start(vec_ptr v)
{
    return v->data;
}


/* Implementation with maximum use of data abstraction */
void combine1(vec_ptr v, data_t *dest)
{
    long i;
    *dest = IDENT;
    for (i = 0; i < vec_length(v); i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

/* Move call to vec_length out of loop */
// A bit faster
void combine2(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    *dest = IDENT;
    for (i = 0; i < length; i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

/* Direct access to vector data */
void combine3(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);

    *dest = IDENT;
    for (i = 0; i < length; i++) {
        *dest = *dest OP data[i];
    }
}


/* Accumulate result in local variable */
void combine4(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    for (i = 0; i < length; i++) {
        acc = acc OP data[i];
    }
    *dest = acc;
}


void dump_vec(vec_ptr v) {
    printf("[");
    data_t *data = get_vec_start(v);
    long length = vec_length(v) - 1;
    for (int i = 0; i < length; i++) {
        printf("%ld, ", data[i]);
    }

    if (length > 0) {
        printf("%ld", data[length - 1]);
    }

    printf("]\n");
}

vec_ptr get_sample_v() {
    vec_ptr v = new_vec(3);
    v->data[0] = 2;
    v->data[1] = 3;
    v->data[2] = 5;

    return v;
}
/* 2 x 1 loop unrolling */
void combine5(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    long limit = length-1;
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=2) {
        acc = (acc OP data[i]) OP data[i+1];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
        acc = acc OP data[i];
    }

    *dest = acc;
}

/* 2 x 2 loop unrolling */
void combine6(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    long limit = length-1;
    data_t *data = get_vec_start(v);
    data_t acc0 = IDENT;
    data_t acc1 = IDENT;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=2) {
        acc0 = acc0 OP data[i];
        acc1 = acc1 OP data[i+1];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
        acc0 = acc0 OP data[i];
    }

    *dest = acc0 OP acc1;
}

/* 2 x 1a loop unrolling */
void combine7(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    long limit = length-1;
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    /* Combine 2 elements at a time */
    for (i = 0; i < limit; i+=2) {
        acc = acc OP (data[i] OP data[i+1]);
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
        acc = acc OP data[i];
    }

    *dest = acc;
}

int main() {
    {
        vec_ptr v = get_sample_v();
        dump_vec(v);
        free_vec(v);
    }

    printf("Combine3 sample\n");
    {
        vec_ptr v = get_sample_v();
        combine3(v, get_vec_start(v));
        dump_vec(v);
        free_vec(v);
    }

    printf("Combine4 sample\n");
    {
        vec_ptr v = get_sample_v();
        combine4(v, get_vec_start(v));
        dump_vec(v);
        free_vec(v);
    }

    printf("Combine3 start + 2 sample\n");
    {
        vec_ptr v = get_sample_v();
        combine3(v, get_vec_start(v)+2);
        dump_vec(v);
        free_vec(v);
    }

    printf("Combine4 start + 2 sample\n");
    {
        vec_ptr v = get_sample_v();
        combine4(v, get_vec_start(v));
        dump_vec(v);
        free_vec(v);
    }

    printf("Combine5 start\n");
    {
        vec_ptr v = get_sample_v();
        combine5(v, get_vec_start(v));
        dump_vec(v);
        free_vec(v);
    }

    printf("Combine6 start\n");
    {
        vec_ptr v = get_sample_v();
        combine6(v, get_vec_start(v));
        dump_vec(v);
        free_vec(v);
    }
    
    printf("Combine7 start\n");
    {
        vec_ptr v = get_sample_v();
        combine7(v, get_vec_start(v));
        dump_vec(v);
        free_vec(v);
    }
}