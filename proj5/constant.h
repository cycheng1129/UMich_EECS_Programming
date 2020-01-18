#ifndef CONSTANT_H_
#define CONSTANT_H_
#include <string>
using namespace std;

const int FIRSTARRTIME = 0;    // The first customer arrives at time = 0
// Types of events, used to print out 
const string ARRIVE = "arrives";
const string SERVE = "is being served";
const string LEAVE = "leaves";

// Percentage of customer choose to stay or leave due to excessively long line
const int MINPERCENTAGE = 0;
const int MAXPERCENTAGE = 100;

#endif