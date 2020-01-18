/*
   Programer: Chen-Yu Cheng
   Date: December 2019
   Title: "Template" of SortedListClass of EECS 402 Fall 2019 Project 5
   Purpose: Sort nodes according to its val.
            This class only consists the information of 
            head node and tail node. The nodes inside the 
            list is defined in each LinkedNodeClass.
*/

#include <iostream>
using namespace std;

template<class T>
SortedListClass<T>::SortedListClass(){
    head = NULL;
    tail = NULL;
}

template<class T>
SortedListClass<T>::SortedListClass(const SortedListClass<T> &rhs){
    head = new LinkedNodeClass<T>(
                   rhs.head->getPrev(), 
                   rhs.head->getValue(), 
                   rhs.head->getNext());
    tail = new LinkedNodeClass<T>(
                   rhs.tail->getPrev(), 
                   rhs.tail->getValue(), 
                   rhs.tail->getNext());
}

template<class T>
SortedListClass<T>::~SortedListClass(){
    clear();
}

template<class T>
void SortedListClass<T>::clear(){
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

template<class T>
void SortedListClass<T>::insertValue(const T &valToInsert){
    LinkedNodeClass<T> *nodeIdx = head; // which node to compare with
    LinkedNodeClass<T> *insertNode; // new node with value valToInsert

    // the list is NULL
    if (nodeIdx == NULL){
        insertNode = new LinkedNodeClass<T>(NULL, valToInsert, NULL);
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
            insertNode = new LinkedNodeClass<T>(
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
    insertNode = new LinkedNodeClass<T>(tail, valToInsert, NULL);
    tail = insertNode;
    insertNode->setBeforeAndAfterPointers();
    nodeIdx = NULL;

    return;
}

template<class T>
void SortedListClass<T>::printForward() const{
    LinkedNodeClass<T> *nodeIdx = head;

    cout << "Forward List Contents Follow:" << endl;
    while (nodeIdx != NULL){
        cout << "  " << nodeIdx->getValue() << endl;
        nodeIdx = nodeIdx->getNext();
    }
    cout << "End Of List Contents" << endl;
}

template<class T>
void SortedListClass<T>::printBackward() const{
    LinkedNodeClass<T> *nodeIdx = tail;

    cout << "Backward List Contents Follow:" << endl;
    while (nodeIdx != NULL){
        cout << "  " << nodeIdx->getValue() << endl;
        nodeIdx = nodeIdx->getPrev();
    }
    cout << "End Of List Contents" << endl;
}

template<class T>
bool SortedListClass<T>::removeFront(T &theVal){
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

template<class T>
bool SortedListClass<T>::removeLast(T &theVal){
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
        
template<class T>
int SortedListClass<T>::getNumElems() const{
    int numElems = 0;
    LinkedNodeClass<T> *nodeIdx = head;

    while (nodeIdx != NULL){
        numElems++;
        nodeIdx = nodeIdx->getNext();
    }

    return numElems;
}

template<class T>
bool SortedListClass<T>::getElemAtIndex(const int index, T &outVal) const{
    int i;
    LinkedNodeClass<T> *nodeIdx = head;

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