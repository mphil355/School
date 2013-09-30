/*
Author : Matt Phillips
Date : 2-25-13
Terminal : B-4
Info : Header file for the PassengerModel class.
*/
#pragma once

class PassengerModel
{
public:
	PassengerModel();
	PassengerModel(int theArrivalTime, int theTransactionTime, int theCustomerNumber);
	PassengerModel(PassengerModel& thePassenger);
	int getArrivalTime();
	int getTransactionTime();
	int getCustomerNumber();
	void setArrivalTime(int theArrivalTime);
	void setTransactionTime(int theTransactionTime);
	void setCustomerNumber(int theCustomerNumber);
	~PassengerModel();
private:
	int arrivalTime;
	int transactionTime;
	int customerNumber;
};

