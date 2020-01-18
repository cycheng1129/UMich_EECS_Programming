/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: Global function of EECS 402 Fall 2019 Project 3
   Purpose: Annotate with a pattern
*/

#include "annoPattern.h"
#include "cinInt.h"
#include "isOutOfPixel.h"
#include "ColorClass.h"
#include <iostream>
using namespace std;

// annotate inImg with insertImg
void annoPattern(ColorImageClass inImg, 
                 ColorImageClass insertImg, 
                 int mainMenuChoice){
    string insertName;
    int rowLoc, colLoc;
    int imgRow = inImg.getRow(), imgCol = inImg.getCol();
    ColorClass patternColor;

    // Read file
    cout << "Enter string for file name containing pattern: ";
    cin >> insertName;
    if(!insertImg.initializeTo(insertName, mainMenuChoice)){
        return;
    }

    // Select position
    cout << "Enter upper left corner of pattern row and column: ";
    if (!cinInt(rowLoc) || !cinInt(colLoc)
        || isOutOfPixel(rowLoc, colLoc, imgRow, imgCol))
        return;

    // Select pattern color
    patternColor.selectColor("pattern");

    // insert pattern at specified location
    inImg.inPatAtLoc(insertImg, rowLoc, colLoc, patternColor);

    return;
}