#include "MyLinkedList.h"

int main()
{
	myLinkedList* ll = initializeLinkedList();
	add(ll, 0);
	add(ll, 1);
	add(ll, 2);
	add(ll, 3);

	printf("Printall.\n");
	printList(ll);
	return 0;
}