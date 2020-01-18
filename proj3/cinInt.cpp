/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: Global function of EECS 402 Fall 2019 Project 3
   Purpose: Input an int type vaiable and check if cin fails
*/

#include "cinInt.h"
#include "constant.h"
#include <iostream>
using namespace std;

// cin an int type variable, check if it's a positive int
bool cinInt(int &varName){
    cin >> varName;
    if (cin.fail() || varName < 0){
        cin.clear();
        cin.ignore(IGNORESIZE, '\n');
        cout << "It's not a valid input. Should input a positive integer. "
             << "Back to main menu." << endl;
        return false;
    }
    return true;
}