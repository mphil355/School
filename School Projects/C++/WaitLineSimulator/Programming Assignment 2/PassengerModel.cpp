/*
Author : Matt Phillips
Date : 2-25-13
Terminal : B-4
Info : Implementation file for the PassengerModel class.
*/
#include "PassengerModel.h"

PassengerModel::PassengerModel()
{
	arrivalTime = 0;
	transactionTime = 0;
	customerNumber = 0;
}
PassengerModel::PassengerModel(int theArrivalTime, int theTransactionTime, int theCustomerNumber)
{
	arrivalTime = theArrivalTime;
	transactionTime = theTransactionTime;
	customerNumber = theCustomerNumber;
}
PassengerModel::PassengerModel(PassengerModel& thePassenger)
{
	arrivalTime = thePassenger.arrivalTime;
	transactionTime = thePassenger.transactionTime;
	customerNumber = thePassenger.customerNumber;		
}
int PassengerModel::getArrivalTime()
{
	return arrivalTime;
}
int PassengerModel::getTransactionTime()
{
	return transactionTime;
}
int PassengerModel::getCustomerNumber()
{
	return customerNumber;
}
void PassengerModel::setArrivalTime(int theArrivalTime)
{
	arrivalTime = theArrivalTime;
}
void PassengerModel::setTransactionTime(int theTransactionTime)
{
	transactionTime = theTransactionTime;
}
void PassengerModel::setCustomerNumber(int theCustomerNumber)
{
	customerNumber = theCustomerNumber;
}
PassengerModel::~PassengerModel()
{
}
