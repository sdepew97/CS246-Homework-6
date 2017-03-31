#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

int main(void){
/*
	llist_node *a = new_node(10, NULL); 
	//llist_node *b = new_node(12, NULL); 
	insert_after(a, 12); 
	printf("%d\n", nth(a, 1)); 
	return 0; 
	*/
	
	int a[2] = {12, 4}; 
	llist_node *head = from_array(2, a);
	printf("%d\n", head->data); 
	printf("%d\n", head->next->data); 
}

// create (i.e., malloc) a new node
llist_node* new_node(int data, llist_node* next){
	llist_node *new = malloc(sizeof(llist_node)); //create a spot in memory large enough for a node and return a pointer to it
	new->data = data; //put the data in the node
	new->next = next; //set the next value for the node
	return new; //return the node pointer
}

// insert a new node after the given one
// Precondition: Supplied node is not NULL.
void insert_after(llist_node* n, int data){
	n->next = new_node(data, n->next); //create a new node that points to what next points to also and then set that to be n's next
}

// delete the node after the given one
// Precondition: Supplied node is not NULL.
void delete_after(llist_node* n){
	llist_node *delnum = n->next; //sets the value to delete to the node to be deleted
	n->next = n->next->next; //just this line creates a memory leak!
	free(delnum); //frees the memory pointed to by delnum
}

// return the nth element (0-indexed) of the linked list
// Precondition: the list has enough nodes
int nth(llist_node* head, int n){	
	for(int i=0; i<n; i++){
		head = head->next; 
	}
	
	return head->data; 
}

// return a pointer to the nth node in the list. If n is
// the length of the list, this returns NULL, but does not error.
// Precondition: the list has at least n nodes
llist_node* nth_node(llist_node* head, int n){
	for(int i=0; i<n; i++){
		head = head->next; 
	}
	
	return head; 
}

// free an entire linked list. The list might be empty.
void free_llist(llist_node* head){
	llist_node *current = head; 
	
	while(current){ //while it is not null/empty
		head = current; 
		current = current->next; 
		free(head); 
	}
}

// create a linked list that stores the same elements as the given array.
// Postcondition: returns the head element
llist_node* from_array(int n, int a[n]){
	llist_node *head = NULL; 
	for(int i=n-1; i>=0; i--){
		head = new_node(a[i], head); 
	}
	return head; 
}

// fill in the given array with the elements from the list.
// Returns the number of elements filled in.
// Postcondition: if n is returned, the first n elements of the array
// have been copied from the linked list
int to_array(llist_node* head, int n, int a[n]){
	int i = 0; 
	while(head && i<n){
		a[i] = head->data; 
		head = head->next; 
		i++; 
	}
	return i; 
}

// gets the length of a list
int length(llist_node* head){
	int length; 
	for(length=0; head; length++, head = head->next)
		; 
	return length; 
}