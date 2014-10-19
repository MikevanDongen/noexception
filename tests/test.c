#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "noexception.h"

#define START_TEST2(name) START_TEST(name) { unsigned int assert_in_order_counter = 0;
#define END_TEST2 } END_TEST

#define assert_in_order(n) (assert_in_order_counter++ == n) ? \
    mark_point() : \
    _fail_unless(0, __FILE__, __LINE__, "Assertion is out of order!", NULL)

#define ALPHA_EXCEPTION 1
#define BETA_EXCEPTION 2
#define CHARLIE_EXCEPTION 3

const EXCEPTION e = NULL;

START_TEST2(test_throw)
{
    THROW(ALPHA_EXCEPTION, "Throwing an Alpha Exception!");
}
END_TEST2

START_TEST2(test_try)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
    }
    ETRY;
    assert_in_order(2);
}
END_TEST2

START_TEST2(test_try_catch)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
    }
    CATCH(ALPHA_EXCEPTION)
    {
    }
    ETRY;
    assert_in_order(2);
}
END_TEST2

START_TEST2(test_try_catch_catch)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
    }
    CATCH(ALPHA_EXCEPTION)
    {
    }
    CATCH(BETA_EXCEPTION)
    {
    }
    ETRY;
    assert_in_order(2);
}
END_TEST2

START_TEST2(test_try_finally)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
    }
    FINALLY
    {
        assert_in_order(2);
    }
    ETRY;
    assert_in_order(3);
}
END_TEST2

START_TEST2(test_try_catch_finally)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
    }
    CATCH(ALPHA_EXCEPTION)
    {
    }
    FINALLY
    {
        assert_in_order(2);
    }
    ETRY;
    assert_in_order(3);
}
END_TEST2

START_TEST2(test_try_catch_catch_finally)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
    }
    CATCH(ALPHA_EXCEPTION)
    {
    }
    CATCH(BETA_EXCEPTION)
    {
    }
    FINALLY
    {
        assert_in_order(2);
    }
    ETRY;
    assert_in_order(3);
}
END_TEST2

START_TEST2(test_try_catchall)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
    }
    CATCHALL
    {
    }
    ETRY;
    assert_in_order(2);
}
END_TEST2

START_TEST2(test_try_throw_catch)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
        THROW(ALPHA_EXCEPTION, "Throwing an Alpha Exception!");
    }
    CATCH(ALPHA_EXCEPTION)
    {
        assert_in_order(2);
    }
    ETRY;
    assert_in_order(3);
}
END_TEST2

START_TEST2(test_try_throw_catch_catch)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
        THROW(BETA_EXCEPTION, "Throwing a Beta Exception!");
    }
    CATCH(ALPHA_EXCEPTION)
    {
    }
    CATCH(BETA_EXCEPTION)
    {
        assert_in_order(2);
    }
    ETRY;
    assert_in_order(3);
}
END_TEST2

START_TEST2(test_try_throw_catch_finally)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
        THROW(ALPHA_EXCEPTION, "Throwing an Alpha Exception!");
    }
    CATCH(ALPHA_EXCEPTION)
    {
        assert_in_order(2);
    }
    FINALLY
    {
        assert_in_order(3);
    }
    ETRY;
    assert_in_order(4);
}
END_TEST2

START_TEST2(test_try_throw_catch_catch_finally)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
        THROW(BETA_EXCEPTION, "Throwing a Beta Exception!");
    }
    CATCH(ALPHA_EXCEPTION)
    {
    }
    CATCH(BETA_EXCEPTION)
    {
        assert_in_order(2);
    }
    FINALLY
    {
        assert_in_order(3);
    }
    ETRY;
    assert_in_order(4);
}
END_TEST2

START_TEST2(test_try_throw_catchall)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
        THROW(ALPHA_EXCEPTION, "Throwing an Alpha Exception!");
    }
    CATCHALL
    {
        assert_in_order(2);
    }
    ETRY;
    assert_in_order(3);
}
END_TEST2

START_TEST2(test_try_throw_catchall_finally)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
        THROW(ALPHA_EXCEPTION, "Throwing an Alpha Exception!");
    }
    CATCHALL
    {
        assert_in_order(2);
    }
    FINALLY
    {
        assert_in_order(3);
    }
    ETRY;
    assert_in_order(4);
}
END_TEST2

START_TEST2(test_try_throw_catch_catchall)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
        THROW(ALPHA_EXCEPTION, "Throwing an Alpha Exception!");
    }
    CATCH(ALPHA_EXCEPTION)
    {
        assert_in_order(2);
    }
    CATCHALL
    {
    }
    ETRY;
    assert_in_order(3);
}
END_TEST2

START_TEST2(test_try_throw_catchall_catch)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
        THROW(ALPHA_EXCEPTION, "Throwing an Alpha Exception!");
    }
    CATCHALL
    {
        assert_in_order(2);
    }
    CATCH(ALPHA_EXCEPTION)
    {
    }
    ETRY;
    assert_in_order(3);
}
END_TEST2

/*
Try [throw] [catch | catchall]* [throw] [finally]
Nested
 */

Suite * regression_test_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Regression testing");

    /* Core test case */
    tc_core = tcase_create("");

    tcase_add_exit_test(tc_core, test_throw, EXIT_FAILURE);
    tcase_add_test(tc_core, test_try);
    tcase_add_test(tc_core, test_try_catch);
    tcase_add_test(tc_core, test_try_catch_catch);
    tcase_add_test(tc_core, test_try_finally);
    tcase_add_test(tc_core, test_try_catch_finally);
    tcase_add_test(tc_core, test_try_catch_catch_finally);
    tcase_add_test(tc_core, test_try_throw_catch);
    tcase_add_test(tc_core, test_try_throw_catch_catch);
    tcase_add_test(tc_core, test_try_throw_catch_finally);
    tcase_add_test(tc_core, test_try_throw_catch_catch_finally);
    tcase_add_test(tc_core, test_try_throw_catchall);
    tcase_add_test(tc_core, test_try_throw_catchall_finally);
    tcase_add_test(tc_core, test_try_throw_catch_catchall);
    tcase_add_test(tc_core, test_try_throw_catchall_catch);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = regression_test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return number_failed != 0;
}





int main_2()
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
        /*tc_sub1();*/
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
        /*tc_sub2();*/
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

