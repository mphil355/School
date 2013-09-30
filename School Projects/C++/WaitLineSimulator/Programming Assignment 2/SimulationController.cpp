/*
Author : Matt Phillips
Date : 2-25-13
Terminal : B-4
Info : Implementation file for the SimulationController class.
*/
#include "SimulationController.h"
#include "MPQueueLinkedList.h"
#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

SimulationController::SimulationController()
{
}
SimulationController::SimulationController(MPQueueLinkedList theRegLine,MPQueueLinkedList theFreqLine)
{
	regLine = theRegLine;
	freqLine = theFreqLine;
	frequent_flyer_max = 0;
	regArrivals = regServed = 0;
	freqArrivals = freqServed = 0;
	regTimeWaited = freqTimeWaited = 0;
	duration = arrivalRateReg = arrivalRateFreq = maxTransactionTime = 0;
	display = 'N';	
}
bool SimulationController::UC1loadFile()
{
	ifstream fileIn("Programming Assignment 2 Data.txt");
	if (fileIn.fail())
	{
		cout << "Error opening File." << endl;
		return false;
	}

	int nextInt;
	char nextChar;
	fileIn >> nextInt;
	arrivalRateFreq = nextInt;
	fileIn >> nextInt;
	arrivalRateReg = nextInt;
	fileIn >> nextInt;
	frequent_flyer_max = nextInt;
	fileIn >> nextInt;
	maxTransactionTime = nextInt;
	fileIn >> nextInt;
	duration = nextInt;
	fileIn >> nextChar;
	display = nextChar;
	fileIn.close();
	return true;
}
bool SimulationController::UC2simulate()
{
	int transactionTimeLeft = 0;
	srand(time(0));
	PassengerModel nextArrival;
	int ffm = 0; // to keep track of frequent flyers served
    for (int clock = 0; clock < duration; clock++)
	{
		int chance = rand()%2;
		if (chance == 0) // for regular passengers
		{
			chance = rand()%60+1;
			if (chance < arrivalRateReg)
			{
				regArrivals++;
				int transactionTime = (rand()%maxTransactionTime+1 );
				nextArrival = PassengerModel(clock, transactionTime, regArrivals);
				regLine.MPenqueue(nextArrival);
				cout << "Regular Passenger " << regArrivals << " enters line at time " << clock <<  "." << endl
					 << "Transaction time is " << transactionTime << "." << endl;
			} // end if
		}
		else if (chance == 1) // for frequent flyers
		{			
			chance = rand()%60+1;
			if (chance < arrivalRateFreq)
			{
				freqArrivals++;
				int transactionTime = (rand()%maxTransactionTime+1 );
				nextArrival = PassengerModel(clock, transactionTime, freqArrivals);
				freqLine.MPenqueue(nextArrival);
				cout << "Frequent Passenger " << freqArrivals << " enters line at time " << clock <<  "." << endl
					 << "Transaction time is " << transactionTime << "." << endl;
			} // end if
		};
      
		if (transactionTimeLeft > 0)
		    transactionTimeLeft--;
	    else if (!freqLine.MPisEmpty() && (ffm < frequent_flyer_max))
		{
		    PassengerModel nextPassenger = freqLine.MPdequeue();
			transactionTimeLeft = nextPassenger.getTransactionTime() - 1;
			int timeWaited = clock - nextPassenger.getArrivalTime();
			freqTimeWaited = freqTimeWaited + timeWaited;
			freqServed++;
			cout << "Frequent Passenger " << nextPassenger.getCustomerNumber() << " begins service at time " << clock << "." << endl
				 << "Time waited is " << timeWaited << "." << endl;
			ffm++;
		} 
		else if (!regLine.MPisEmpty())
		{			
		    PassengerModel nextPassenger = regLine.MPdequeue();
			transactionTimeLeft = nextPassenger.getTransactionTime() - 1;
			int timeWaited = clock - nextPassenger.getArrivalTime();
			regTimeWaited = regTimeWaited + timeWaited;
			regServed++;
			cout << "Regular Passenger " << nextPassenger.getCustomerNumber() << " begins service at time " << clock << "." << endl
				 << "Time waited is " << timeWaited << "." << endl;
			ffm = 0;
		}
		else
		{
			cout << "Server is Idle." << endl;
			ffm = 0;
		}
	} // end for

	if (display == 'Y')
		UC3displayResults();
	return true;
  } // end simulate
bool SimulationController::UC3displayResults()
{
	cout << "Regular Passengers Served: " << regServed << endl;
	if (regTimeWaited == 0)
		cout << "Regular Passengers had no wait time" << endl;
	else
	{
		double avgWait = static_cast<double>(regServed)/regTimeWaited;
		cout << "Regular Passengers Average Wait Time: " << avgWait << endl;
	}

	cout << "Frequent Passengers Served: " << freqServed << endl;
	if (freqTimeWaited == 0)
		cout << "Frequent Passengers Average Wait Time : " << freqTimeWaited << endl;
	else
	{
		double avgWait = static_cast<double>(freqServed)/freqTimeWaited;
		cout << "Frequent Passengers Average Wait Time: " << avgWait << endl;
	}
	cout << "Regular Passengers Left in Line: " << regLine.MPsize() << endl;
	cout << "Frequent Passengers Left in Line: " << freqLine.MPsize() << endl;
	return true;
}
SimulationController::~SimulationController()
{
}
