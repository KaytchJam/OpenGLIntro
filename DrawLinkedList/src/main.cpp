#include "MyLinkedList.h"

void insertAtEndTest(myLinkedList* ll);
void insertWithinTest(myLinkedList* ll);
void removalTest(myLinkedList* ll);
void duplicateValueTest(myLinkedList* ll);

int main()
{
	myLinkedList* ll = initializeLinkedList();
	insertAtEndTest(ll);
	insertWithinTest(ll);
	removalTest(ll);
	duplicateValueTest(ll);



	//insertAtEndTest(ll);
	//removalTest(ll);
	return 0;
}

void insertAtEndTest(myLinkedList* ll) {

	printf("EXERCISE 1\n");
	addItem(ll, 0);
	addItem(ll, 1);
	addItem(ll, 2);
	addItem(ll, 3);
	printList(ll);
	removeAll(ll);
}

void insertWithinTest(myLinkedList* ll) {

	printf("EXERCISE 2\n");
	add(ll, 5);
	add(ll, 0);
	add(ll, 4);
	add(ll, 2);

	printList(ll);

	add(ll, 3);
	
	printList(ll);

	add(ll, 1);

	printList(ll);
	removeAll(ll);
}

void removalTest(myLinkedList* ll) {
	printf("EXERCISE 3\n");
	add(ll, 0);
	add(ll, 1);
	add(ll, 2);
	add(ll, 3);
	add(ll, 4);
	add(ll, 5);

	printList(ll);

	remove(ll, 3); // remove 3

	printList(ll);

	remove(ll, 2); // remove 2
	remove(ll, 0); // remove 0

	printList(ll);
	removeAll(ll);
}

void duplicateValueTest(myLinkedList* ll) {

	printf("EXERCISE 4\n");
	add(ll, 1);
	add(ll, 1);
	add(ll, 1);
	add(ll, 1);
	add(ll, 1);
	add(ll, 0);
	printList(ll);
	removeAll(ll);
}