#include <stdio.h>

#include "trycatch.h"

#define ALPHA_EXCEPTION 1
#define BETA_EXCEPTION 2
#define CHARLIE_EXCEPTION 3

void tc_sub1();
void tc_sub2();

int main()
{
    TRY
    {
        printf("1 trying..\n");
        tc_sub1();
    }
    CATCH(ALPHA_EXCEPTION)
    {
        printf("1 catching ALPHA_EXCEPTION..\n");
    }
    CATCH(BETA_EXCEPTION)
    {
        printf("1 catching BETA_EXCEPTION..\n");
    }
    FINALLY
    {
        printf("1 finally!\n");
    }
    ETRY;
    
    printf("\n");
    
    TRY
    {
        printf("1 trying..\n");
        tc_sub2();
    }
    CATCH(CHARLIE_EXCEPTION)
    {
        printf("1 catching CHARLIE_EXCEPTION..\n");
    }
    ETRY;

    printf("main continues, so all exceptions (if any) were caught!\n");
    
    return 0;
}

void tc_sub1()
{
    TRY
    {
        printf("2   trying..\n");
        tc_sub2();
        printf("2   more trying..\n");
    }
    CATCH(ALPHA_EXCEPTION)
    {
        printf("2   catching ALPHA_EXCEPTION..\n");
    }
    CATCHALL
    {
        printf("2   gotta catch(%d) em all!\n", EXCEPTION);
        THROW(ALPHA_EXCEPTION);
    }
    FINALLY
    {
        printf("2   finally!\n");
    }
    ETRY;
}

void tc_sub2()
{
    TRY
    {
        printf("3     trying..\n");
        THROW(CHARLIE_EXCEPTION);
        printf("3     won't reach this!\n");
    }
    CATCH(BETA_EXCEPTION)
    {
        printf("3     catching BETA_EXCEPTION..\n");
    }
    FINALLY
    {
        printf("3     finally!\n");
    }
    ETRY;
}
