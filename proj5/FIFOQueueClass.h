/*
   Programer: Chen-Yu Cheng
   Date: December 2019
   Title: "Template" of FIFOQueueClass of EECS 402 Fall 2019 Project 5
   Purpose: Define a queue (first in first out, FIFO) class and implement
            functions with FIFO methods. This class only consists the
            information of head node and tail node. The nodes inside the 
            list is defined in each LinkedNodeClass.
*/
#ifndef FIFOQUEUECLASS_H_
#define FIFOQUEUECLASS_H_

#include "LinkedNodeClass.h"

template<class T>
class FIFOQueueClass
{
    private:
        LinkedNodeClass<T> *head; //Points to the first node in a queue, or 
                                  //NULL if queue is empty.
        LinkedNodeClass<T> *tail; //Points to the last node in a queue, or 
                                  //NULL if queue is empty.
    public:
        //Default Constructor. Will properly initialize a queue to
        //be an empty queue, to which values can be added.
        FIFOQueueClass();

        //Destructor. Responsible for making sure any dynamic memory
        //associated with an object is freed up when the object is
        //being destroyed.
        ~FIFOQueueClass();

        //Inserts the value provided (newItem) into the queue.
        void enqueue(const T &newItem);
    
        //Attempts to take the next item out of the queue. If the
        //queue is empty, the function returns false and the state
        //of the reference parameter (outItem) is undefined. If the
        //queue is not empty, the function returns true and outItem
        //becomes a copy of the next item in the queue, which is
        //removed from the data structure.
        bool dequeue(T &outItem);
    
        //Prints out the contents of the queue. All printing is done
        //on one line, using a single space to separate values, and a
        //single newline character is printed at the end.
        void print() const;
    
        //Returns the number of nodes contained in the queue.
        int getNumElems() const;

        //Clears the queue to an empty state without resulting in any
        //memory leaks.
        void clear();
};
#include "FIFOQueueClass.inl"

#endif