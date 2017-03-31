/* llist_node.h

   Prototypes for functions on a singly-linked list
*/

#ifndef LLIST_NODE_H_
#define LLIST_NODE_H_

typedef struct llist_node {
  int data;  // the data stored in this node
  struct llist_node* next; // pointer to next node
} llist_node;

// create (i.e., malloc) a new node
llist_node* new_node(int data, llist_node* next);

// insert a new node after the given one
// Precondition: Supplied node is not NULL.
void insert_after(llist_node* n, int data);

// delete the node after the given one
// Precondition: Supplied node is not NULL.
void delete_after(llist_node* n);

// return a pointer to the nth node in the list. If n is
// the length of the list, this returns NULL, but does not error.
// Precondition: the list has at least n nodes
llist_node* nth_node(llist_node* head, int n);

// free an entire linked list. The list might be empty.
void free_llist(llist_node* head);

// create a linked list that stores the same elements as the given array.
// Postcondition: returns the head element
llist_node* from_array(int n, int a[n]);

// fill in the given array with the elements from the list.
// Returns the number of elements filled in.
// Postcondition: if n is returned, the first n elements of the array
// have been copied from the linked list
int to_array(llist_node* head, int n, int a[n]);

// gets the length of a list
int length(llist_node* head);

llist_node *reverse_llist(llist_node *head); 

int last_remaining(int n, int k); 
#endif