#pragma once
#include <cstdlib>
#include <iostream>
#include <cassert>

typedef struct LinkedListNode {
	int data;
	struct LinkedListNode* next;
	struct LinkedListNode* prev;
} llNode;

typedef struct myLinkedList {
	llNode* head;
	int size;
} myLinkedList;

void setNode(llNode* node, llNode* prevNode, int item, llNode* nextNode) {
	node->prev = prevNode;
	node->data = item;
	node->next = nextNode;
}

llNode* createNode(llNode* prevNode, int item, llNode* nextNode) {
	llNode* newNode = (llNode*)malloc(sizeof(llNode));
	assert(newNode != NULL);

	setNode(newNode, prevNode, item, nextNode);
	return newNode;
}

myLinkedList * initializeLinkedList() {
	myLinkedList* newLL = (myLinkedList*)malloc(sizeof(myLinkedList));
	assert(newLL != NULL);

	newLL->head = createNode(NULL, 0, NULL);
	return newLL;
}

void addFirst(myLinkedList *ll, int item) {
	llNode* newNode = createNode(ll->head, item, ll->head->next);

}

void addFirst(myLinkedList* ll) {
}


