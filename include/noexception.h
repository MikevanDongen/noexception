/* Copyright (C) 2009-2013 Francesco Nidito
 * Copyright (C) 2013-2014 Mike van Dongen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _TRY_THROW_CATCH_H_
#define _TRY_THROW_CATCH_H_

#include <setjmp.h>

/* With the original version, by Francesco Nidito, it's possible to create a
 * try/catch/finally block. Though his version has some limitations:
 * - The `finally' block was required;
 * - Exceptions could only be thrown within the same function;
 * - Exceptions not caught were simply forgotten.
 * The original version can be found on the authors website:
 * http://www.di.unipi.it/~nids/docs/longjump_try_trow_catch.html
 *
 * In this version, by Mike van Dongen, improvements were made to the original code:
 * Exceptions consist of a type and a message; The `finally' block is optional;
 * An optional catch-all block was implemented; Uncaught exceptions will be thrown
 * to the calling function; If an exception does not get caught, an error message
 * will be printed to the stderr stream and the executable will exit with code `EXIT_FAILURE'.
 * 
 * Code can be compiled using the -ansi flag for gcc, proving compatibility with ANSI C89:
 *  gcc main.c trycatch.c -o trycatch -ansi -pedantic
 * 
 * Valgrind command used for making sure there is no memory leakage:
 *  valgrind --leak-check=full --show-reachable=yes ./trycatch
 */

typedef struct trycatch_exception_struct *EXCEPTION;
struct trycatch_exception_struct
{
    unsigned int type;
    const char *msg;
    EXCEPTION previous;
};


jmp_buf * trycatch_jumper_new(void);
void trycatch_end(int exception_not_caught, EXCEPTION caught_exception);
void trycatch_exception_throw(unsigned int type, const char *msg, EXCEPTION previous);
EXCEPTION trycatch_exception_get(void);


#define TRY do{ EXCEPTION e = ((void *) 0), new_e = ((void *) 0); int value__ = setjmp(*trycatch_jumper_new()); unsigned int e_type = 0; if(value__){ new_e = trycatch_exception_get(); e_type = new_e->type; } switch(e_type){ case 0: while(1){
#define CATCH(x) break; case x: if(e) break; e = new_e; e_type = 0;
#define CATCHALL break; default: break; } } switch(e_type == 0 || e) { case 0: e = new_e; e_type = 0; while(1) {
#define FINALLY break; } default: while(1){
#define ETRY break; } } trycatch_end(e_type, e); }while(0)
#define THROW(type, msg) trycatch_exception_throw(type, msg, e)


#endif /*!_TRY_THROW_CATCH_H_*/
