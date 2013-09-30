/*
Author : Matt Phillips
Date : 2-25-13
Terminal : B-4
Info : Implementation file for the Node class.
*/
#include "Node.h"

Node::Node()
{
}
Node::Node(PassengerModel theData, Node* theNext)
{
	data = theData;
	next = theNext;
}
Node* Node::getNext()
{
	return next;
}
PassengerModel Node::getData()
{
	return data;
}
void Node::setNext(Node* theNext)
{
	next = theNext;
}
void Node::setData(PassengerModel theData)
{
	data = theData;
}
Node::~Node()
{
}
