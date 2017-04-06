#include "dlist_node.h"
#include "dlist.h"
#include <stdio.h>

int main(void){
	int arr[] = {1,2,3,4,5,6}; 
	dlist d = dlist_new(); 
	
	for(int i=0; i<6; i++){
		dlist_push(d, arr[i]); 
		//dlist_push_end(d, arr[5-i]);
		//dlist_insert(d, 0, arr[i]);  
	}
	for(int i=0; i<6; i++){
		if(arr[i]!=dlist_get(d,i)){
			printf("failed"); 
		}
	}

}