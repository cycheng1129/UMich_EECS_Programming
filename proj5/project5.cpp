#include <iostream>
#include <string>
#include "EventClass.h"
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "RestaurantSimulationClass.h"
#include "random.h"
#include "constant.h"
using namespace std;


/*
    Programer: Chen-Yu Cheng
    Date: December 2019
    Title: EECS 402 Fall 2019 Project 5
    Purpose: Server simulation at a fast food restaurant. Use templates so 
             that the inputs of functions are able to have class type variable.
             Use pseudo-random numbers to generate the scheduled times of the 
             events that will happen. Print out important informations of the 
             simulation results.
*/

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else 

int main()
{
    bool success;
    string paramsFname;
    RestaurantSimulationClass restSim;

    cout << "Please enter the file name of simulation parameters: " << endl;
    cin >> paramsFname;

    // Setting up
    success = restSim.setUpSimulation(paramsFname);
    if (success)
        restSim.printParameters();
    else
        cout << "ERROR: Not running simulation - error in setup!" << endl; 

    if (success){
        cout << "Scheduling 'seed' event of 1st customer arrival at 0" << endl;
        restSim.scheduleEvent(EventClass(1, ARRIVE, FIRSTARRTIME));
        cout << "-------------Starting simulation now!-------------" << endl;

        while (restSim.getNumScheduledEvents() > 0){
            restSim.handleNextEvent();
        }
        cout << "-------------Simulation has finished!-------------" << endl;
        restSim.printStatistics();
        cout << "Thanks for using this program!" << endl;
    }

    return 0;
}

#endif