#include "dlist_node.h"

// create (i.e., malloc) a new node
dlist_node* new_node(int data, dlist_node* next, dlist_node* prev){
	//mallocing memory for new node and creates a space in memory just large enough
	dlist_node *n = malloc(sizeof(dlist_node)); 
	
	//fill with input values
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
	
	//check to see if node is not at the end of the list, if it is then there is no node->next; it is NULL
	if(node->next){ 
		node->next->prev = node; 
	}
}

// insert a new node before the given one
// Precondition: Supplied node is not NULL.
void insert_before(dlist_node* n, int data){
	//create new node
	dlist_node *node = new_node(data, n, n->prev); 
	
	//connect the input node, n, to the new node
	n->prev = node; 
	
	//check to see if the new node is the first node or if the node before it needs to connect to it 
	if(node->prev){
		node->prev->next = node; 
	}
}

// delete the given node   
// Precondition: Supplied node is not NULL.
void delete_node(dlist_node* n){
	dlist_node *prev = n->prev; //node before n
	dlist_node *next = n->next; //node after n
	dlist_node *to_delete = n; //additional pointer to n
	
	//connect if next and prev are not null/making connections to close gap being left by deleting n
	if(next)
		next->prev = prev; 
		
	if(prev)
		prev->next = next; 
	
	//free n in order to prevent memory leaks
	free(to_delete);   
}

// return a pointer to the nth node in the list. If n is
// the length of the list, this returns NULL, but does not error.
// Precondition: the list has at least n nodes
dlist_node* nth_node(dlist_node* head, int n){
	//iterate through the nodes until you reach the nth one
	for(int i=0; i<n; i++, head = head->next)
		;
	
	//return a pointer to the nth node
	return head; 
}

// return a pointer to the nth previous node in the list. (That is,
// this uses `prev` pointers, not `next` pointers.) If n is
// the length of the list, this returns NULL, but does not error.
// Precondition: the list has at least n nodes
dlist_node* nth_node_prev(dlist_node* tail, int n){
	//iterate through the nth previous node
	for(int i = 0; i<n; i++, tail = tail->prev)
		; 
	
	//return a pointer to the nth previous node
	return tail; 
}

// free an entire linked list. The list might be empty.
void free_dlist(dlist_node* head){
	//second pointer to keep track of current node, so that when head is freed you do not worry about not pointing to valid node/don't lose any nodes
	dlist_node *current = head;  
	
	//based off of free_llist(); this while loop iterates through all the nodes and deletes until the pointer is NULL
	while(current){  
		head = current; 
		current = current->next;  
		free(head);   
	}
}

// create a linked list that stores the same elements as the given array.
// Postcondition: returns the head element
dlist_node* from_array(int n, int a[n]){
	//the pointer that will track the return value node
	dlist_node *return_val = NULL; 
	
	//for loop that fills the linked list
	for(int i=n-1; i>=0; i--){
		return_val = new_node(a[i], return_val, NULL); 
		
		//check that the node is not the first node, so there is no next node to set a prev to!
		if(return_val->next){ 
			return_val->next->prev = return_val; 
		}
	}
	
	//return a pointer to the linked list filled with the array values
	return return_val; 
}

// fill in the given array with the elements from the list.
// Returns the number of elements filled in.
// Postcondition: if n is returned, the first n elements of the array
// have been copied from the linked list
int to_array(dlist_node* head, int n, int a[n]){
	//int variable to keep track of number of elements "seen" or put into the array of size n
	int num_elements = 0; 
	
	//adds the elements from the linked list to the array and, if the linked list is shorter than n, ensures the head is not NULL as well
	for(int i=0; i<n && head; i++){
		a[i] = head->data; 
		head = head->next;
		num_elements++;  	
	}
	
	//returns the number of elements added
	return num_elements; 
}

// gets the length of a list
int length(dlist_node* head){
	//length value
	int length = 0; 
	
	//while loop that iterates through all the nodes in the list
	while(head){
		head = head->next; 
		length++; 
	}
	
	//return value of the length 
	return length; 
}
