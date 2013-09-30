/*
Author : Matt Phillips
Date : 2-25-13
Terminal : B-4
Info : Test file for the MPQueueLinkedList class. All methods currently passing.
*/
#include <cfixcc.h>
#include "MPQueueLinkedList.h"
class MPQueueLinkedListTest : public cfixcc::TestFixture
{
private:

public:
	void TestMPenqueue()
	{
		MPQueueLinkedList q = MPQueueLinkedList();
		PassengerModel temp;
		bool expected = true;
		bool actual = q.MPenqueue(temp);
		CFIXCC_ASSERT_EQUALS(expected, actual);
	}
	void TestMPdequeue()
	{
		MPQueueLinkedList q = MPQueueLinkedList();
		PassengerModel expectedPass = PassengerModel();
		PassengerModel actualPass = expectedPass;
		q.MPenqueue(expectedPass);
		actualPass = q.MPdequeue();		
		int expected = expectedPass.getArrivalTime();
		int actual = actualPass.getArrivalTime();
		CFIXCC_ASSERT_EQUALS(expected, actual);
	}
	void TestMPgetFront()
	{
		MPQueueLinkedList q = MPQueueLinkedList();
		PassengerModel expectedPass = PassengerModel();
		PassengerModel actualPass = expectedPass;
		q.MPenqueue(expectedPass);
		actualPass = q.MPgetFront();		
		int expected = expectedPass.getArrivalTime();
		int actual = actualPass.getArrivalTime();
		CFIXCC_ASSERT_EQUALS(expected, actual);
	}
	void TestMPisEmpty()
	{
		MPQueueLinkedList q = MPQueueLinkedList();
		bool expected = true;
		bool actual = q.MPisEmpty();
		CFIXCC_ASSERT_EQUALS(expected, actual);
	}
	void TestMPclear()
	{
		MPQueueLinkedList q = MPQueueLinkedList();
		bool expected = true;
		bool actual = q.MPclear();
		CFIXCC_ASSERT_EQUALS(expected, actual);
	}
	void TestMPsize()
	{
		MPQueueLinkedList q = MPQueueLinkedList();
		int expected = 0;
		int actual = q.MPsize();
		CFIXCC_ASSERT_EQUALS(expected, actual);
	}
};

CFIXCC_BEGIN_CLASS(MPQueueLinkedListTest)
	CFIXCC_METHOD(TestMPenqueue)
	CFIXCC_METHOD(TestMPdequeue)
	CFIXCC_METHOD(TestMPgetFront)
	CFIXCC_METHOD(TestMPisEmpty)
	CFIXCC_METHOD(TestMPclear)
	CFIXCC_METHOD(TestMPsize)
CFIXCC_END_CLASS()

