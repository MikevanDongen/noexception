#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trycatch.h"

void trycatch_exception_not_caught(void);

/* GENERIC STACK */

#define TRYCATCH_STACK_DEFAULT_MAX 11

struct trycatch_stack
{
    void* list;
    size_t item_size;
    unsigned int max;
    unsigned int n;
};

typedef struct trycatch_stack* TRYCATCH_STACK;

TRYCATCH_STACK trycatch_stack_create(size_t item_size);
void trycatch_stack_enlarge(TRYCATCH_STACK stack);
void* trycatch_stack_push(TRYCATCH_STACK stack, const void* item);
void* trycatch_stack_peek(TRYCATCH_STACK stack);
int trycatch_stack_pop(TRYCATCH_STACK stack);
void trycatch_stack_destroy(TRYCATCH_STACK stack);


TRYCATCH_STACK trycatch_stack_create(size_t item_size)
{
    TRYCATCH_STACK stack = malloc(sizeof(*stack));
    
    stack->list = malloc(item_size * TRYCATCH_STACK_DEFAULT_MAX);
    stack->item_size = item_size;
    stack->max = TRYCATCH_STACK_DEFAULT_MAX;
    stack->n = 0;
    
    return stack;
}

void trycatch_stack_enlarge(TRYCATCH_STACK stack)
{
    stack->max <<= 1;
    stack->list = realloc(stack->list, stack->item_size * stack->max);
}

void* trycatch_stack_push(TRYCATCH_STACK stack, const void* item)
{
    void* item_dest;
    if(stack->n == stack->max)
        trycatch_stack_enlarge(stack);
    
    item_dest = (unsigned char*) stack->list + (stack->item_size * stack->n++);
    
    if(item)
        memcpy(item_dest, item, stack->item_size);
    
    return item_dest;
}

void* trycatch_stack_peek(TRYCATCH_STACK stack)
{
    if(stack->n)
        return (unsigned char*) stack->list + (stack->item_size * (stack->n - 1));
    
    return NULL;
}

int trycatch_stack_pop(TRYCATCH_STACK stack)
{
    if(stack->n)
        stack->n--;
    
    return stack->n;
}

void trycatch_stack_destroy(TRYCATCH_STACK stack)
{
    free(stack->list);
    free(stack);
}

/* JUMPERS */

TRYCATCH_STACK trycatch_jumper_stack = NULL;

jmp_buf * trycatch_jumper_new(void)
{
    if(!trycatch_jumper_stack)
        trycatch_jumper_stack = trycatch_stack_create(sizeof(jmp_buf));
    
    return trycatch_stack_push(trycatch_jumper_stack, NULL);
}

void trycatch_jumper_free(void)
{
    trycatch_stack_destroy(trycatch_jumper_stack);
    trycatch_jumper_stack = NULL;
}

void trycatch_jumper_free_if_empty(void)
{
    if(!trycatch_stack_peek(trycatch_jumper_stack))
        trycatch_jumper_free();
}

void trycatch_jumper_previous()
{
    void* previous = trycatch_stack_peek(trycatch_jumper_stack);
    if(previous)
        longjmp(previous, 1);
    
    trycatch_exception_not_caught();
}

void trycatch_jumper_remove_top(void)
{
    trycatch_stack_pop(trycatch_jumper_stack);
}

/* EXCEPTIONS */

TRYCATCH_STACK trycatch_exception_stack = NULL;

void trycatch_exception_new(int type, char* msg, EXCEPTION previous)
{
    EXCEPTION e;
    
    if(!trycatch_exception_stack)
        trycatch_exception_stack = trycatch_stack_create(sizeof(*e));
    
    e = trycatch_stack_push(trycatch_exception_stack, NULL);
    e->type = type;
    e->msg = msg;
    e->previous = previous;
}

void trycatch_exception_free(void)
{
    trycatch_stack_destroy(trycatch_exception_stack);
    trycatch_exception_stack = NULL;
}

void trycatch_exception_free_if_empty(void)
{
    if(trycatch_exception_stack && !trycatch_stack_peek(trycatch_exception_stack))
        trycatch_exception_free();
}

void trycatch_exception_remove_top_and_previous(void)
{
    EXCEPTION current = trycatch_stack_peek(trycatch_exception_stack);
    while(current)
    {
        current = current->previous;
        trycatch_stack_pop(trycatch_exception_stack);
    }
}

void trycatch_end(int exception_not_caught, EXCEPTION caught_exception)
{
    trycatch_jumper_remove_top();
    
    if(exception_not_caught)
        trycatch_jumper_previous();
    
    trycatch_jumper_free_if_empty();
    
    if(caught_exception)
        trycatch_exception_remove_top_and_previous();
    
    trycatch_exception_free_if_empty();
}

void trycatch_exception_throw(int type, char* msg, EXCEPTION previous)
{
    trycatch_exception_new(type, msg, previous);
    trycatch_jumper_previous();
}

EXCEPTION trycatch_exception_get(void)
{
    return trycatch_stack_peek(trycatch_exception_stack);
}

void trycatch_exception_not_caught(void)
{
    EXCEPTION e = trycatch_exception_get();
    fprintf(stderr, "EXCEPTION (%d) NOT CAUGHT: %s\n", e->type, e->msg);
    
    trycatch_exception_free();
    trycatch_jumper_free();
    exit(EXIT_FAILURE);
}
