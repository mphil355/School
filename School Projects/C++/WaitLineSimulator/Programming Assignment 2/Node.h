/*
Author : Matt Phillips
Date : 2-25-13
Terminal : B-4
Info : Header file for the Node class.
*/
#pragma once
#include "PassengerModel.h"

class Node
{
public:
	Node();
	Node(PassengerModel theData, Node* theNext);
	Node* getNext();
	PassengerModel getData();
	void setNext(Node* theNext);
	void setData(PassengerModel theData);
	~Node();
private:
	Node *next;
	PassengerModel data;
};

