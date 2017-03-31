/* llist_node.c

   A singly-linked list implementation
*/

#include <stdlib.h>
#include <stdio.h> 

#include "llist_node.h"

int main(void){
/*
	llist_node *first = new_node(10, NULL);
	insert_after(first, 12);  
	insert_after(first, 22); 
	
	printf("Length %d\n", length(first)); 
	
	llist_node *current = first; 
	
	for(int i=0; i<length(first); i++){
		printf("%d\n", current->data);
		current = current->next; 
	}
	
	first = reverse_llist(first); 
	
	printf("Length %d\n", length(first)); 
	
	current = first;
	for(int i=0; i<length(first); i++){
		printf("%d\n", current->data);
		current = current->next; 
	}
	
	free_llist(first); 
*/
	int children = 0; 
	int number = 0; 
	
	printf("Please enter the number of children in the circle: "); 
	scanf("%d", &children); 
	printf("Please enter the counting number: "); 
	scanf("%d", &number);
	printf("The last remaining child is %d.\n", last_remaining(children, number)); 
	
}

// create (i.e., malloc) a new node
llist_node* new_node(int data, llist_node* next)
{
  llist_node* n = malloc(sizeof(llist_node));
  n->data = data;
  n->next = next;
  return n;
}

// insert a new node after the given one
// Precondition: Supplied node is not NULL.
void insert_after(llist_node* n, int data)
{
  n->next = new_node(data, n->next);
}

// delete the node after the given one
// Precondition: Supplied node is not NULL.
void delete_after(llist_node* n)
{
  llist_node* delendum = n->next;
  n->next = n->next->next;
  free(delendum);
}

// return a pointer to the nth node in the list. If n is
// the length of the list, this returns NULL, but does not error.
// Precondition: the list has at least n nodes
llist_node* nth_node(llist_node* head, int n)
{
  for( ; n > 0; n--, head = head->next)
    ;
  return head;
}

// free an entire linked list. The list might be empty.
void free_llist(llist_node* head)
{
  llist_node* cur = head;
  while(cur)
  {
    head = cur;
    cur = cur->next;
    free(head);
  }
}

// create a linked list that stores the same elements as the given array.
// Postcondition: returns the head element
llist_node* from_array(int n, int a[n])
{
  llist_node* result = NULL;
  for(int i = n-1; i >= 0; i--)
  {
    result = new_node(a[i], result);
  }
  return result;
}

// fill in the given array with the elements from the list.
// Returns the number of elements filled in.
// Postcondition: if n is returned, the first n elements of the array
// have been copied from the linked list
int to_array(llist_node* head, int n, int a[n])
{
  int i;
  for(i = 0; i < n && head; i++, head = head->next)
  {
    a[i] = head->data;
  }
  return i;
}

// gets the length of a list
int length(llist_node* head)
{
  int len = 0;
  for( ; head; head = head->next, len++)
    ;
  return len;
}

llist_node *reverse_llist(llist_node *head){
	int length_value = length(head); 
	llist_node *last; 
	llist_node *prev; 
	llist_node *return_val = nth_node(head, length_value-1); 
	
	//printf("%d\n", length_value); 
	
	for(; length_value>1; length_value--){
		last = nth_node(head, length_value-1); 
		prev = nth_node(head, length_value-2); 
		last->next = prev; 
		prev->next = NULL; 
	} 
	
	return return_val; 
}

/*
	A children’s game is played like this: n children stand in a circle. One child 
	(call her child 0) starts counting by saying “1”. The child to 0’s right 
	(call him child 1) then continues the count by saying “2”. The counting continues, 
	until a child gets to the number k. The child who says k then leaves the circle. 
	Counting resumes at 1 with the child to the right of the child who just left. 
	Once again, the child who counts “k” leaves. This process continues until only one 
	child is left.
*/


int last_remaining(int n, int k){
	llist_node *head = new_node(0, NULL);
	llist_node *current = head; 
	 
	//create the children and label them with numbers
	for(int i=1; i<n; i++){
		insert_after(current, i);
		current = current -> next;   
	}
	
	//connect to first child or create a circular llinked list
	current->next = head; 
	current = head; 
	
	//printf("%d \n", current->data);
	
	llist_node *remove = head; //value after to remove
	
	while(n>1){
		for(int i=0; i<k-2; i++){ 
			remove = remove->next; 
		}
		
		//printf("%d \n", remove->data);

		delete_after(remove); 
		remove = remove->next;
		n--; 
	}
	
	int val = remove->data;
	
	free(remove); 
	
	return val;  
}
