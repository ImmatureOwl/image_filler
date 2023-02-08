#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* data;
    int count;
} filler_stacki_t;

static filler_stacki_t* filler_stacki_new(int capacity) 
{
    filler_stacki_t* s = (filler_stacki_t*)malloc(sizeof(filler_stacki_t));
    s->data = (int*)calloc(capacity, sizeof(int));
    s->count = 0;
    return s;
}
static void filler_stacki_free(filler_stacki_t* stack) 
{
    free(stack->data);
    free(stack);
}


static void filler_stacki_push(filler_stacki_t* stack, int value) 
{
    stack->data[stack->count++] = value;
}

static bool filler_stacki_is_empty(filler_stacki_t* stack) 
{
    return stack->count == 0;
}

static int filler_stacki_pop(filler_stacki_t* stack) 
{
    return stack->data[--stack->count];
}