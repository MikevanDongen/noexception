#include <stdio.h>

#include "noexception.h"

#define ALPHA_EXCEPTION 1
#define BETA_EXCEPTION 2
#define CHARLIE_EXCEPTION 3

void tc_sub1();
void tc_sub2();

int main()
{
    TRY
    {
        printf("trying..\n");
        THROW(BETA_EXCEPTION, "B!");
    }
    CATCH(BETA_EXCEPTION)
    {
        printf("catching BETA_EXCEPTION: %s\n", e->msg);
        TRY
        {
            printf("trying..\n");
            THROW(CHARLIE_EXCEPTION, "C!");
            printf("won't reach this!\n");
        }
        CATCH(CHARLIE_EXCEPTION)
        {
            printf("catching C_EXCEPTION: %s\n", e->msg);
        }
        FINALLY
        {
            printf("finally\n");
        }
        ETRY;
        printf("reach this!\n");
    }
    FINALLY
    {
        printf("cleaning up!\n");
    }
    ETRY;
    
    printf("\n");
    
    TRY
    {
        printf("trying..\n");
        tc_sub1();
    }
    CATCH(ALPHA_EXCEPTION)
    {
        printf("catching ALPHA_EXCEPTION: %s (%s)\n", e->msg, e->previous ? e->previous->msg : "no rethrow");
    }
    CATCH(BETA_EXCEPTION)
    {
        printf("catching BETA_EXCEPTION..\n");
    }
    FINALLY
    {
        printf("cleaning up!\n");
    }
    ETRY;
    
    printf("\n");
    
    TRY
    {
        printf("trying..\n");
        tc_sub2();
    }
    CATCH(CHARLIE_EXCEPTION)
    {
        printf("catching CHARLIE_EXCEPTION: %s\n", e->msg);
        TRY
        {
            printf("trying something else..\n");
            THROW(CHARLIE_EXCEPTION, "something went bad with Charlie!");
        }
        CATCHALL
        {
            printf("gotta catch(%d) em all: %s (%s)\n", e->type, e->msg, e->previous ? e->previous->msg : "no rethrow");
        }
        ETRY;
        printf("same catching CHARLIE_EXCEPTION: %s\n", e->msg);
    }
    FINALLY
    {
        printf("cleaning up!\n");
    }
    ETRY;
    
    printf("\n");
    printf("main continues, so all exceptions (if any) were caught!\n");
    
    return 0;
}

void tc_sub1()
{
    TRY
    {
        printf("trying..\n");
        tc_sub2();
        printf("more trying..\n");
    }
    CATCH(ALPHA_EXCEPTION)
    {
        printf("catching ALPHA_EXCEPTION: %s\n", e->msg);
    }
    CATCHALL
    {
        printf("gotta catch(%d) em all: %s\n", e->type, e->msg);
        THROW(ALPHA_EXCEPTION, "the Alpha team is here!");
    }
    FINALLY
    {
        printf("cleaning up!\n");
    }
    ETRY;
}

void tc_sub2()
{
    TRY
    {
        printf("trying..\n");
        THROW(CHARLIE_EXCEPTION, "Charlie is down!");
        printf("won't reach this!\n");
    }
    CATCH(BETA_EXCEPTION)
    {
        printf("catching BETA_EXCEPTION: %s\n", e->msg);
    }
    FINALLY
    {
        printf("cleaning up!\n");
    }
    ETRY;
}
