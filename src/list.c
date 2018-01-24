#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct Element {
	void *value;
	Element *prev;
	Element *next;
};

void save(List list, char fileName[], unsigned int size) {
	FILE *fp = fopen(fileName, "wb");
	for (unsigned int i = 0; i < list.length; i++)
		fwrite(get(list, i), size, 1, fp);
	fclose(fp);
}

List importList(char fileName[], unsigned int size) {
	List list = { NULL, NULL };
	FILE *fp = fopen(fileName, "rb");
	void *element = malloc(size);
	do {
		fread(element, size, 1, fp);
		if (!feof(fp))
			add(&list, element, size);
	} while (!feof(fp));
	free(element);
	fclose(fp);
	return list;
}

// only for testing purpose
void print(List list) {
	for (unsigned int i = 0; i < list.length; i++)
		printf("%d ", *(unsigned int*) get(list, i));
	puts("");
}

void add(List *list, void *value, unsigned int size) {
	Element *element = (Element*) malloc(sizeof(Element));
	element->value = malloc(size);
	element->next = NULL;
	element->prev = NULL;
	memcpy(element->value, value, size);
	if (list->last != NULL) {
		list->last->next = element;
		element->prev = list->last;
	} else
		list->first = element;
	list->last = element;
	list->length++;
}

void addStart(List *list, void *value, unsigned int size) {
	Element *element = (Element*) malloc(sizeof(Element));
	element->value = malloc(size);
	element->next = NULL;
	element->prev = NULL;
	memcpy(element->value, value, size);
	if (list->first != NULL) {
		list->first->prev = element;
		element->next = list->first;
	} else
		list->last = element;
	list->first = element;
	list->length++;
}

void removeIndex(List *list, unsigned int index) {
	Element *element = list->first;
	for (unsigned int i = 0; i < index; i++)
		element = element->next;
	if (element->prev != NULL)
		element->prev->next = element->next;
	else
		list->first = element->next;
	if (element->next != NULL)
		element->next->prev = element->prev;
	else
		list->last = element->prev;
	free(element);
	list->length--;
}

void decrementIndexes(List indexes, unsigned int index) {
	unsigned int decIndex;
	for (unsigned int i = index + 1; i < indexes.length; i++) {
		decIndex = *(unsigned int*) get(indexes, i) - 1;
		set(indexes, i, &decIndex, sizeof(decIndex));
	}
}

void removeValue(List *list, void *value, unsigned int size) {
	List indexes = indexesOfValue(*list, value, size);
	Element *index = indexes.first;
	for (unsigned int i = 0; i < indexes.length; i++) {
		decrementIndexes(indexes, i);
		removeIndex(list, *(unsigned int*) index->value);
		index = index->next;
	}
}

void *get(List list, unsigned int index) {
	Element *element = list.first;
	for (unsigned int i = 0; i < index; i++)
		element = element->next;
	return element->value;
}

void set(List list, unsigned int index, void *value, unsigned int size) {
	Element *element = list.first;
	for (unsigned int i = 0; i < index; i++)
		element = element->next;
	memcpy(element->value, value, size);
}

void setAll(List list, void *oldValue, void *newValue, unsigned int size) {
	List indexes = indexesOfValue(list, oldValue, size);
	for (unsigned int i = 0; i < indexes.length; i++)
		set(list, *(int*) get(indexes, i), newValue, size);
}

List indexesOfValue(List list, void *value, unsigned int size) {
	List aus = { NULL, NULL };
	for (unsigned int i = 0; i < list.length; i++)
		if (memcmp(value, get(list, i), size) == 0)
			add(&aus, &i, sizeof(i));
	return aus;
}

List indexesOfSub(List list, List sub, unsigned int size) {
	List aus = indexesOfValue(list, get(sub, 0), size);
	unsigned int match, index;
	for (unsigned int i = 0; i < aus.length; i++) {
		match = 0;
		for (unsigned int j = 1; j < sub.length; j++) {
			index = *(unsigned int*) get(aus, i) + j;
			if (index < list.length)
				if (memcmp(get(list, index), get(sub, j), size) == 0)
					match++;
		}
		if (match != sub.length - 1) {
			removeIndex(&aus, i);
			i--;
		}
	}
	return aus;
}

void init(List *list) {
	list->first = NULL;
	list->last = NULL;
	list->length = 0;
}

void removeAll(List *list) {
	unsigned int length = list->length;
	for (unsigned int i = 0; i < length; i++)
		removeIndex(list, 0);
	init(list);
}

List splitWithSub(List list, List sub, unsigned int size) {
	unsigned int index;
	unsigned int start = 0;
	List aus = { NULL, NULL, 0 };
	List element = { NULL, NULL, 0 };
	List indexes = indexesOfSub(list, sub, size);
	for (unsigned int i = 0; i < indexes.length; i++) {
		index = *(unsigned int*) get(indexes, i);
		for (unsigned int j = start; j < index; j++)
			add(&element, get(list, j), size);
		if (element.length > 0)
			add(&aus, &element, sizeof(element));
		init(&element);
		start = index + sub.length;
	}
	if (start < list.length) {
		for (unsigned int i = start; i < list.length; i++)
			add(&element, get(list, i), size);
		add(&aus, &element, sizeof(element));
	}
	return aus;
}

List splitWithVal(List list, void *value, unsigned int size) {
	List sub = { NULL, NULL, 0 };
	add(&sub, value, size);
	return splitWithSub(list, sub, size);
}

List clone(List list, unsigned int size) {
	List aus = { NULL, NULL, 0 };
	for (unsigned int i = 0; i < list.length; i++)
		add(&aus, get(list, i), size);
	return aus;
}

