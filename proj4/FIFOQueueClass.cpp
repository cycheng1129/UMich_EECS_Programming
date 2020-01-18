/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: FIFOQueueClass of EECS 402 Fall 2019 Project 4
   Purpose: Define a queue class and implement 
            functions with FIFO methods
*/

#include <iostream>
#include "FIFOQueueClass.h"
using namespace std;

FIFOQueueClass::FIFOQueueClass(){
    head = NULL;
    tail = NULL;
}

FIFOQueueClass::~FIFOQueueClass(){
    clear();
}

void FIFOQueueClass::enqueue(const int &newItem){
    LinkedNodeClass *newNode;

    newNode = new LinkedNodeClass(tail, newItem, NULL);
    if (head == NULL)
        head = newNode;
    tail = newNode;
    newNode->setBeforeAndAfterPointers();
}

bool FIFOQueueClass::dequeue(int &outItem){
    // empty 
    if (head == NULL)
        return false;

    outItem = head->getValue();
    if (head->getNext() != NULL){
        head = head->getNext();
        delete head->getPrev();
        head->setPreviousPointerToNull();
    }
    else // there is only one node in queue
        clear();

    return true;
}

void FIFOQueueClass::print() const{
    LinkedNodeClass *nodeIdx = head;

    while (nodeIdx != NULL){
        cout << nodeIdx->getValue() << " ";
        nodeIdx = nodeIdx->getNext();
    }
    cout << endl;
    nodeIdx = NULL;
}
    
int FIFOQueueClass::getNumElems() const{
    int numElems = 0;
    LinkedNodeClass *nodeIdx = head;

    while (nodeIdx != NULL){
        numElems++;
        nodeIdx = nodeIdx->getNext();
    }

    return numElems;
}

void FIFOQueueClass::clear(){
    // empty queue
    if (head == NULL){
        return;
    }

    // non-empty queue
    while (head->getNext() != NULL){
        head = head->getNext();
        delete head->getPrev();
        head->setPreviousPointerToNull();
    }
    delete head;
    head = NULL;
    tail = NULL;
}