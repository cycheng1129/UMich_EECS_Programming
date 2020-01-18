/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: ColorClass of EECS 402 Fall 2019 Project 3
   Purpose: Defining the RGB value of a image
*/

#include "ColorImageClass.h"
#include "ColorClass.h"
#include "constant.h"
#include "isOutOfPixel.h"
#include <iostream>
#include <fstream>
using namespace std;

/* ColorImageClass functions */
ColorImageClass::ColorImageClass(){
    colNum = 0;
    rowNum = 0;
}

bool ColorImageClass::initializeTo(string fname, int mainMenuChoice){
    ifstream inFile;
    ofstream outFile;
    bool isValid = true;
    int i, j;
    int max = 0;
    ColorClass index;
    cout << "Reading..." << endl;
    string notInRange;

    inFile.open(fname.c_str());
    if (inFile.fail()){
        cout << "Unable to open input file!\n";
        return false;
    }

    // get file type, image size, and MAX value
    if (!inFile.eof()){
        if (mainMenuChoice != ANNOPATTERN){
            inFile >> fileType;
            // check file type
            if (fileType != "P3"){
                cout << "Error found when trying to read magic number - "
                     << "expected P3 but found " << fileType << endl;
                isValid = false;
            }
        }

        inFile >> colNum >> rowNum;
        // check column and row inputs
        if (inFile.fail()){
            cout << "Error found when trying to read numbers "
                 << "of column and row - "
                 << "must be an integer." << endl;
                isValid = false;
        }
        else if (colNum <= 0 || rowNum <= 0){
            cout << "Error found when trying to read numbers "
                 << "of column and row - "
                 << "must be greater than 0, "
                 << "but found (" << colNum << "," << rowNum << ")" << endl;
                isValid = false;
        }

        if (mainMenuChoice != ANNOPATTERN){
            inFile >> max;
            // check max value
            if (max != MAX){
                cout << "Error found when trying to read "
                    << "the max value of color - must equal to 255" << endl;
                isValid = false;
            }
        }
    }

    if (isValid){
        // read each pixel value to ColorClass
        img = new ColorClass[rowNum * colNum];
        while (!inFile.eof()){
            for (i = 0; i < rowNum; i++){
                for (j = 0; j < colNum; j++){
                    // -----Deduction: -10-----
                    // Class responsibility: image should not be 
                    // aware of details specific to ColorClass.
                    // set color and check the value (0~255)
                    if (!img[i * colNum + j].setTo(inFile, mainMenuChoice)){
                        cout << "Error pixel at "
                             << "(" << i << ", " << j << "). " << endl
                             << "Back to main menu." << endl;
                        return false;
                    }
                }
            }
            inFile >> notInRange; // read redundant values in the file
        }
    }

    inFile.close();

    return isValid;
}

void ColorImageClass::drawRectAtLoc(
                     int row1, int col1, int row2, int col2, 
                     ColorClass color, int fillChoice){
    int i, j;

    switch (fillChoice){
        case NOFILL:
            // left side
            j = col1;
            for (i = row1; i <= row2; i++){
                this->setColorAtLocation(i, j, color);
            }
            // right side
            j = col2;
            for (i = row1; i <= row2; i++){
                this->setColorAtLocation(i, j, color);
            }
            // upper side
            i = row1;
            for (j = col1 + 1; j < col2; j++){
                this->setColorAtLocation(i, j, color);
            }
            // lower side
            i = row2;
            for (j = col1 + 1; j < col2; j++){
                this->setColorAtLocation(i, j, color);
            }
            break;

        case FILL:
            for (i = row1; i <= row2; i++){
                for (j = col1; j <= col2; j++){
                    this->setColorAtLocation(i, j, color);
                }
            }
            break;

        default:
            cout << "It's not a valid choice number. "
                 << "Should be 1 or 2. "
                 << "Back to main menu." << endl;
    }
    
    return;
}

void ColorImageClass::inPatAtLoc(
                     ColorImageClass insertImg, 
                     int rowLoc, int colLoc, 
                     ColorClass patternColor){
    int i, j;
    int rowRightLimit = insertImg.rowNum < (rowNum - rowLoc)
                        ? insertImg.rowNum : (rowNum - rowLoc);
    int cowLowLimit = insertImg.colNum < (colNum - colLoc)
                      ? insertImg.colNum : (colNum - colLoc);
    for (i = 0; i < rowRightLimit; i++){
        for (j = 0; j < cowLowLimit; j++){
            if (!insertImg.img[i * insertImg.colNum + j].getTransp()){
                img[(rowLoc + i) * colNum + (colLoc + j)].setTo(patternColor);
            }
        }
    }
    
    return;
}

void ColorImageClass::inImgAtLoc(
                     ColorImageClass insertImg, 
                     int rowLoc, int colLoc, 
                     ColorClass transpColor){
    int i, j;
    int rowRightLimit = insertImg.rowNum < (rowNum - rowLoc)
                        ? insertImg.rowNum : (rowNum - rowLoc);
    int cowLowLimit = insertImg.colNum < (colNum - colLoc)
                      ? insertImg.colNum : (colNum - colLoc);
    for (i = 0; i < rowRightLimit; i++){
        for (j = 0; j < cowLowLimit; j++){
            if (!insertImg.img[i * insertImg.colNum + j].isTransp(transpColor)){
                img[(i + rowLoc) * colNum + (j + colLoc)].
                setTo(insertImg.img[i * insertImg.colNum + j]);
            }
        }
    }
    
    return;
}

int ColorImageClass::getRow(){
    return rowNum;
}

int ColorImageClass::getCol(){
    return colNum;
}

bool ColorImageClass::addImageTo(ColorImageClass &rhsImg){
    bool isClipped = false;

    for (int i = 0; i < rowNum; i++){
        for (int j = 0; j < colNum; j++){
            isClipped |= img[i * colNum + j].addColor(rhsImg.img[i * colNum + j]);
        }
    }

    return isClipped;  
}

bool ColorImageClass::addImages(int numImgsToAdd, 
                                ColorImageClass imagesToAdd[]){
    bool isClipped = false;
    int imgNum = 0; // which img is being added
    ColorClass black(0, 0, 0);
    // this->initializeTo(black);

    for (imgNum = 0; imgNum < numImgsToAdd; imgNum++){
        isClipped |= this->addImageTo(imagesToAdd[imgNum]);
    }

    return isClipped;
}

// if the image is not modified in ANY way, returns false
bool ColorImageClass::setColorAtLocation(
                      int inRow, int inCol, 
                      ColorClass &inColor){    
    // check if the pixel is outof range
    if (isOutOfPixel(inRow, inCol, rowNum, colNum))
        return false;
    img[inRow * colNum + inCol].setTo(inColor);

    return true;
}

// If the row/column is invalid, returns false
bool ColorImageClass::getColorAtLocation(
                      int inRow, int inCol, 
                      ColorClass &outColor){
    // check if the pixel is outof range
    if (isOutOfPixel(inRow, inCol, rowNum, colNum))
        return false;
    outColor.setTo(img[inRow * colNum + inCol]);

    return true;
}

void ColorImageClass::saveImg(){
    ofstream outFile;

    cout << "Enter string for PPM file name to output: ";
    cin >> outFileName;
    outFile.open(outFileName.c_str());
    if (outFile.fail()){
        cout << "Unable to open output file!\n";

        return;
    }
    else{
        outFile << fileType << endl;
        outFile << colNum << " " << rowNum << endl;
        outFile << MAX << endl;
        for (int i = 0; i < rowNum; i++){
            for (int j = 0; j < colNum; j++){
                outFile << img[i * colNum + j].getRed() << " ";
                outFile << img[i * colNum + j].getGreen() << " ";
                outFile << img[i * colNum + j].getBlue() << " ";
            }
            outFile << endl;
        }
    }
    outFile.close();
}

void ColorImageClass::delImg(){
    delete [] img;
}