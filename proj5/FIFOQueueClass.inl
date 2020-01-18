/*
   Programer: Chen-Yu Cheng
   Date: December 2019
   Title: "Template" of FIFOQueueClass of EECS 402 Fall 2019 Project 5
   Purpose: Define a queue (first in first out, FIFO) class and implement
            functions with FIFO methods. This class only consists the
            information of head node and tail node. The nodes inside the 
            list is defined in each LinkedNodeClass.
*/

#include <iostream>
using namespace std;

template<class T>
FIFOQueueClass<T>::FIFOQueueClass(){
    head = NULL;
    tail = NULL;
}

template<class T>
FIFOQueueClass<T>::~FIFOQueueClass(){
    clear();
}

template<class T>
void FIFOQueueClass<T>::enqueue(const T &newItem){
    LinkedNodeClass<T> *newNode;

    newNode = new LinkedNodeClass<T>(tail, newItem, NULL);
    if (head == NULL)
        head = newNode;
    tail = newNode;
    newNode->setBeforeAndAfterPointers();
}

template<class T>
bool FIFOQueueClass<T>::dequeue(T &outItem){
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

template<class T>
void FIFOQueueClass<T>::print() const{
    LinkedNodeClass<T> *nodeIdx = head;

    while (nodeIdx != NULL){
        cout << nodeIdx->getValue() << " ";
        nodeIdx = nodeIdx->getNext();
    }
    cout << endl;
    nodeIdx = NULL;
}

template<class T>
int FIFOQueueClass<T>::getNumElems() const{
    int numElems = 0;
    LinkedNodeClass<T> *nodeIdx = head;

    while (nodeIdx != NULL){
        numElems++;
        nodeIdx = nodeIdx->getNext();
    }

    return numElems;
}

template<class T>
void FIFOQueueClass<T>::clear(){
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