#include "MyLinkedList.h"

void insertAtEndTest(myLinkedList* ll);
void insertWithinTest(myLinkedList* ll);
void removalTest(myLinkedList* ll);

int main()
{
	myLinkedList* ll = initializeLinkedList();
	insertWithinTest(ll);
	removeAll(ll);


	//insertAtEndTest(ll);
	//removalTest(ll);
	return 0;
}

void insertAtEndTest(myLinkedList* ll) {

	printf("EXERCISE 1\n");
	add(ll, 0);
	add(ll, 1);
	add(ll, 2);
	add(ll, 3);

	printf("Printall.\n");
	printList(ll);
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
}

void removalTest(myLinkedList* ll) {
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

}