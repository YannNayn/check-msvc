#include "../lib/libcompat.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <check.h>

START_TEST(test_pass)
{
  ck_assert_msg (1==1, "Shouldn't see this");
}
END_TEST

START_TEST(test_fail)
{
  ck_abort_msg("Failure");
}
END_TEST

/*
 * This test will fail without fork, as it will result in the
 * unit test runniner exiting early.
 */
#if defined(HAVE_FORK)
START_TEST(test_exit)
{
  exit(1);
}
END_TEST
#endif /* HAVE_FORK */

START_TEST(test_pass2)
{
  ck_assert_msg (1==1, "Shouldn't see this");
}
END_TEST

static Suite *make_s1_suite (void)
{
  Suite *s;
  TCase *tc;

  s = suite_create("S1");
  tc = tcase_create ("Core");
  suite_add_tcase(s, tc);
  tcase_add_test (tc, test_pass);
  tcase_add_test (tc, test_fail);
#if defined(HAVE_FORK)
  tcase_add_test (tc, test_exit);
#endif /* HAVE_FORK */

  return s;
}

static Suite *make_s2_suite (void)
{
  Suite *s;
  TCase *tc;

  s = suite_create("S2");
  tc = tcase_create ("Core");
  suite_add_tcase(s, tc);
  tcase_add_test (tc, test_pass2);

  return s;
}

static void run_tests (int printmode)
{
  SRunner *sr;

  sr = srunner_create(make_s1_suite());
  srunner_add_suite(sr, make_s2_suite());
  srunner_set_log(sr, "test.log");
  srunner_run_all(sr, printmode);
  srunner_free(sr);
}

static void usage(void)
{
  printf ("Usage: ex_output (CK_SILENT | CK_MINIMAL | CK_NORMAL | CK_VERBOSE)\n");
}

int main (int argc, char **argv)
{
  
  if (argc != 2) {
    usage();
    return EXIT_FAILURE;
  }

  if (strcmp (argv[1], "CK_SILENT") == 0)
    run_tests(CK_SILENT);
  else if (strcmp (argv[1], "CK_MINIMAL") == 0)
    run_tests(CK_MINIMAL);
  else if (strcmp (argv[1], "CK_NORMAL") == 0)
    run_tests(CK_NORMAL);
  else if (strcmp (argv[1], "CK_VERBOSE") == 0)
    run_tests(CK_VERBOSE);
  else {
    usage();
    return EXIT_FAILURE;
  }    
    

  return EXIT_SUCCESS;
}
  
