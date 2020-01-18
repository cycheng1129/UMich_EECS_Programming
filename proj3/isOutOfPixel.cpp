/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: Global function of EECS 402 Fall 2019 Project 3
   Purpose: Check if the pixel is out of range
*/

#include "isOutOfPixel.h"
#include "iostream"
using namespace std;

bool isOutOfPixel(int inRow, int inCol, int imgRow, int imgCol){
    if (inRow < 0 || inCol < 0 || inRow > imgRow -1 || inCol > imgCol - 1){
        cout << "The position is outside of the image ("
             << imgRow << "*" << imgCol << "). "
             << "Back to main menu." << endl;
            return true;
    }

    return false;
}