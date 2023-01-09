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

	// header node that is never changed, using minimum 32 bit signed integer
	newLL->head = createNode(NULL, 1 << ((sizeof(int) * 8) - 1), NULL);
	newLL->head->next = newLL->head;
	newLL->head->prev = newLL->head;
	newLL->size = 0;

	return newLL;
}

void printNode(llNode *newNode) {
	printf("_______________\n");
	printf("newNode data: %d\n", newNode->data);
	printf("newNode prev data: %d\n", newNode->prev->data);
	printf("newNode next data: %d\n", newNode->next->data);
	printf("_______________\n");
}

void addFirst(myLinkedList *ll, int item) {
	llNode* newNode = createNode(ll->head, item, ll->head->next);
	ll->head->next = newNode;
	ll->size++;
}

void add(myLinkedList* ll, int item) {
	llNode* temp = ll->head;
	int count = -1;

	while (count < ll->size - 1 && temp->next->data <= item) {
		temp = temp->next;
		count++;
	}

	llNode* newNode = createNode(temp, item, temp->next);
	newNode->next->prev = newNode;
	newNode->prev->next = newNode;
	ll->size++;
}

void printList(myLinkedList* ll) {

	llNode* temp = ll->head->next;
	for (int i = 0; i < ll->size; i++) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}
