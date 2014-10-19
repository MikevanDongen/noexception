#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "noexception.h"

#define START_TEST2(__testname) START_TEST(__testname) { unsigned int assert_in_order_counter = 0;
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

START_TEST2(test_try_throw_catch_throw_finally)
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
        THROW(BETA_EXCEPTION, "Throwing a Beta Exception!");
    }
    FINALLY
    {
        assert_in_order(3);
    }
    ETRY;
    fail("This should never be reached!");
}
END_TEST2

START_TEST2(test_try_try_throw_catch_catch)
{
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
        TRY
        {
            assert_in_order(2);
            THROW(ALPHA_EXCEPTION, "Throwing an Alpha Exception!");
        }
        CATCH(ALPHA_EXCEPTION)
        {
            assert_in_order(3);
        }
        ETRY;
        assert_in_order(4);
    }
    CATCH(ALPHA_EXCEPTION)
    {
    }
    ETRY;
    assert_in_order(5);
}
END_TEST2

START_TEST2(test_try_throw_catch_try_throw_catch_finally_finally)
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
        TRY
        {
            assert_in_order(3);
            THROW(ALPHA_EXCEPTION, "Throwing an Alpha Exception!");
        }
        CATCH(ALPHA_EXCEPTION)
        {
            assert_in_order(4);
        }
        FINALLY
        {
            assert_in_order(5);
        }
        ETRY;
        assert_in_order(6);
    }
    FINALLY
    {
        assert_in_order(7);
    }
    ETRY;
    assert_in_order(8);
}
END_TEST2

START_TEST2(test_try_throw_catch_try_throw_catch)
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

    TRY
    {
        assert_in_order(4);
        THROW(ALPHA_EXCEPTION, "Throwing an Alpha Exception!");
    }
    CATCH(ALPHA_EXCEPTION)
    {
        assert_in_order(5);
    }
    ETRY;
    assert_in_order(6);
}
END_TEST2

START_TEST2(test_try_throw_catch_compare_exceptions)
{
    const char * const message = "Throwing an Alpha Exception!";
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
        THROW(ALPHA_EXCEPTION, message);
    }
    CATCH(ALPHA_EXCEPTION)
    {
        assert_in_order(2);
        ck_assert_int_eq(e->type, ALPHA_EXCEPTION);
        ck_assert_str_eq(e->msg, message);
    }
    ETRY;
    assert_in_order(3);
}
END_TEST2

static void test_try_call_catch_finally_helper(const char *message)
{
    THROW(ALPHA_EXCEPTION, message);
}

START_TEST2(test_try_call_catch_finally)
{
    const char *message = "Throwing an Alpha Exception!";
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
        test_try_call_catch_finally_helper(message);
        fail("This should never be reached!");
    }
    CATCH(ALPHA_EXCEPTION)
    {
        assert_in_order(2);
        ck_assert_str_eq(e->msg, message);
    }
    FINALLY
    {
        assert_in_order(3);
    }
    ETRY;
    assert_in_order(4);
}
END_TEST2

static void test_try_call_catch_catchall_finally_helper(const char *message)
{
    TRY
    {
        THROW(BETA_EXCEPTION, "Throwing a Beta Exception!");
    }
    CATCH(BETA_EXCEPTION)
    {
        THROW(CHARLIE_EXCEPTION, message);
    }
    ETRY;
}

START_TEST2(test_try_call_catch_catchall_finally)
{
    const char *message = "Throwing a Charlie Exception!";
    assert_in_order(0);
    TRY
    {
        assert_in_order(1);
        test_try_call_catch_catchall_finally_helper(message);
        fail("This should never be reached!");
    }
    CATCH(CHARLIE_EXCEPTION)
    {
        assert_in_order(2);
        ck_assert_str_eq(e->msg, message);
    }
    CATCHALL
    {
        fail("This should never be reached! %d %s", e->type, e->msg);
    }
    FINALLY
    {
        assert_in_order(3);
    }
    ETRY;
    assert_in_order(4);
}
END_TEST2

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
    tcase_add_exit_test(tc_core, test_try_throw_catch_throw_finally, EXIT_FAILURE);
    tcase_add_test(tc_core, test_try_try_throw_catch_catch);
    tcase_add_test(tc_core, test_try_throw_catch_try_throw_catch_finally_finally);
    tcase_add_test(tc_core, test_try_throw_catch_try_throw_catch);
    tcase_add_test(tc_core, test_try_throw_catch_compare_exceptions);
    tcase_add_test(tc_core, test_try_call_catch_finally);
    tcase_add_test(tc_core, test_try_call_catch_catchall_finally);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s = regression_test_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
