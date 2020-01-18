/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: ColorClass of EECS 402 Fall 2019 Project 3
   Purpose: Defining the RGB value of a image
*/

#ifndef COLORCLASS_H_
#define COLORCLASS_H_

#include "constant.h"
#include <string>
#include <fstream>
using namespace std;

class ColorClass
{
    private:
        int red, green, blue;
        bool isTransparent;
        // check the color range, if out of range: false
        bool isOutOfRange();

    public:
        // initialize to full white
        ColorClass();
        ColorClass(int inRed, int inGreen, int inBlue);
        void setToBlack();
        void setToRed();
        void setToGreen();
        void setToBlue();
        void setToWhite();
        // select color options, the purpose of inFunc is to cout properly
        void selectColor(string inFunc);

        // -----Deduction: -10-----
        // Class responsibility: image should not be 
        // aware of details specific to ColorClass.
        // read from inFile and set the colors
        bool setTo(ifstream &inFile, int mainMenuChoice);
        bool setTo(int inRed, int inGreen, int inBlue);
        bool setTo(ColorClass &inColor);
        bool addColor(ColorClass &rhs);
        bool subtractColor(ColorClass &rhs);
        bool adjustBrightness(double adjFactor);
        void printComponentValues();
        int getRed();
        int getGreen();
        int getBlue();
        // if the value in a pattern is 0, isTransparent = true
        void setTransp(int colored);
        // get bool value of isTransparent in ColorClass
        bool getTransp();
        // if red, green, and blue of the insert
        // ColorImage == transpColor, return true
        bool isTransp(ColorClass transpColor);
};

#endif