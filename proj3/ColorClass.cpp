/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: ColorClass of EECS 402 Fall 2019 Project 3
   Purpose: Defining the RGB value of a image
*/

#include "ColorClass.h"
#include "cinInt.h"
#include <iostream>
using namespace std;

/* additional function
    if it's out of range, return false*/
bool ColorClass::isOutOfRange(){
    if ((red > MAX || green > MAX || blue > MAX) ||
        (red < MIN || green < MIN || blue < MIN)){
        cout << "Error found when reading color values. "
             << "Found (" 
             << red << "," 
             << green << "," 
             << blue << "). "
             << "Should between 0~255." << endl;
        return false;
    }

    return true;
}

/* colorClass functions */
ColorClass::ColorClass(){
    red = MAX;
    green = MAX;
    blue = MAX;
    isTransparent = false;
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

void ColorClass::selectColor(string inFunc){
    int colorChoice;
    cout << "1. Red" << endl;
    cout << "2. Green" << endl;
    cout << "3. Blue" <<endl;
    cout << "4. Black" << endl;
    cout << "5. White" << endl;
    cout << "Enter int for " << inFunc << " color: ";
    if (!cinInt(colorChoice)){
        return;
    }
    switch (colorChoice){
        case CHOICERED:
            this->setToRed();
            break;

        case CHOICEGREEN:
            this->setToGreen();
            break;

        case CHOICEBLUE:
            this->setToBlue();
            break;

        case CHOICEBLACK:
            this->setToBlack();
            break;

        case CHOICEWHITE:
            this->setToWhite();
            break;

        default:
            cout << "It's not a valid choice number. "
                 << "Should between 1~5. "
                 << "Back to main menu." << endl;
    }
}

// -----Deduction: -10-----
// Class responsibility: image should not be 
// aware of details specific to ColorClass.
bool ColorClass::setTo(ifstream &inFile, int mainMenuChoice){
    int colored;

    // read values of image (ppm file)
    if (mainMenuChoice != ANNOPATTERN){
        inFile >> red >> green >> blue;
        if (inFile.fail()){
            inFile.clear();
            inFile.ignore(IGNORESIZE, '\n');
            cout << "Error! "
                << "Either there is a missing value "
                << "or the value is not an integer." << endl;
            return false;
        }  
        return isOutOfRange();
    }
    // read values of pattern (txt file)
    else{
        inFile >> colored;
        if (inFile.fail()){
            inFile.clear();
            inFile.ignore(IGNORESIZE, '\n');
            cout << "Error! Value should be zero or one." << endl;
        return false;
        }
        else if (colored != 0 && colored != 1){
            cout << "Error! Value should be zero or one." << endl;
            return false;
        }
        else{
            isTransparent = !colored;
            return true;
        }
    }
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

int ColorClass::getRed(){
    return red;
}

int ColorClass::getGreen(){
    return green;
}

int ColorClass::getBlue(){
    return blue;
}

void ColorClass::setTransp(int colored){
    if(colored == 0)
        isTransparent = true;
}

bool ColorClass::getTransp(){
    return isTransparent;
}

bool ColorClass::isTransp(ColorClass transpColor){
    if (this->red == transpColor.red
        && this->green == transpColor.green
        && this->blue == transpColor.blue){
        return true;
    }

    return false;
}