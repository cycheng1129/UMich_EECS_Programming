/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: Global function of EECS 402 Fall 2019 Project 3
   Purpose: Insert another smaller image onto the original image.
*/

#include "ColorClass.h"
#include "annoPattern.h"
#include "cinInt.h"
#include "isOutOfPixel.h"
#include <iostream>
using namespace std;

void insertion(ColorImageClass inImg, 
               ColorImageClass insertImg){
    string insertName;
    int rowLoc, colLoc;
    int imgRow = inImg.getRow(), imgCol = inImg.getCol();
    ColorClass transpColor;

    // Read file
    cout << "Enter string for file name of PPM image to insert: ";
    cin >> insertName;
    if(!insertImg.initializeTo(insertName)){
        return;
    }

    // Select insert position
    cout << "Enter upper left corner to insert image row and column: ";
    if (!cinInt(rowLoc) || !cinInt(colLoc)
        || isOutOfPixel(rowLoc, colLoc, imgRow, imgCol))
        return;

    // Select transparency parts to be which color
    transpColor.selectColor("transparency");

    // insert pattern at specified location
    inImg.inImgAtLoc(insertImg, rowLoc, colLoc, transpColor);

    return;
}