/* check_dlist_node.c

   Unit tests for dlist_node
*/

#include <check.h>

#include "dlist_node.h"

/*
// return a pointer to the nth node in the list. If n is
// the length of the list, this returns NULL, but does not error.
// Precondition: the list has at least n nodes
dlist_node* nth_node(dlist_node* head, int n);

// return a pointer to the nth previous node in the list. (That is,
// this uses `prev` pointers, not `next` pointers.) If n is
// the length of the list, this returns NULL, but does not error.
// Precondition: the list has at least n nodes
dlist_node* nth_node_prev(dlist_node* tail, int n);

// free an entire linked list. The list might be empty.
void free_dlist(dlist_node* head);

// create a linked list that stores the same elements as the given array.
// Postcondition: returns the head element
dlist_node* from_array(int n, int a[n]);

// fill in the given array with the elements from the list.
// Returns the number of elements filled in.
// Postcondition: if n is returned, the first n elements of the array
// have been copied from the linked list
int to_array(dlist_node* head, int n, int a[n]);

// gets the length of a list
int length(dlist_node* head);
*/

START_TEST(test_new_node)
{
  dlist_node *head = new_node(10, NULL, NULL); 
  
  ck_assert_int_eq(head->data, 10); //if the method worked, then 10 should be in head->data
//  ck_assert_int_eq(head->next, NULL); 
//  ck_assert_int_eq(head->prev, NULL); 
  
  free(head); //clean up after myself 
}
END_TEST

START_TEST(test_insert_after)
{
	dlist_node *head = new_node(10, NULL, NULL); 
	insert_after(head, 22); 
	
	ck_assert_int_eq(head->next->data, 22);
//	ck_assert_int_eq(head->next->prev->data, 10);
//	ck_assert_int_eq(head->next->next, 0);
//	ck_assert_int_eq(head->prev, 0);
	
	free(head->next); //clean up after myself
	free(head); 
}
END_TEST

START_TEST(test_insert_before)
{
	dlist_node *head = new_node(10, NULL, NULL); 
	insert_before(head, 8); 
	
	ck_assert_int_eq(head->prev->data, 8);
	ck_assert_int_eq(head->data, 10);
//	ck_assert_int_eq(head->prev->prev, 0);
//	ck_assert_int_eq(head->next, 0);
	
	free(head->prev); //clean up after myself
	free(head); 
}
END_TEST

START_TEST(test_delete_node)
{
	dlist_node *head = new_node(10, NULL, NULL); 
	insert_after(head, 13); 
	insert_after(head->next, 22); 
	
	delete_node(head->next);
	
	ck_assert_int_eq(head->next->data, 22);
	
	free(head->next); 
	free(head); 
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
  TCase* tc = tcase_create("dlist_node");

  // Each TCase can have many individual testing functions.
  tcase_add_test(tc, test_new_node);
  tcase_add_test(tc, test_insert_after);
  tcase_add_test(tc, test_insert_before);
  tcase_add_test(tc, test_delete_node);

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