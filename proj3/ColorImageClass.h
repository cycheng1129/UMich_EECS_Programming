/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: ColorImageClass of EECS 402 Fall 2019 Project 3
   Purpose: Defining the RGB value of a image
*/

#ifndef COLORIMAGECLASS_H_
#define COLORIMAGECLASS_H_

#include "ColorClass.h"
#include <string>

using namespace std;

class ColorImageClass
{
    private:
        string fileType, outFileName;
        int rowNum, colNum;
        ColorClass *img;

    public:
        ColorImageClass();
        // initialize all img[][] in ColorImageClass
        bool initializeTo(string fname, int mainMenuChoice = FAILED);
        // draw rectangle from (row1,col1) to (row2,col2)
        void drawRectAtLoc(int row1, int col1, int row2, int col2, 
                          ColorClass color, int fillChoice);
        // annotate a pattern at (rowLoc,colLoc)
        void inPatAtLoc(ColorImageClass insertImg, 
                       int rowLoc, int colLoc, 
                       ColorClass patternColor);
        // insert an image at (rowPos,colPos), 
        // if the pixel color == transpColor, do nothing
        void inImgAtLoc(ColorImageClass insertImg,
                       int rowPos, int colPos,
                       ColorClass transpColor);
        int getRow();
        int getCol();
        bool addImageTo(ColorImageClass &rhsImg);
        bool addImages(int numImgsToAdd, ColorImageClass imagesToAdd []);
        bool setColorAtLocation(int inRow, int inCol, ColorClass &inColor);
        bool getColorAtLocation(int inRow, int inCol, ColorClass &outColor);
        void saveImg();
        // delete the dynamic allocation of img[][] in ColorImageClass
        void delImg();
};

#endif