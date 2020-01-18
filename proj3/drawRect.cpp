/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: Global function of EECS 402 Fall 2019 Project 3
   Purpose: Choose one of the three ways to draw Rectangles:
            1. upper-left & lower -right
            2. upper-left, width, & height
            3. center, width, & height
*/

#include "drawRect.h"
#include "constant.h"
#include "isOutOfPixel.h"
#include "cinInt.h"
#include "ColorClass.h"
#include <iostream>
using namespace std;

void drawRect(ColorImageClass inImg){
    int choice;
    int row1 = 0, col1 = 0, row2 = 0, col2 = 0;
    int imgRow = inImg.getRow(), imgCol = inImg.getCol();
    int width, height, halfWidth, halfHeight, rowCen, colCen;
    int rectFill;
    ColorClass rectColor;

    // Select rectangle drawing method
    cout << "1. Specify upper left and lower ";
    cout << "right corners of rectangle " << endl;
    cout << "2. Specify upper left corner and dimensions of rectangle" << endl;
    cout << "3. Specify extent from center of rectangle" << endl;
    cout << "Enter int for rectangle specification method: ";
    if (!cinInt(choice)){
        return;
    }

    switch (choice){
        case TWOPOINTS: // upper-left & lower -right
            cout << "Enter upper left corner row and column: ";
            if (!cinInt(row1) || !cinInt(col1) 
                || isOutOfPixel(row1, col1, imgRow, imgCol))
                return;
            cout << "Enter lower right corner row and column: ";
            if (!cinInt(row2) || !cinInt(col2) 
                || isOutOfPixel(row1, col1, imgRow, imgCol))
                return;
            // check point1 is on the left & upper side of point2
            if (row1 > row2 || col1 > col2){
                cout << "The 1st point should be on the "
                << "left side and upper side of 2nd point. "
                << "Back to main menu," << endl;
                return;
            }
            break;

        case ONEPOINTHW: // upper-left, height, & width
            cout << "Enter upper left corner row and column: ";
            if (!cinInt(row1) || !cinInt(col1) 
                || isOutOfPixel(row1, col1, imgRow, imgCol))
                return;
            cout << "Enter int for number of rows: ";
            if (!cinInt(height) 
                || isOutOfPixel(row1 + height, col1, imgRow, imgCol))
                return;
            cout << "Enter int for number of columns: ";
            if (!cinInt(width) 
                || isOutOfPixel(row1 ,col1 + width, imgRow, imgCol))
                return;
            row2 = row1 + height;
            col2 = col1 + width;
            break;

        case CENHW: // center, height, & width
            cout << "Enter rectangle center row and column: ";
            if (!cinInt(rowCen) || !cinInt(colCen) 
                || isOutOfPixel(rowCen, col1, imgRow, imgCol))
                return;
            cout << "Enter int for half number of rows: ";
            if (!cinInt(halfHeight))
                return;
            row1 = rowCen - halfHeight;
            row2 = rowCen + halfHeight;
            if (isOutOfPixel(row1, col1, imgRow, imgCol)
                || isOutOfPixel(row2, col2, imgRow, imgCol))
                return;
            cout << "Enter int for half number of columns: ";
            if (!cinInt(halfWidth))
                return;
            col1 = colCen - halfWidth;
            col2 = colCen + halfWidth;
            if (isOutOfPixel(row1, col1, imgRow, imgCol)
                || isOutOfPixel(row2, col2, imgRow, imgCol))
                return;
            break;

        default:
            cout << "It's not a valid choice number. "
                 << "Should between 1~3. "
                 << "Back to main menu." << endl;

            return;
    }

    // Select rectangle color
    rectColor.selectColor("rectangle");

    // Select to fill or not
    cout << "1. No" << endl;
    cout << "2. Yes" << endl;
    cout << "Enter int for rectangle fill option: ";
    if (!cinInt(rectFill))
        return;
    
    // draw rectangle at specified location
    inImg.drawRectAtLoc(row1, col1, row2, col2, rectColor, rectFill);

    return;
}