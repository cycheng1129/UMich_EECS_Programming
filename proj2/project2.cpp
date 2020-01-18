#include <iostream>
using namespace std;

/*
   Programer: Chen-Yu Cheng
   Date: October 2019
   Title: EECS 402 Fall 2019 Project 2
   Purpose: Implement object-oriented principles.
            There are three classes, 
            ColorClass: the RGB value
            RowColumnClass: the pixel position
            ColorImageClass: the RGB value at a specific pixel
*/

/* global constant */
const int MAX = 1000;          // max RGB value
const int MIN = 0;             // min RGB value
const int DEFAULTIDX = -99999; // default index
const int IMGROW = 10;
const int IMGCOL = 18;

/* global function prototypes and documentation */
// check the pixel range, if out of range: false
bool isOutOfPixel(int inRow, int inCol);

/* class definitions */
class ColorClass
{
    private:
        int red, green, blue;
        // check the color range, if out of range: true
        bool isOutOfRange();

    public:
        ColorClass(); // initialize to full white
        ColorClass(int inRed, int inGreen, int inBlue);
        void setToBlack();
        void setToRed();
        void setToGreen();
        void setToBlue();
        void setToWhite();
        bool setTo(int inRed, int inGreen, int inBlue);
        bool setTo(ColorClass &inColor);
        bool addColor(ColorClass &rhs);
        bool subtractColor(ColorClass &rhs);
        bool adjustBrightness(double adjFactor);
        void printComponentValues();
};

class RowColumnClass
{
    private:
        int row, col;

    public:
        RowColumnClass(); // initialize to [-99999,-99999]
        RowColumnClass(int inRow, int inCol);
        void setRowCol(int inRow, int inCol);
        void setRow(int inRow);
        void setCol(int inCol);
        int getRow();
        int getCol();
        void addRowColTo(RowColumnClass &inRowCol);
        void printRowCol();
};

class ColorImageClass
{
    private:
        ColorClass img[IMGROW][IMGCOL];

    public:
        ColorImageClass();
        void initializeTo(ColorClass &inColor);
        bool addImageTo(ColorImageClass &rhsImg);
        bool addImages(int numImgsToAdd, ColorImageClass imagesToAdd []);
        bool setColorAtLocation(RowColumnClass &inRowCol, ColorClass &inColor);
        bool getColorAtLocation(RowColumnClass &inRowCol, ColorClass &outColor);
        void printImage();
};

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
    ColorClass testColor;
    RowColumnClass testRowCol;
    RowColumnClass testRowColOther(111, 222);
    ColorImageClass testImage;
    ColorImageClass testImages[3];

    //Test some basic ColorClass operations...
    cout << "Initial: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.setToBlack();
    cout << "Black: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.setToGreen();
    cout << "Green: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.adjustBrightness(0.5);
    cout << "Dimmer Green: ";
    testColor.printComponentValues();
    cout << endl;

    //Test some basic RowColumnClass operations...
    cout << "Want defaults: ";
    testRowCol.printRowCol();
    cout << endl;

    testRowCol.setRowCol(2, 8);
    cout << "Want 2,8: ";
    testRowCol.printRowCol();
    cout << endl;

    cout << "Want 111, 222: ";
    testRowColOther.printRowCol();
    cout << endl;

    testRowColOther.setRowCol(4, 2);
    testRowCol.addRowColTo(testRowColOther);
    cout << "Want 6,10: ";
    testRowCol.printRowCol();
    cout << endl;

    //Test some basic ColorImageClass operations...
    testColor.setToRed();
    testImage.initializeTo(testColor);

    testRowCol.setRowCol(555, 5);
    cout << "Want: Color at [555,5]: Invalid Index!" << endl;
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
        testColor.printComponentValues();
    else
        cout << "Invalid Index!";
    cout << endl;

    testRowCol.setRow(4);
    cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
        testColor.printComponentValues();
    else
        cout << "Invalid Index!";
    cout << endl;

    //Set up an array of images of different colors
    testColor.setToRed();
    testColor.adjustBrightness(0.25);
    testImages[0].initializeTo(testColor);
    testColor.setToBlue();
    testColor.adjustBrightness(0.75);
    testImages[1].initializeTo(testColor);
    testColor.setToGreen();
    testImages[2].initializeTo(testColor);

    //Modify a few individual pixel colors
    testRowCol.setRowCol(4, 2);
    testColor.setToWhite();
    testImages[1].setColorAtLocation(testRowCol, testColor);

    testRowCol.setRowCol(2, 4);
    testColor.setToBlack();
    testImages[2].setColorAtLocation(testRowCol, testColor);

    //Add up all images in testImages array and assign result
    //to the testImage image
    testImage.addImages(3, testImages);
  
    //Check some certain values
    cout << "Added values:" << endl;
    for (int colInd = 0; colInd < 8; colInd += 2){ 
        testRowCol.setRowCol(4, colInd);
        cout << "Color at ";
        testRowCol.printRowCol();
        cout << ": ";
        if (testImage.getColorAtLocation(testRowCol, testColor))
            testColor.printComponentValues();
        else
            cout << "Invalid Index!";
        cout << endl;
    }
  
    for (int rowInd = 0; rowInd < 8; rowInd += 2){
        testRowCol.setRowCol(rowInd, 4);
        cout << "Color at ";
        testRowCol.printRowCol();
        cout << ": ";
        if (testImage.getColorAtLocation(testRowCol, testColor))
            testColor.printComponentValues();
        else
            cout << "Invalid Index!";
        cout << endl;
    }
  
    cout << "Printing entire test image:" << endl;
    testImage.printImage();

    return 0;
}
#endif

/* global function definitions*/
bool isOutOfPixel(int inRow, int inCol){
    if (inRow > IMGROW - 1 || inCol > IMGCOL - 1 ||
        inRow < 0 || inCol < 0)
        return true;

    return false;
}

/* class member function definitions */
/* additional function
    check if it's out of range, if yes, clip it and return true*/
bool ColorClass::isOutOfRange(){
    if ((red > MAX || green > MAX || blue > MAX) ||
        (red < MIN || green < MIN || blue < MIN))
    {
        /* Another way to write:
        red = red > MAX ? MAX : red;
        red = red < MIN ? MIN : red; */
        if (red > MAX)
            red = MAX;
        else if (red < MIN)
            red = MIN;
        if (green > MAX)
            green = MAX;
        else if (green < MIN)
            green = MIN;
        if (blue > MAX)
            blue = MAX;
        else if (blue < MIN)
            blue = MIN;
        return true;
    }

    return false;
}

/* colorClass functions */
ColorClass::ColorClass(){
    red = MAX;
    green = MAX;
    blue = MAX;
}

ColorClass::ColorClass(int inRed, int inGreen, int inBlue):
    red(inRed), green(inGreen), blue(inBlue){
    isOutOfRange();
}

void ColorClass::setToBlack(){
    red = MIN;
    green = MIN;
    blue = MIN;
}

void ColorClass::setToRed(){
    red = MAX;
    green = MIN;
    blue = MIN;
}

void ColorClass::setToGreen(){
    red = MIN;
    green = MAX;
    blue = MIN;
}

void ColorClass::setToBlue(){
    red = MIN;
    green = MIN;
    blue = MAX;
}

void ColorClass::setToWhite(){
    red = MAX;
    green = MAX;
    blue = MAX;
}

// if clipped, return true
bool ColorClass::setTo(int inRed, int inGreen, int inBlue){
    red = inRed;
    green = inGreen;
    blue = inBlue;
    
    return isOutOfRange();
}

bool ColorClass::setTo(ColorClass &inColor){
    red = inColor.red;
    green = inColor.green;
    blue = inColor.blue;

    return isOutOfRange();
}

bool ColorClass::addColor(ColorClass &rhs){
    red += rhs.red;
    green += rhs.green;
    blue += rhs.blue;
    
    return isOutOfRange();
}

bool ColorClass::subtractColor(ColorClass &rhs){
    red -= rhs.red;
    green -= rhs.green;
    blue -= rhs.blue;

    return isOutOfRange();
}

bool ColorClass::adjustBrightness(double adjFactor){
    red = static_cast<int>(red*adjFactor);
    green = static_cast<int>(green*adjFactor);
    blue = static_cast<int>(blue*adjFactor);

    return isOutOfRange();;
}

void ColorClass::printComponentValues(){
    cout << "R: " << red << " G: " << green << " B: " << blue;
}

/* RowColumnClass functions */
RowColumnClass::RowColumnClass(){
    row = col = DEFAULTIDX;
}

RowColumnClass::RowColumnClass(int inRow, int inCol):
    row(inRow), col(inCol)
    {;}

void RowColumnClass::setRowCol(int inRow, int inCol){
    row = inRow;
    col = inCol;
}

void RowColumnClass::setRow(int inRow){
    row = inRow;
}

void RowColumnClass::setCol(int inCol){
    col = inCol;
}

int RowColumnClass::getRow(){
    return row;
}

int RowColumnClass::getCol(){
    return col;
}

void RowColumnClass::addRowColTo(RowColumnClass &inRowCol){
    row += inRowCol.row;
    col += inRowCol.col;
}

void RowColumnClass::printRowCol(){
    cout << "[" << row << "," << col << "]";
}

/* ColorImageClass functions */
ColorImageClass::ColorImageClass(){
    for (int i = 0; i < IMGROW; i++){
        for (int j = 0; j < IMGCOL; j++){
            img[i][j].setToBlack();
        }
    }
}

void ColorImageClass::initializeTo(ColorClass &inColor){
    for (int i = 0; i < IMGROW; i++){
        for (int j = 0; j < IMGCOL; j++){
            img[i][j].setTo(inColor);
        }
    }
}

bool ColorImageClass::addImageTo(ColorImageClass &rhsImg){
    bool isClipped = false;

    for (int i = 0; i < IMGROW; i++){
        for (int j = 0; j < IMGCOL; j++){
            isClipped |= img[i][j].addColor(rhsImg.img[i][j]);
        }
    }

    return isClipped;  
}

bool ColorImageClass::addImages(
                    int numImgsToAdd, 
                    ColorImageClass imagesToAdd[]){
    bool isClipped = false;
    int imgNum = 0; // which img is being added
    ColorClass black(0, 0, 0);
    this->initializeTo(black);

    for (imgNum = 0; imgNum < numImgsToAdd; imgNum++){
        // use addImageTo() to change values of an image
        isClipped |= this->addImageTo(imagesToAdd[imgNum]);
        // use addColor() to change value of a pixel
        /*for (int i = 0; i < IMGROW; i++){
            for (int j = 0; j < IMGCOL; j++){
                // initialize to all black
                if (imgNum == 0)
                    img[i][j].setToBlack();
                isClipped |= img[i][j].addColor(imagesToAdd[imgNum].img[i][j]);
            }
        }*/
    }

    return isClipped;
}

// if the image is not modified in ANY way, returns false
bool ColorImageClass::setColorAtLocation(
                    RowColumnClass &inRowCol, 
                    ColorClass &inColor){    
    // check if the pixel is outof range
    if (isOutOfPixel(inRowCol.getRow(), inRowCol.getCol()))
        return false;
    img[inRowCol.getRow()][inRowCol.getCol()].setTo(inColor);

    return true;
}

// If the row/column is invalid, returns false
bool ColorImageClass::getColorAtLocation(
                    RowColumnClass &inRowCol, 
                    ColorClass &outColor){
    // check if the pixel is outof range
    if (isOutOfPixel(inRowCol.getRow(), inRowCol.getCol()))
        return false;
    outColor.setTo(img[inRowCol.getRow()][inRowCol.getCol()]);

    return true;
}

void ColorImageClass::printImage(){
    for (int i = 0; i < IMGROW; i++){
        for (int j = 0; j < IMGCOL; j++){
            img[i][j].printComponentValues();
            if (j != IMGCOL - 1)
                cout << "--";
        }
        cout << endl;
    }
}