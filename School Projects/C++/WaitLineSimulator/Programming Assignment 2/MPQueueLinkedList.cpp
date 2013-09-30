/*
Author : Matt Phillips
Date : 2-25-13
Terminal : B-4
Info : Implementation file for the MPQueueLinkedList class.
*/
#include "MPQueueLinkedList.h"
#include <cstddef>
#include <iostream>

using namespace std;

MPQueueLinkedList::MPQueueLinkedList()
{
	head = NULL;
	tail = NULL;
	size = 0;
}
bool MPQueueLinkedList::MPenqueue(PassengerModel thePassenger)
{
	Node *newNode = new Node(thePassenger, NULL);

	if(MPisEmpty())
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->setNext(newNode);
		tail = newNode;
	}

	size++;
	return true;
}
PassengerModel MPQueueLinkedList::MPdequeue()
{
	Node *temp;
	if (!MPisEmpty())
	{
		PassengerModel thePassenger = head->getData();
		temp = head;
		head = head->getNext();

		if ( head == NULL)
			tail == NULL;
		
		delete temp;
		return thePassenger;
	}

	cout << "Error : Queue is empty! " << endl;
}
PassengerModel MPQueueLinkedList::MPgetFront()
{
	if (!MPisEmpty())
	{
		PassengerModel front = head->getData();
		return front;
	}
	cout << "Error : Queue is empty! " << endl;
}
bool MPQueueLinkedList::MPisEmpty()
{
	return (head == NULL);
}
bool MPQueueLinkedList::MPclear()
{
	Node *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->getNext();
		delete temp;
	}
	tail = NULL;

	return true;
}
int MPQueueLinkedList::MPsize()
{
	return size;
}
MPQueueLinkedList::~MPQueueLinkedList()
{

}
