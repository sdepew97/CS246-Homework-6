#include "dlist.h"
#include "dlist_node.h"

typedef struct dlist_record {
  dlist_node *head; //pointer to the first node in the dlist
  dlist_node *tail; //pointer to the last node in the dlist
  int size;  // number of nodes in the dlist
} dlist_record;

// An abstract type for sequences
typedef struct dlist_record* dlist;

// return an empty dlist. Make sure to call dlist_free when you're done
// with it.
dlist dlist_new(){
	dlist d = malloc(sizeof(dlist_record)); 
	d->size = 0; 
	d->head = NULL;
	d->tail = NULL;  
	
	return d; 
}

// returns the number of elements in the dlist. Runs in constant time.
int dlist_size(dlist l){
	return l->size; 
}

// appends a new element to the beginning of the dlist. Runs in constant time.
void dlist_push(dlist l, int elt){
	l->head = new_node(elt, l->head, NULL); 
	
	if(l->head->next != NULL){ //if this element is not the first element/has a node after it
		l->head->next->prev = l->head; 
	}
	
	if(l->tail == NULL){ //if the tail doesn't point to anything, which makes this the first element of the list, then tail should change 
		l->tail = l->head; 
	}
	
	l->size++; 
}

// removes and returns the first element in the dlist. Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_pop(dlist l){
	dlist_node *old_head = l->head; 
	int return_val = old_head->data;
	
	if(l->head == l->tail){ //popping the only element on the list
			l->tail = NULL; //the list is going to be empty 
	} 
	
	l->head = old_head->next; //will be NULL iff head only node 
	l->size--; 
	
	free(old_head); //frees the memory for the old head value, since this was originally malloced 
	return return_val; 
}

// returns the first element in the dlist, without changing the dlist.
// Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_peek(dlist l){
	return l->head->data; //returns the data from the dlist node pointed to by head
}

// appends a new element to the end of the dlist. Runs in constant time.
void dlist_push_end(dlist l, int elt){
	l->tail = new_node(elt, NULL, l->tail); 
	
	if(l->tail->prev != NULL){ //the tail was updated and so the node pointed to needs to link to the one before it 
		l->tail->prev->next = l->tail; 
	}
	
	if(l->head == NULL){ //if the head doesn't currently point to anything, which makes this the first element of the list, then head should change 
		l->head = l->tail; 
	}
	
	l->size++;
}

// removes and returns the last element in the dlist. Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_pop_end(dlist l){
	dlist_node *old_tail = l->tail;
	int return_val = old_tail->data; 
	
	if(l->tail == l->head){ //checking if there is only one node or if there are more
		l->head = NULL; 
	}
	
	l->tail = old_tail->prev; 
	free(old_tail); 
	l->size--; 
	
	return return_val; 
}

// returns the last element in the dlist, without changing the dlist.
// Runs in constant time.
// precondition: there is at least one element in the dlist.
int dlist_peek_end(dlist l){
	return l->tail->data; 
}

// adds a new element into the dlist, after n existing elements.
// Traverses from whichever side of the dlist is closer.
// precondition: the list has at least n elements
void dlist_insert(dlist l, int n, int elt){
	if(n==0){
		dlist_push(l, elt); 
	}
	
	else if(n==l->size){
		dlist_push_end(l, elt); 
	}
	
	else if(n<=l->size/2){
		dlist_node *target = l->head; 
		for(int i=0; i<n-1; i++){
			target = target->next; 
		}
		insert_after(target, elt);
		l->size++;  
	}
	
	//n>l->size/2
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
	if(n==0){
		return dlist_peek(l); 
	}
	
	else if(n+1==l->size){
		return dlist_peek_end(l); 
	}
	
	else if(n<=l->size/2-1){
		dlist_node *head = l->head; 
		
		for(int i=0; i<n; i++){
			head = head->next; 
		}
		return head->data;  	
	}
	
	else{ //n>l->size/2
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
	if(n==0){
		int return_val = dlist_peek(l);
		
		l->head->data = new_elt; 
		
		return return_val; 
	}
	
	else if(n+1==l->size){
		int return_val = dlist_peek_end(l);
		
		l->tail->data = new_elt; 
		
		return return_val;  
	}
	
	else if(n<=l->size/2-1){
		dlist_node *head = l->head; 
		
		for(int i=0; i<n; i++){
			head = head->next; 
		}
		int return_val = head->data;  
		
		head->data = new_elt; 
		
		return return_val; 	
	}
	
	else{ //n>l->size/2
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
	if(n==0){
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
	}
	
	else if(n+1==l->size){ //will never be the only node, since the if statement, above, would catch the time when head and tail point to the same element
		int return_val = dlist_peek_end(l);
		
		dlist_node *tail = l->tail->prev;
		
		l->tail = tail; 
		l->size--; 
		
		return return_val;  
	}
	
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
	
	else{ //n>l->size/2
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
	//free_dlist(l->head); 
	free(l); 
}