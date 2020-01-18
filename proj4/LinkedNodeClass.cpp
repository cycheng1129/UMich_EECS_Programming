/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: LinkedNodeClass of EECS 402 Fall 2019 Project 4
   Purpose: Containing values of this node and pointers to previou and next node.
            Functions: getting values or previous/next nodes,
                       set pointers related to this/prev/next nodes
*/

#include <iostream>
#include "LinkedNodeClass.h"
using namespace std;

LinkedNodeClass::LinkedNodeClass(
                 LinkedNodeClass *inPrev,
                 const int &inVal,
                 LinkedNodeClass *inNext){
    prevNode = inPrev;
    nodeVal = inVal;
    nextNode = inNext;
}

int LinkedNodeClass::getValue() const{
    return nodeVal;
}

LinkedNodeClass* LinkedNodeClass::getNext() const{
    return nextNode;
}

LinkedNodeClass* LinkedNodeClass::getPrev() const{
    return prevNode;
}

void LinkedNodeClass::setNextPointerToNull(){
    nextNode = NULL;
}

void LinkedNodeClass::setPreviousPointerToNull(){
    prevNode = NULL;
}

void LinkedNodeClass::setBeforeAndAfterPointers(){
    if (prevNode != NULL)
        prevNode->nextNode = this;
    if (nextNode != NULL)
        nextNode->prevNode = this;
}