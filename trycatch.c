#include "trycatch.h"

int n = 0;
int max = 11;
jmp_buf * jumpers = NULL;

jmp_buf * try_jmpr_new()
{
	if(!jumpers)
	{
    	jumpers = malloc(sizeof(jmp_buf) * max);
	}
	else if(n == max)
    {
    	max <<= 1;
    	jmp_buf * new_jumpers = realloc(jumpers, sizeof(jmp_buf) * max);
    	if(!new_jumpers)
    		return NULL;
		jumpers = new_jumpers;
	}
	return &jumpers[n++];
}

void try_jmpr_prev(int value)
{
	if(n)
		longjmp(jumpers[n - 1], value);
}

void try_jmpr_remove_top()
{
	--n;
}
