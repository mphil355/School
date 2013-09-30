/*
Author : Matt Phillips
Date : 2-25-13
Terminal : B-4
Info : This is the main file for the ProgrammingAssignment2View .cpp. It contains the main() method
*/
#include <iostream>
#include "SimulationController.h"
#include "PassengerModel.h"
#include "MPQueueLinkedList.h"

using namespace std;

int main()
{
	MPQueueLinkedList freqLine = MPQueueLinkedList();
	MPQueueLinkedList regLine = MPQueueLinkedList();
	SimulationController controller = SimulationController(regLine, freqLine);
	
	controller.UC1loadFile();

	cout << "Data loaded. " << endl;
	cout << "Enter a 1 to proceed, enter 0 to quit : " << endl;
	int temp;
	cin >> temp;
	if (temp == 1)
		controller.UC2simulate();
	else
		cout << "Goodbye!" << endl;

	int farts;
	cout << "Enter a number to exit.";
	cin >> farts;
}