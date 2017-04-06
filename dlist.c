#include "dlist.h"
#include "dlist_node.h"

typedef struct dlist_record {
	//pointer to the first node in the dlist
  	dlist_node *head;
  	//pointer to the last node in the dlist 
  	dlist_node *tail;
  	// number of nodes in the dlist
  	int size;  
} dlist_record;

// An abstract type for sequences
typedef struct dlist_record* dlist;

// return an empty dlist. Make sure to call dlist_free when you're done
// with it.
dlist dlist_new(){
	//malloc enough memory for the dlist
	dlist d = malloc(sizeof(dlist_record)); 
	
	//fill
	d->size = 0; 
	d->head = NULL;
	d->tail = NULL;  
	
	//return pointer to dlist_record or dlist (since we used typedef)
	return d; 
}

// returns the number of elements in the dlist. Runs in constant time.
int dlist_size(dlist l){
	//get the size field from the struct and return it as the size of the dlist
	return l->size; 
}

// appends a new element to the beginning of the dlist. Runs in constant time.
void dlist_push(dlist l, int elt){
	//add a new node to the head of the list and have the head field point to this new node
	l->head = new_node(elt, l->head, NULL); 
	
	//if this element is not the first element/has a node after it
	if(l->head->next != NULL){ 
		l->head->next->prev = l->head; 
	}
	
	//if the tail doesn't point to anything, which makes this the first element of the list, then tail should change 
	if(l->tail == NULL){ 
		l->tail = l->head; 
	}
	
	//increment the size, since we added an element
	l->size++; 
}

// removes and returns the first element in the dlist. Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_pop(dlist l){
	//create a pointer to the old head value, so it can be freed, and the return_val for the value of the data currently in that node
	dlist_node *old_head = l->head; 
	int return_val = old_head->data;
	
	//check if we are popping the only element on the list and update tail; only case where tail needs to be updated
	if(l->head == l->tail){ 
		//the list is going to be empty
		l->tail = NULL;  
	} 
	
	//will be NULL if and only if head only node and set the value of the head/update it 
	l->head = old_head->next; 
	
	//if the head is not NULL
	if(l->head){ 
		//nothing to point to for prev, anymore since this node is now the only node in the list
		l->head->prev = NULL; 
	}
	
	//decrement the size, since we deleted 
	l->size--; 
	
	//frees the memory for the old head value, since this was originally malloced
	free(old_head);  
	
	//return the data value that was in the old head 
	return return_val; 
}

// returns the first element in the dlist, without changing the dlist.
// Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_peek(dlist l){
	//returns the data from the dlist node pointed to by head
	return l->head->data; 
}

// appends a new element to the end of the dlist. Runs in constant time.
void dlist_push_end(dlist l, int elt){
	//create the new tail node and have the field point to the tail
	l->tail = new_node(elt, NULL, l->tail); 
	
	//the tail was updated and so the node pointed to needs to link to the one before it
	if(l->tail->prev != NULL){  
		l->tail->prev->next = l->tail; 
	}
	
	//if the head doesn't currently point to anything, which makes this the first element of the list, then head should change 
	if(l->head == NULL){ 
		l->head = l->tail; 
	}
	
	//increase the size, since a new node was added
	l->size++;
}

// removes and returns the last element in the dlist. Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_pop_end(dlist l){
	//store the value of the old tail and store the data value that is in old tail 
	dlist_node *old_tail = l->tail;
	int return_val = old_tail->data; 
	
	//checking if there is only one node or if there are more if there is only one node, then head should be NULL after tail node deleted
	if(l->tail == l->head){ 
		l->head = NULL; 
	}
	
	//reset tail and make necessary connections 
	l->tail = old_tail->prev; 
	
	//if the tail is not NULL, then we need to set the tail's next value to NULL, since tail is last node 
	if(l->tail){ 
		//set tail's next pointer to NULL
		l->tail->next = NULL; 
	}
	//free the old tail
	free(old_tail); 
	
	//decrement the size
	l->size--; 
	
	//return the value of the data stored in the old tail 
	return return_val; 
}

// returns the last element in the dlist, without changing the dlist.
// Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_peek_end(dlist l){
	//return the data value stored in the tail
	return l->tail->data; 
}

// adds a new element into the dlist, after n existing elements.
// Traverses from whichever side of the dlist is closer.
// precondition: the list has at least n elements
void dlist_insert(dlist l, int n, int elt){
	//if an element is inserted at the 0th location, this element should be pushed to the head
	if(n==0){
		dlist_push(l, elt); 
	}
	
	//if an element is inserted at n, then the element should be pushed at the end
	else if(n==l->size){
		dlist_push_end(l, elt); 
	}
	
	//if the element is in the first half of the list, then the element's insertion location is closer to the head than the tail
	else if(n<=(l->size)/2){
		dlist_node *target = l->head; 
		for(int i=0; i<n-1; i++){
			target = target->next; 
		}
		insert_after(target, elt);
		l->size++;  
	}
	
	//else the element is in the last half of the list, then the element's insertion location is closer to the tail than the head
	else{ 
		dlist_node *target = l->tail; 
		
		for(int i=0; i<l->size-n-1; i++){
			target = target->prev; 
		}
		insert_after(target, elt); 
		l->size++; 
	}

}

// retrieves the nth element of the dlist.
// Traverses from whichever side of the dlist is closer.
// precondition: the list has at least (n+1) elements
int dlist_get(dlist l, int n){
	//if the nth element is 0, then the head should be peeked 
	if(n==0){
		return dlist_peek(l); 
	}
	
	//if the nth element is n+1 = size, then the tail should be peeked 
	else if(n+1==l->size){
		return dlist_peek_end(l); 
	}
	
	//if the element is in the first half of the list, then the head is closer 
	else if(n<=((l->size)/2)-1){
		dlist_node *head = l->head; 
		
		for(int i=0; i<n; i++){
			head = head->next; 
		}
		return head->data;  	
	}
	
	//if the element is in the second half of the list, then the tail is closer 
	else{
		dlist_node *tail = l->tail; 
		
		for(int i=0; i<l->size-n-1; i++){
			tail = tail->prev; 
		}
		return tail->data; 
	}
	
	//default return value
	return -1; 
}

// sets the nth element of the dlist to a new value.
// Traverses from whichever side of the dlist is closer.
// precondition: the list has at least (n+1) elements
// postcondition: returns the old value of the element that was set
int dlist_set(dlist l, int n, int new_elt){
	//closest to head 
	if(n==0){
		int return_val = dlist_peek(l);
		
		l->head->data = new_elt; 
		
		return return_val; 
	}
	//closest to tail
	else if(n+1==l->size){
		int return_val = dlist_peek_end(l);
		
		l->tail->data = new_elt; 
		
		return return_val;  
	}
	
	//closest to head if in first half of list
	else if(n<=((l->size)/2)-1){
		dlist_node *head = l->head; 
		
		for(int i=0; i<n; i++){
			head = head->next; 
		}
		int return_val = head->data;  
		
		head->data = new_elt; 
		
		return return_val; 	
	}
	
	//closest to tail if in the second half of the list
	else{ 
		dlist_node *tail = l->tail; 
		
		for(int i=0; i<l->size-n-1; i++){
			tail = tail->prev; 
		}
		int return_val = tail->data;
		
		tail->data = new_elt; 
		
		return return_val;  
	}
	
	//default return value
	return -1; 
}

// removes the nth element of the dlist.
// Traverses from whichever side of the dlist is closer.
// precondition: the list has at least (n+1) elements
// postcondition: returns the removed element
int dlist_remove(dlist l, int n){
	//if n=0, then remove the element at the head of the list
	if(n==0){
		/*
		int return_val = dlist_peek(l);
		dlist_node *head = l->head; 
		
		if(head->next!=NULL){
			head = head->next;
			free(head->prev); 
			head->prev = NULL;
			l->head = head; 
		}
		
		else{
			free(head); 
			l->head = NULL; 
		}
		
		l->size--;
		 
		return return_val;
		*/
		return dlist_pop(l);  
	}
	
	//if n+1 = the size of the linked list, then delete the tail. It is important to note that this node will never be the only node, since the if statement, above, would catch the time when head and tail point to the same element
	else if(n+1==l->size){ 
		/*
		int return_val = dlist_peek_end(l);
		
		dlist_node *tail = l->tail->prev;
		free(tail->next);
		tail->next = NULL;  
		l->tail = tail; 
		l->size--; 
		
		return return_val;
		*/
		return dlist_pop_end(l);   
	}
	
	//if you are deleting from the first half of the list, then the head is closest 
	else if(n<=l->size/2-1){
		dlist_node *head = l->head; 
		
		for(int i=0; i<n; i++){
			head = head->next; 
		}
		
		int return_val = head->data;  
		
		delete_node(head);  
		l->size--;
		
		return return_val; 	
	}
	
	//if you are deleting from the second half of the list, then the tail is closest 
	else{
		dlist_node *tail = l->tail; 
		
		for(int i=0; i<l->size-n-1; i++){
			tail = tail->prev; 
		}
		int return_val = tail->data;
		
		delete_node(tail);  
		l->size--;
		
		return return_val;  
	}
	
	//default return value
	return -1; 
}

// frees an dlist. Takes O(size(l)) steps.
void dlist_free(dlist l){
	//free the entire dlist
	free_dlist(l->head); 
	
	//free the dlist_record
	free(l); 
}