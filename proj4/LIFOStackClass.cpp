/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: LIFOStackClass of EECS 402 Fall 2019 Project 4
   Purpose: Define a stack class and implement 
            functions with LIFO methods
*/

#include <iostream>
#include "LIFOStackClass.h"
using namespace std;

LIFOStackClass::LIFOStackClass(){
    head = NULL;
    tail = NULL;
}

LIFOStackClass::~LIFOStackClass(){
    clear();
}

void LIFOStackClass::push(const int &newItem){
    LinkedNodeClass *newNode;

    newNode = new LinkedNodeClass(tail, newItem, NULL);
    if (head == NULL)
        head = newNode;
    tail = newNode;
    newNode->setBeforeAndAfterPointers();
}

bool LIFOStackClass::pop(int &outItem){
    if (tail == NULL)
        return false;

    outItem = tail->getValue();
    if (tail->getPrev() != NULL){
        tail = tail->getPrev();
        delete tail->getNext();
        tail->setNextPointerToNull();
    }
    else // there is only one node in stack
        clear();

    return true;
}

void LIFOStackClass::print() const{
    LinkedNodeClass *nodeIdx = head;

    while (nodeIdx != NULL){
        cout << nodeIdx->getValue() << " ";
        nodeIdx = nodeIdx->getNext();
    }
    cout << endl;
    nodeIdx = NULL;
}

int LIFOStackClass::getNumElems() const{
    int numElems = 0;
    LinkedNodeClass *nodeIdx = head;

    while (nodeIdx != NULL){
        numElems++;
        nodeIdx = nodeIdx->getNext();
    }

    return numElems;
}

void LIFOStackClass::clear(){
    // empty stack
    if (head == NULL){
        return;
    }

    // non-empty stack
    while (head->getNext() != NULL){
        head = head->getNext();
        delete head->getPrev();
        head->setPreviousPointerToNull();
    }
    delete head;
    head = NULL;
    tail = NULL;
}