/*
Author : Matt Phillips
Date : 2-25-13
Terminal : B-4
Info : Header file for the SimulationController class.
*/
#pragma once
#include "PassengerModel.h"
#include "MPQueueLinkedList.h"

class SimulationController
{
public:
	SimulationController();
	SimulationController(MPQueueLinkedList theRegLine,MPQueueLinkedList theFreqLine);
	bool UC1loadFile();
	bool UC2simulate();
	bool UC3displayResults();
	~SimulationController();
private:
	MPQueueLinkedList regLine;
	MPQueueLinkedList freqLine;
	int frequent_flyer_max;
	int regArrivals, regServed;
	int freqArrivals, freqServed;
	int regTimeWaited, freqTimeWaited;
	int duration, arrivalRateReg, arrivalRateFreq, maxTransactionTime;
	char display;
};

