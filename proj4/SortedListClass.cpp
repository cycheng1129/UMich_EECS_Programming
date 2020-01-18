/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: SortedListClass of EECS 402 Fall 2019 Project 4
   Purpose: 
*/

#include <iostream>
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
using namespace std;

SortedListClass::SortedListClass(){
    head = NULL;
    tail = NULL;
}

SortedListClass::SortedListClass(const SortedListClass &rhs){
    head = new LinkedNodeClass(
                   rhs.head->getPrev(), 
                   rhs.head->getValue(), 
                   rhs.head->getNext());
    tail = new LinkedNodeClass(
                   rhs.tail->getPrev(), 
                   rhs.tail->getValue(), 
                   rhs.tail->getNext());
}

SortedListClass::~SortedListClass(){
    clear();
}

void SortedListClass::clear(){
    // empty list
    if (head == NULL){
        return;
    }

    // non-empty list
    while (head->getNext() != NULL){
        head = head->getNext();
        delete head->getPrev();
        head->setPreviousPointerToNull();
    }
    delete head;
    head = NULL;
    tail = NULL;
}

void SortedListClass::insertValue(const int &valToInsert){
    LinkedNodeClass *nodeIdx = head; // which node to compare with
    LinkedNodeClass *insertNode; // new node with value valToInsert

    // the list is NULL
    if (nodeIdx == NULL){
        insertNode = new LinkedNodeClass(NULL, valToInsert, NULL);
        head = insertNode;
        tail = insertNode;
        
        return;
    }

    // insert at the head or middle of the list
    while (nodeIdx != NULL){ //check the index value exists
        if (valToInsert >= nodeIdx->getValue()){
            nodeIdx = nodeIdx->getNext();
        }
        else{
            insertNode = new LinkedNodeClass(
                                 nodeIdx->getPrev(), 
                                 valToInsert, 
                                 nodeIdx);
            if (insertNode->getPrev() == NULL) // insert at head
                head = insertNode;
            insertNode->setBeforeAndAfterPointers();
            nodeIdx = NULL;

            return;
        }
    }

    // insert at tail
    insertNode = new LinkedNodeClass(tail, valToInsert, NULL);
    tail = insertNode;
    insertNode->setBeforeAndAfterPointers();
    nodeIdx = NULL;

    return;
}

void SortedListClass::printForward() const{
    LinkedNodeClass *nodeIdx = head;

    cout << "Forward List Contents Follow:" << endl;
    while (nodeIdx != NULL){
        cout << "  " << nodeIdx->getValue() << endl;
        nodeIdx = nodeIdx->getNext();
    }
    cout << "End Of List Contents" << endl;
}

void SortedListClass::printBackward() const{
    LinkedNodeClass *nodeIdx = tail;

    cout << "Backward List Contents Follow:" << endl;
    while (nodeIdx != NULL){
        cout << "  " << nodeIdx->getValue() << endl;
        nodeIdx = nodeIdx->getPrev();
    }
    cout << "End Of List Contents" << endl;
}

bool SortedListClass::removeFront(int &theVal){
    // empty list
    if (head == NULL)
        return false;

    theVal = head->getValue();
    if (head->getNext() != NULL){
        head = head->getNext();
        delete head->getPrev();
        head->setPreviousPointerToNull();
    }
    else // there is only one node in list
        clear();

    return true;
}

bool SortedListClass::removeLast(int &theVal){
    // empty list
    if (tail == NULL)
        return false;

    theVal = tail->getValue();
    if (tail->getPrev() != NULL){
        tail = tail->getPrev();
        delete tail->getNext();
        tail->setNextPointerToNull();
    }
    else // there is only one node in list
        clear();

    return true;
}
        
int SortedListClass::getNumElems() const{
    int numElems = 0;
    LinkedNodeClass *nodeIdx = head;

    while (nodeIdx != NULL){
        numElems++;
        nodeIdx = nodeIdx->getNext();
    }

    return numElems;
}

bool SortedListClass::getElemAtIndex(const int index,int &outVal) const{
    int i;
    LinkedNodeClass *nodeIdx = head;

    // check the index is valid
    if (index > getNumElems() - 1 || index < 0){
        nodeIdx = NULL;

        return false;
    }

    for (i = 0; i < index; i++)
        nodeIdx = nodeIdx->getNext();
    outVal = nodeIdx->getValue();
    nodeIdx = NULL;

    return true;
}