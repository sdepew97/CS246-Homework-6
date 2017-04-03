#include "dlist_node.h"

// create (i.e., malloc) a new node
dlist_node* new_node(int data, dlist_node* next, dlist_node* prev){
	//mallocing memory for new node and creates a space in memory just large enough
	dlist_node *n = malloc(sizeof(dlist_node)); 
	
	//fill
	n->prev = prev; 
	n->next = next; 
	n->data = data; 
	
	//return value 
	return n; 
}

// insert a new node after the given one
// Precondition: Supplied node is not NULL.
void insert_after(dlist_node* n, int data){
	//create new node
	dlist_node *node = new_node(data, n->next, n); 
	
	//make necessary connections and break others
	n->next = node;
	
	if(node->next){ //node is not at the end of the list
		node->next->prev = node; 
	}
}

// insert a new node before the given one
// Precondition: Supplied node is not NULL.
void insert_before(dlist_node* n, int data){

	//could I simply do insert_after(n->prev, data); ?? or not, because the input cannot be NULL...
	
	dlist_node *node = new_node(data, n, n->prev); 
	
	//connect n to this node
	n->prev = node; 
	
	if(node->prev){
		node->prev->next = node; 
	}
}

// delete the given node   
// Precondition: Supplied node is not NULL.
void delete_node(dlist_node* n){
	dlist_node *prev = n->prev; //node before n
	dlist_node *next = n->next; //node after n
	dlist_node *to_delete = n; 
	
	//connect if next and prev are not null
	if(next)
		next->prev = prev; 
		
	if(prev)
		prev->next = next; 
	
	//free n
	free(to_delete);   
}

// return a pointer to the nth node in the list. If n is
// the length of the list, this returns NULL, but does not error.
// Precondition: the list has at least n nodes
dlist_node* nth_node(dlist_node* head, int n){
	for(int i=0; i<n; i++, head = head->next)
		;
	return head; 
}

// return a pointer to the nth previous node in the list. (That is,
// this uses `prev` pointers, not `next` pointers.) If n is
// the length of the list, this returns NULL, but does not error.
// Precondition: the list has at least n nodes
dlist_node* nth_node_prev(dlist_node* tail, int n){
	for(int i = 0; i<n; i++, tail = tail->prev)
		; 
	return tail; 
}

// free an entire linked list. The list might be empty.
void free_dlist(dlist_node* head){
	dlist_node *current = head; //second pointer
	
	while(current){ //based off of free_llist(); 
		head = current; 
		current = current->next;  
		free(head);   
	}
}

// create a linked list that stores the same elements as the given array.
// Postcondition: returns the head element
dlist_node* from_array(int n, int a[n]){
	dlist_node *return_val = NULL; //the pointer that will track the return value node
	
	for(int i=n-1; i>=0; i--){
		return_val = new_node(a[i], return_val, NULL); 
		
		if(return_val->next){ //check that the node is not the first node, so there is no next node to set a prev to!
			return_val->next->prev = return_val; 
		}
	}
	
	return return_val; 
}

// fill in the given array with the elements from the list.
// Returns the number of elements filled in.
// Postcondition: if n is returned, the first n elements of the array
// have been copied from the linked list
int to_array(dlist_node* head, int n, int a[n]){
	int num_elements = 0; 
	for(int i=0; i<n; i++){
		a[i] = head->data; 
		head = head->next;
		num_elements++;  	
	}
	return num_elements; 
}

// gets the length of a list
int length(dlist_node* head){
	int length = 0; 
	while(head){
		head = head->next; 
		length++; 
	}
	return length; 
}
