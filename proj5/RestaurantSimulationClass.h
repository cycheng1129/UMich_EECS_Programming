// Customer arrives
// Customer finishes being served
// Customer leaves (%customer, # in queue)
// close time

/*
   Programer: Chen-Yu Cheng
   Date: December 2019
   Title: 
   Purpose: ******************************.
*/

#ifndef RESTAURANTSIMULATIONCLASS_H_
#define RESTAURANTSIMULATIONCLASS_H_

#include <string>
#include "EventClass.h"
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
using namespace std;

class RestaurantSimulationClass
{
    private:
        SortedListClass<EventClass> eventList; // All events happen based on 
                                               // time sequence during opening 
                                               // time
        FIFOQueueClass<EventClass> serveQueue; // Serve queue for arrived 
                                               // customers
        
        // Simulation parameters initialization (read from file)
        int closeTime;          // The total open time of the restaurant (mins)
        float percentNotWait;   // The percentage of customer don't 
                                // like to wait in excessively long line
                                // being served
        int lengthLongLine;     // Min length of excessively long line
        int seedVal;            // Seed value of the pseudo-random number 
                                // generator
        int minArriveTime;      // Min time for next customer to arrive
        int maxArriveTime;      // Max time for next customer to arrive
        double meanServeTime;   // Average time of serving time
        double stdDevServeTime; // Standard deviation of serving time
        
        // Parameters during smulation (change with time)
        int currTime;           // Current time in restaurant, equals the 
                                // time that current event happens
        int customerBeingServed;// Number of customer(s) is being served
        int timeLongStart;      // The start time of excessively long line
        bool directlyServed;

        // Statistics
        int numCustomers;   // Total number of customers that showed up
        double timeBusy;    // Total time the server was busy helping 
                            // customers
        int numInLine;      // Number of customers had to wait in line
        int numLeftNoServe; // Number of customers left without being served
        int longestLine;    // The longest line throughout the simulation
        int afterTime;      // Time served after closed
        int timeLongQueue;  // Total time with excessively long line

    public:
        // Read parameters from fname file and set up them
        bool setUpSimulation(string fname);
 
        // Print out all parameter
        void printParameters();
 
        // Insert inEvent into eventList
        void scheduleEvent(EventClass inEvent);

        // How many events are scheduled currently
        int getNumScheduledEvents();

        // Deal with the first event in eventList. Based on the event type 
        // (arrive/serve/leave), insert new events into eventList.
        void handleNextEvent();

        // Print out all statistics data during the simulation, including:
        // - Total number of customers that showed up during open time
        // - Percentage of time the server was busy helping customers
        //   (total serve time / open times + time for serving after closed)
        //   * 100%
        // - Percentage of customers had to wait in line (excluding the 
        //   customers left without being served) 
        // - The number of customers that arrived, but left due to excessive
        //   line length
        // - The longest the line was throughout the simulation
        // - Time required to serve customers already in queue after the 
        //   restaurant closed
        // - Percentage of time with excessively long line
        void printStatistics();
};

#endif