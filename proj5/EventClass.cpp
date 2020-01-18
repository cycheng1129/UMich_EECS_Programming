/*
   Programer: Chen-Yu Cheng
   Date: December 2019
   Title: EventClass of EECS 402 Fall 2019 Project 5
   Purpose: Contains the ordinal number of the customer, the event type 
            (arrive/serve/leave), the time point of the event to happen, which 
            sorting is based on, if the customer is served before leaving
*/

#include <iostream>
#include "EventClass.h"
#include "constant.h"
using namespace std;

EventClass::EventClass(){
    custOrdNum = 0;
    eventType = "";
    time = 0;
    isServed = true;
}

EventClass::EventClass(int inOrdNum, 
                       string inEvent, 
                       int inTime, 
                       bool serve){
    custOrdNum = inOrdNum;
    eventType = inEvent;
    time = inTime;
    isServed = serve;
}

bool EventClass::operator>=(const EventClass &rhs) const{
    if (time > rhs.time)
        return true;

    // If time is the same, the previous customer leave first,
    // then serve the next in queue, lastly the new customer 
    // arrives. So that the new customer can see the correct 
    // number in queue.
    else if (time == rhs.time){
        if (eventType == LEAVE)
            return false;
        else if (eventType == ARRIVE)
            return true;
    }

    return false;
}

int EventClass::getCustOrdNum(){
    return custOrdNum;
}

string EventClass::getEvent(){
    return eventType;
}

int EventClass::getTime(){
    return time;
}

bool EventClass::leaveWithServe(){
    return isServed;
}