#ifndef LIST_H
#define LIST_H

typedef struct Element Element;

typedef struct {
	Element *first;
	Element *last;
	unsigned int length;
} List;

void save(List list, char fileName[], unsigned int size);
List importList(char fileName[], unsigned int size);
void add(List *list, void *value, unsigned int size);
void addStart(List *list, void *value, unsigned int size);
void removeIndex(List *list, unsigned int index);
void removeValue(List *list, void *value, unsigned int size);
void *get(List list, unsigned int index);
void set(List list, unsigned int index, void *value, unsigned int size);
List indexesOfValue(List list, void *value, unsigned int size);
List indexesOfSub(List list, List sub, unsigned int size);
List splitWithVal(List list, void *value, unsigned int size);
List splitWithSub(List list, List sub, unsigned int size);
void init(List *list);
void removeAll(List *list);
List clone(List list, unsigned int size);
void setAll(List list, void *oldValue, void *newValue, unsigned int size);

#endif
