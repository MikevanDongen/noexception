/* Copyright (C) 2009-2013 Francesco Nidito
 * Copyright (C) 2013      Mike van Dongen
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
#include <stdlib.h>

/* With the original version, by Francesco Nidito, it's possible to create a
 * try/catch/finally block. Though his version has some limitations:
 * - The `finally' block was required;
 * - Exceptions could only be thrown within the same function;
 * - Exceptions not caught were simply forgotten.
 * The original version can be found on the authors website:
 * http://www.di.unipi.it/~nids/docs/longjump_try_trow_catch.html
 *
 * In this version, by Mike van Dongen, improvements were made to the original code:
 * The `finally' block is optional; An optional catch-all block was implemented;
 * Uncaught exceptions will be thrown to the calling function; If an exception
 * does not get caught, an error message will be printed to the stderr stream and
 * the application will be exited with code `EXIT_FAILURE'.
 */

jmp_buf * try_jmpr_new(void);
void try_jmpr_prev(int value);
void try_jmpr_remove_top(void);


#define TRY do{ int EXCEPTION = 0; int value__ = setjmp(*try_jmpr_new()); switch(value__){ case 0: while(1){
#define CATCH(x) break; case x: if(EXCEPTION) break; EXCEPTION = value__; value__ = 0;
#define CATCHALL break; default: goto catchall__; } } catchall__: switch(value__ == 0 || EXCEPTION) { case 0: EXCEPTION = value__; value__ = 0; while(1) {
#define FINALLY break; } default: while(1){
#define ETRY break; } } try_jmpr_remove_top(); if(value__){ try_jmpr_prev(value__); fprintf(stderr, "EXCEPTION (%d) NOT CAUGHT!\n", value__); exit(EXIT_FAILURE); } }while(0)
#define THROW(x) try_jmpr_prev(x)


#endif /*!_TRY_THROW_CATCH_H_*/
