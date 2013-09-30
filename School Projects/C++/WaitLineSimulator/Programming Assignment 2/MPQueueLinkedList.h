/*
Author : Matt Phillips
Date : 2-25-13
Terminal : B-4
Info : Header file for the MPQueueLinkedList class.
*/
#pragma once
#include "PassengerModel.h"
#include "Node.h"

class MPQueueLinkedList
{
public:
	MPQueueLinkedList();
	bool MPenqueue(PassengerModel thePassenger);
	PassengerModel MPdequeue();
	PassengerModel MPgetFront();
	bool MPisEmpty();
	bool MPclear();
	int MPsize();
	~MPQueueLinkedList();
private:	
	Node *head;
	Node *tail;
	int size;
};

