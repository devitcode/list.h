#ifndef LIST_H
#define LIST_H

typedef struct Element Element;

typedef struct {	// Defines the data structure bidirectional list's node
	Element *first;
	Element *last;
	unsigned int length;
} List;

void save(List list, char fileName[], unsigned int size);	// Saves the list in a file
List importList(char fileName[], unsigned int size);	// Reads the list for a file and stores it in a new list
void add(List *list, void *value, unsigned int size);
void addStart(List *list, void *value, unsigned int size);	// Adds first element of the list
void removeIndex(List *list, unsigned int index);	// Removes the index-positioned node from the list
void removeValue(List *list, void *value, unsigned int size);
void *get(List list, unsigned int index);
void set(List list, unsigned int index, void *value, unsigned int size);
List indexesOfValue(List list, void *value, unsigned int size);	// Finds elements with a certain value in their value field
List indexesOfSub(List list, List sub, unsigned int size);
List splitWithVal(List list, void *value, unsigned int size);
List splitWithSub(List list, List sub, unsigned int size);
void init(List *list);	// Creates a new list
void removeAll(List *list);	// Deletes all elements from a list and deallocates them from heap
List clone(List list, unsigned int size);
void setAll(List list, void *oldValue, void *newValue, unsigned int size);

#endif
