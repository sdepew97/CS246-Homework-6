/* check_dlist.c

   Unit tests for dlist
*/

#include <check.h>
#include "dlist.h"

START_TEST(test_push_pop)
{
  dlist d = dlist_new();
  
  ck_assert_int_eq(dlist_size(d), 0);

  dlist_push(d, 3);
  
  ck_assert_int_eq(dlist_peek_end(d), 3); 
  ck_assert_int_eq(dlist_peek(d), 3);
  
  dlist_push(d, 4);
  
  ck_assert_int_eq(dlist_pop(d), 4);

  dlist_push(d, 5);
  ck_assert_int_eq(dlist_peek(d), 5);
  ck_assert_int_eq(dlist_size(d), 2);
  
  dlist_push(d, 6);
  dlist_push_end(d, 8);
  ck_assert_int_eq(dlist_peek_end(d), 8);  
  dlist_push_end(d, 12); 
  dlist_push_end(d, 7); 
  
  ck_assert_int_eq(dlist_size(d), 6);
  ck_assert_int_eq(dlist_pop(d), 6);
  ck_assert_int_eq(dlist_pop_end(d), 7);
  ck_assert_int_eq(dlist_pop_end(d), 12);
  ck_assert_int_eq(dlist_size(d), 3);
  ck_assert_int_eq(dlist_pop(d), 5);
  ck_assert_int_eq(dlist_peek(d), 3);
  ck_assert_int_eq(dlist_peek_end(d), 8);
  ck_assert_int_eq(dlist_pop(d), 3);
  ck_assert_int_eq(dlist_size(d), 1);
  ck_assert_int_eq(dlist_peek(d), 8);
  ck_assert_int_eq(dlist_peek_end(d), 8);
  ck_assert_int_eq(dlist_pop(d), 8);
  ck_assert_int_eq(dlist_size(d), 0);
  
  dlist_free(d);
}
END_TEST

START_TEST(test_interior)
{
  dlist d = dlist_new();

  dlist_insert(d, 0, 3);
  dlist_insert(d, 0, 2);
  dlist_insert(d, 0, 1);
  dlist_insert(d, 1, 8);
  dlist_insert(d, 4, 10);
  dlist_insert(d, 1, 6);

  // should be [1, 6, 8, 2, 3, 10]
  ck_assert_int_eq(dlist_size(d), 6);
  ck_assert_int_eq(dlist_get(d, 0), 1);
  ck_assert_int_eq(dlist_get(d, 1), 6);
  ck_assert_int_eq(dlist_get(d, 2), 8);
  ck_assert_int_eq(dlist_get(d, 3), 2);
  ck_assert_int_eq(dlist_get(d, 4), 3);
  ck_assert_int_eq(dlist_get(d, 5), 10);

  ck_assert_int_eq(dlist_set(d, 2, 42), 8);
  ck_assert_int_eq(dlist_set(d, 5, 88), 10);
  ck_assert_int_eq(dlist_set(d, 0, 33), 1);
  
  // should be [33, 6, 42, 2, 3, 88]
  ck_assert_int_eq(dlist_remove(d, 1), 6);
  ck_assert_int_eq(dlist_size(d), 5);
  
  // should be [33, 42, 2, 3, 88]
  ck_assert_int_eq(dlist_remove(d, 0), 33);
  ck_assert_int_eq(dlist_size(d), 4);
  
  // should be [42, 2, 3, 88]
  ck_assert_int_eq(dlist_remove(d, 2), 3);
  ck_assert_int_eq(dlist_size(d), 3);
  
  // should be [42, 2, 88]
  ck_assert_int_eq(dlist_remove(d, 0), 42);
  ck_assert_int_eq(dlist_size(d), 2);
  
  // should be [2, 88]
  ck_assert_int_eq(dlist_peek(d), 2);
  
  ck_assert_int_eq(dlist_remove(d, 0), 2);
  ck_assert_int_eq(dlist_remove(d, 0), 88);
  
  dlist_free(d);
}
END_TEST


// the main() function for unit testing is fairly prescribed.
// Just copy & paste, but make sure to update the test names!
int main()
{
  // `check` allows for multiple test suites, but we'll always
  // just have one, called "main"
  Suite* s = suite_create("main");

  // Inside a suite are potentially many `TCase`s.
  TCase* tc = tcase_create("dlist");

  // Each TCase can have many individual testing functions.
  tcase_add_test(tc, test_push_pop);
  tcase_add_test(tc, test_interior);

  // Having set up the TCase, add it to the suite:
  suite_add_tcase(s, tc);

  // To run the tests, we need a runner:
  SRunner* sr = srunner_create(s);

  // This next line means that all tests run sequentially (instead
  // of at the same time). It also means that valgrind's output is
  // simpler.
  srunner_set_fork_status(sr, CK_NOFORK);

  // You can see options for running only some of the tests at
  // the documentation link above. The CK_NORMAL indicates to
  // print only failing tests.
  srunner_run_all(sr, CK_NORMAL);

  // after running, we can retrieve the number of failures
  int number_failed = srunner_ntests_failed(sr);

  // We're done now with the testsuite, so dispose of it properly
  srunner_free(sr);

  // conveniently, number_failed makes a nice exit code.
  // a non-zero answer means a failed test!
  return number_failed;
}
				    