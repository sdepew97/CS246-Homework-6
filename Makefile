# Name: Sarah Depew

all: check_dlist_node check_dlist

check_dlist: dlist.o check_dlist.o
	gcc -g -o check_dlist dlist.o dlist_node.o check_dlist.o -lcheck

check_dlist_node: dlist_node.o check_dlist_node.o
	gcc -g -o check_dlist_node dlist_node.o check_dlist_node.o -lcheck

check_dlist_node.o: check_dlist_node.c dlist_node.h
	gcc -c -g check_dlist_node.c

check_dlist.o: check_dlist.c dlist.h dlist_node.h
	gcc -c -g check_dlist.c

dlist.o: dlist.c dlist.h dlist_node.h
	gcc -c -g dlist.c

dlist_node.o: dlist_node.c dlist_node.h
	gcc -c -g dlist_node.c

