/*
 ============================================================================
 Name        : list.h
 Author      : Davide Cosentino
 Version     : 1.0
 Description : Dynamic list implementation for C
 ============================================================================
 */

#include <stdio.h>
#include "list.h"

// Example usages

void addElements(List *list, unsigned int n) {
	for (unsigned int i = 0; i < n; i++)
		add(list, &i, sizeof(i));
}

void printList(List list) {
	for (unsigned int i = 0; i < list.length; i++)
		printf("%d ", *(unsigned int*)get(list, i));
}

int main(void) {
	List list = { NULL, NULL, 0 };
	addElements(&list, 100);
	printList(list);
	getchar();
	return 0;
}
