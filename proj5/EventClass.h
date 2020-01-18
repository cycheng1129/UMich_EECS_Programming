/*
   Programer: Chen-Yu Cheng
   Date: December 2019
   Title: EventClass of EECS 402 Fall 2019 Project 5
   Purpose: Contains the ordinal number of the customer, the event type 
            (arrive/serve/leave), the time point of the event to happen, which 
            sorting is based on, if the customer is served before leaving
            
*/

#ifndef EVENTCLASS_H_
#define EVENTCLASS_H_

#include <string>
using namespace std;

//The class will be the data type for individual nodes of
//a doubly-linked data structure.
class EventClass
{
    private:
        int custOrdNum;   // The ordinal number of the customer
        string eventType; // One of the thee events: arrive/being served/leave
        int time;         // The time point of the event to happen
        bool isServed;    // The customer is served or not, default: true

    public:
        // Default constructor
        EventClass();
        // The constructor for the event class - it takes in the newly
        // created node's customer ordinal number, event name, time, and
        // boolean to check if the customer leaves with being served 
        // (default is true), and then assigns them.
        EventClass(int inOrdNum,   // The ordinal number of the customer
                   string inEvent, // Event type
                   int inTime,     // The time that the event happens
                   bool served = true);
        // Overloading operator>=, the comparison is done between time, 
        // if the time is the same, the sequence should based on event 
        // type, leave > serve > arrive
        bool operator>=(const EventClass &rhs) const;
        // get the ordinal number of the customer
        int getCustOrdNum();
        // get the event type of this event 
        string getEvent();
        // get the time point of the event
        int getTime();
        // check if the customer leaves with being served
        bool leaveWithServe();
};

#endif