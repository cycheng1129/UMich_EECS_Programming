/*
   Programer: Chen-Yu Cheng
   Date: December 2019
   Title: **********
   Purpose: **********
*/

#include <iostream>
#include <fstream>
#include "RestaurantSimulationClass.h"
#include "EventClass.h"
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "random.h"
#include "constant.h"
using namespace std;

bool RestaurantSimulationClass::setUpSimulation(string fname){
    ifstream inFile;

    inFile.open(fname.c_str());
    if (inFile.fail()){
        cout << "Unable to open input file!\n";
        return false;
    }
    // Parameters initialization
    inFile >> closeTime
           >> percentNotWait >> lengthLongLine >> seedVal
           >> minArriveTime >> maxArriveTime
           >> meanServeTime >> stdDevServeTime;
    setSeed(seedVal);
    // Parameters during simulation (change with time)
    currTime = 0;
    customerBeingServed = 0;
    timeLongStart = 0;
    // Statistics
    numCustomers = 0;
    timeBusy = 0;
    numInLine = 0;
    numLeftNoServe = 0;
    longestLine = 0;
    afterTime = 0;
    timeLongQueue = 0;

    return true;
}

void RestaurantSimulationClass::printParameters(){
    cout << "---------------Simulation Parameters---------------" << endl;
    cout << "Total opening minutes: " << closeTime << endl;
    cout << "Percentage of customers don't like to wait in excessively" << endl
         << "long line: " << percentNotWait<< endl;
    cout << "The length of line to be considered as excessively long: "
         << lengthLongLine << endl;
    cout << "Minimum time for next customer to arrive: "
         << minArriveTime << endl;
    cout << "Maximum time for next customer to arrive: "
         << maxArriveTime << endl;
    cout << "Average time of serving time: " << meanServeTime << endl;
    cout << "Standard deviation time of serving time: " 
         << stdDevServeTime << endl;
}

void RestaurantSimulationClass::scheduleEvent(EventClass inEvent){
    eventList.insertValue(inEvent);
}

int RestaurantSimulationClass::getNumScheduledEvents(){
    return eventList.getNumElems();
}

void RestaurantSimulationClass::handleNextEvent(){
    int arriveTime, serveTime, custNum;
    int lengthQueue = serveQueue.getNumElems();
    string event;
    EventClass nextEvent;
    EventClass nextServe;
    EventClass currLeave;
    bool served;

    // Get the next event in eventList
    eventList.removeFront(nextEvent);
    custNum = nextEvent.getCustOrdNum();
    event = nextEvent.getEvent();
    currTime = nextEvent.getTime();
    served = nextEvent.leaveWithServe();
    cout << "========================================================" << endl;
    cout << "At time = " << currTime << ", customer " << custNum
         << " " << event << endl;

    if (event == ARRIVE){
        numCustomers++;

        // Customer comes after restaurant close
        if (currTime > closeTime){
            numCustomers--;
            cout << "  The restaurant is closed, customer " << custNum 
                 << " can't be served." << endl;
            
            return;
        }

        // Schedule next arrive event
        arriveTime = getUniform(minArriveTime, maxArriveTime);
        EventClass nextArrEvent(custNum + 1, 
                                ARRIVE, 
                                currTime + arriveTime);
        eventList.insertValue(nextArrEvent);
        
        // If the line is excessively long
        if (lengthQueue >= lengthLongLine){
            cout << "  The line is excessively long, customer " << custNum
                 << " decides to ";
            // Decides to leave directly
            if (getUniform(MINPERCENTAGE, MAXPERCENTAGE) <= percentNotWait){
                cout << "leave" << endl;
                EventClass leaveEvent(custNum, LEAVE, currTime, false);
                eventList.insertValue(leaveEvent);
                numLeftNoServe++;

                return;
            }
            // Decides to queue
            else{
                cout << "queue" << endl;
            }
        }
        
        // Schedule serve event of the arrived customer
        EventClass serveEvent(custNum, SERVE, currTime);
        // The customer can be served immediately after arriving
        if (customerBeingServed == 0){
            directlyServed = true;
            eventList.insertValue(serveEvent);
            // Schedule leave event of the arrived customer
            serveTime = getNormal(meanServeTime, stdDevServeTime);
            EventClass leaveEvent(custNum, LEAVE, currTime + serveTime);
            eventList.insertValue(leaveEvent);
            // Update the total serve busy time
            timeBusy += serveTime;
        }
        // There is customer being served now, enqueue
        else {
            serveQueue.enqueue(serveEvent);
            numInLine++;
            lengthQueue++;
            cout << "  Customer " << custNum << " queues, ";
            cout << "current queue length: " << lengthQueue << endl;
            // Update the statistics (longest line)
            if (lengthQueue > longestLine)
                longestLine = lengthQueue;
            // Update the long line time
            if (lengthQueue >= lengthLongLine){
                // The queue becomes excessively long
                if (lengthQueue == lengthLongLine)
                    cout << "  Excessively long queue starts!" << endl;
                // The excessively long line continues
                else 
                    timeLongQueue += currTime - timeLongStart;
                timeLongStart = currTime;
            }
        }
    }

    else if (event == SERVE){
        customerBeingServed++;
        if (directlyServed == false)
            cout << "  Current queue length: " << lengthQueue << endl;
        
        // Excessively long line ends
        if (lengthQueue == lengthLongLine - 1){ // The length of queue 
                                                // "becomes" smaller than 
                                                // excessively long length 
            cout << "  The queue is not excessively long now." << endl;
            timeLongQueue += currTime - timeLongStart;
            cout << "  Total time of excessively long queue so far: " 
                 << timeLongQueue << endl;
        }
    }

    else if (event == LEAVE && served){
        customerBeingServed--;

        // There is customer in queue, the next customer can be served 
        // after the previous one left
        if(lengthQueue > 0){
            serveQueue.dequeue(nextServe);
            // Schedule the next serve event
            directlyServed = false;
            custNum = nextServe.getCustOrdNum();
            EventClass nextServe(custNum, 
                                 SERVE, 
                                 currTime);
            eventList.insertValue(nextServe);
            // Schedule the next leave event
            serveTime = getNormal(meanServeTime, stdDevServeTime);
            EventClass leaveEvent(custNum, 
                                  LEAVE, 
                                  currTime + serveTime);
            eventList.insertValue(leaveEvent);
            // Update the total serve busy time
            timeBusy += serveTime;
        }

        // Update time to serve after the restaurant closed
        afterTime = currTime - closeTime;
        // There is no customer in queue after it closed
        if (afterTime < 0) 
            afterTime = 0;
    }
}

void RestaurantSimulationClass::printStatistics(){
    cout << "-Total number of customers that showed up during open " << endl
         << " time: " << numCustomers << endl;
    cout << "-Percentage of time the server was busy helping " << endl
         << " customers: "
         << static_cast<float>(timeBusy) / (closeTime + afterTime) * 100
         << "%" << endl;
    cout << "-Percentage of customers had to wait in line: "
         << static_cast<float>(numInLine) / 
            (numCustomers - numLeftNoServe) * 100
         << "%" << endl;
    cout << "-The number of customers that arrived, but left due to " << endl
         << " excessive line length: " << numLeftNoServe << endl;
    cout << "-The longest the line was throughout the simulation: "
         << longestLine << endl;
    cout << "-Time required to serve customers already in queue after " << endl
         << " the restaurant closed: " << afterTime << endl;
    cout << "-Percentage of time with excessively long line: " 
         << static_cast<float>(timeLongQueue) / (closeTime + afterTime) *100
         << "%" << endl;
}
