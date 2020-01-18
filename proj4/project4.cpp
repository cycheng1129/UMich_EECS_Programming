#include <iostream>
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "LIFOStackClass.h"
using namespace std;

//Do NOT remove any of the preprocessor directives in this file.
//They should not affect your ability to write test code in your
//main function below, and they must be in your submitted main
//file exactly as provided to you with the project.
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else 

int main()
{
  //This is just a placeholder main function - it does exceptionally
  //little actual testing, so you'll want to add your own tests here.
  //Feel free to leave your tests in the version of this file you
  //submit, but we will not be running your main function, so the
  //output, etc., of your main doesn't need to match anything from
  //a sample output, etc.
  SortedListClass testList;
  FIFOQueueClass testQueue;
  LIFOStackClass testStack;
  LinkedNodeClass testNode(NULL,1,NULL);
  int idx_in = 2, idx_out = 100, numElems = 0, outVal = 0;
  
  // Test Lists
  cout << "------TESTING OF LIST------" << endl;
  numElems = testList.getNumElems();
  cout << "Num of Elements: " << numElems << endl;
  testList.insertValue(10);
  testList.insertValue(50);
  testList.insertValue(20);
  testList.printForward();
  testList.printBackward();
  numElems = testList.getNumElems();
  cout << "Num of Elements: " << numElems << endl;
  if(testList.getElemAtIndex(idx_in, outVal))
    cout << "Element at index " << idx_in << " (0 based): " << outVal << endl;
  if(!testList.getElemAtIndex(idx_out, outVal))
    cout << "Element at index " << idx_out << ": out of range" << endl;
  testList.removeLast(outVal);
  cout << "Last: " << outVal << endl;
  testList.printForward();
  testList.printBackward();

  cout << "CLEAR" << endl;
  testList.clear();
  testList.printForward();
  testList.insertValue(19);
  testList.insertValue(5);
  testList.insertValue(12);
  testList.printForward();
  testList.printBackward();

  if(testList.getElemAtIndex(idx_in, outVal))
    cout << "Element at index " << idx_in << " (0 based): " << outVal << endl;
  if(!testList.getElemAtIndex(idx_out, outVal))
    cout << "Element at index " << idx_out << ": out of range" << endl;
  testList.removeFront(outVal);
  cout << "Front: " << outVal << endl;
  testList.printForward();
  testList.printBackward();

  // Test Queues
  cout << endl << "-----TESTING OF QUEUE------" << endl;
  numElems = testQueue.getNumElems();
  cout << "Num of Elements: " << numElems << endl;
  testQueue.enqueue(10);
  testQueue.enqueue(50);
  testQueue.enqueue(20);
  cout << "Current queue: " << endl;
  testQueue.print();
  numElems = testQueue.getNumElems();
  cout << "Num of Elements: " << numElems << endl;
  if(testQueue.dequeue(outVal))
    cout << "The next in queue: " << outVal << endl;
  if(testQueue.dequeue(outVal))
    cout << "The next in queue: " << outVal << endl;
  if(testQueue.dequeue(outVal))
    cout << "The next in queue: " << outVal << endl;
  cout << "CLEAR" << endl;
  testQueue.clear();
  if(!testQueue.dequeue(outVal))
    cout << "The queue is empty." << endl;
  cout << "Current queue: " << endl;
  testQueue.print();
  testQueue.enqueue(19);
  testQueue.enqueue(5);
  testQueue.enqueue(12);
  cout << "Current queue: " << endl;
  testQueue.print();
  if(testQueue.dequeue(outVal))
    cout << "The next in queue: " << outVal << endl;

  // Test Stacks
  cout << endl << "------TESTING OF STACK------" << endl;
  numElems = testStack.getNumElems();
  cout << "Num of Elements: " << numElems << endl;
  testStack.push(10);
  testStack.push(50);
  testStack.push(20);
  cout << "Current stack: " << endl;
  testStack.print();
  numElems = testStack.getNumElems();
  cout << "Num of Elements: " << numElems << endl;
  if(testStack.pop(outVal))
    cout << "The top in stack: " << outVal << endl;
  if(testStack.pop(outVal))
    cout << "The top in stack: " << outVal << endl;
  if(testStack.pop(outVal))
    cout << "The top in stack: " << outVal << endl;
  cout << "CLEAR" << endl;
  testStack.clear();
  if(!testStack.pop(outVal))
    cout << "The queue is empty." << endl;
  cout << "Current stack: " << endl;
  testStack.print();
  testStack.push(19);
  testStack.push(5);
  testStack.push(12);
  cout << "Current stack: " << endl;
  testStack.print();
  if(testStack.pop(outVal))
    cout << "The top in stack: " << outVal << endl;

  return 0;
}

#endif