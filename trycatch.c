#include <stdio.h>
#include <stdlib.h>

#include "trycatch.h"

void trycatch_exception_not_caught(int value);

/* JUMPERS */

jmp_buf * trycatch_jumper_list = NULL;
int trycatch_jumper_list_max = 1;
int trycatch_jumper_list_n = 0;

jmp_buf * trycatch_jumper_new(void)
{
    if(!trycatch_jumper_list)
    {
        trycatch_jumper_list = malloc(sizeof(jmp_buf) * trycatch_jumper_list_max);
    }
    else if(trycatch_jumper_list_n == trycatch_jumper_list_max)
    {
        jmp_buf * new_jumpers;
        trycatch_jumper_list_max <<= 1;
        new_jumpers = realloc(trycatch_jumper_list, sizeof(jmp_buf) * trycatch_jumper_list_max);
        if(!new_jumpers)
            return NULL;
        trycatch_jumper_list = new_jumpers;
    }
    return &trycatch_jumper_list[trycatch_jumper_list_n++];
}

void trycatch_jumper_free(void)
{
    if(trycatch_jumper_list)
        free(trycatch_jumper_list);
    trycatch_jumper_list = NULL;
}

void trycatch_jumper_free_if_empty(void)
{
    if(!trycatch_jumper_list_n)
        trycatch_jumper_free();
}

void trycatch_jumper_previous(int value)
{
    if(trycatch_jumper_list_n)
        longjmp(trycatch_jumper_list[trycatch_jumper_list_n - 1], value);
    
    trycatch_exception_not_caught(value);
}

void trycatch_jumper_remove_top(void)
{
    --trycatch_jumper_list_n;
}

/* EXCEPTIONS */

EXCEPTION * trycatch_exception_list = NULL;
int trycatch_exception_list_max = 1;
int trycatch_exception_list_n = 0;

int trycatch_exception_new(int type, char* msg)
{
    EXCEPTION e, previous = NULL;
    
    if(!trycatch_exception_list)
    {
        trycatch_exception_list = malloc(sizeof(EXCEPTION *) * trycatch_exception_list_max);
    }
    else if(trycatch_exception_list_n == trycatch_exception_list_max)
    {
        EXCEPTION * new_exception_list;
        trycatch_exception_list_max <<= 1;
        new_exception_list = realloc(trycatch_exception_list, sizeof(EXCEPTION *) * trycatch_exception_list_max);
        if(!new_exception_list)
            return 0;
        trycatch_exception_list = new_exception_list;
    }
    
    if(trycatch_exception_list_n)
        previous = trycatch_exception_list[trycatch_exception_list_n - 1];
    
    e = malloc(sizeof(*e));
    e->type = type;
    e->msg = msg;
    e->previous = previous;
    trycatch_exception_list[trycatch_exception_list_n++] = e;
    return trycatch_exception_list_n;
}

void trycatch_exception_list_clean(void)
{
    if(!trycatch_exception_list)
        return;
    
    while(trycatch_exception_list_n)
    {
        free(trycatch_exception_list[--trycatch_exception_list_n]);
    }
    
    free(trycatch_exception_list);
    trycatch_exception_list = NULL;
}

EXCEPTION trycatch_exception_get(int index)
{
    return trycatch_exception_list[index];
}

void trycatch_exception_not_caught(int value)
{
    EXCEPTION e = trycatch_exception_get(value - 1);
    
    trycatch_jumper_free();
    fprintf(stderr, "EXCEPTION (%d) NOT CAUGHT: %s\n", e->type, e->msg);
    trycatch_exception_list_clean();
    exit(EXIT_FAILURE);
}
