#include <iostream>
#include <fstream>
#include <string>
#include "constant.h"
#include "isOutOfPixel.h"
#include "cinInt.h"
#include "mainMenu.h"
#include "drawRect.h"
#include "annoPattern.h"
#include "insertion.h"
#include "ColorClass.h"
#include "ColorImageClass.h"
using namespace std;

/*
    Programer: Chen-Yu Cheng
    Date: November 2019
    Title: EECS 402 Fall 2019 Project 3
    Purpose: Modifying pictures, includes: read/write ppm files,
             drawing rectangles, annotating a pattern, & inserting another image.
             Implement dynamic allocation of array, file input/output,
             and Makefile to compile multiple files.
*/

int main()
{
    string fname, fileType;
    ColorImageClass inImg, insertImg;
    int mainMenuChoice = 0;
    bool initInsertImg = false;

    // Read image from file
    cout << "Enter string for PPM image file name to load: ";
    cin >> fname;
    // check if the image is in right format and initialize inImg
    if (!inImg.initializeTo(fname)){
        return 0;
    }
    
    while(mainMenuChoice != 5){
        // main menu choices:
        mainMenuChoice = mainMenu();

        switch (mainMenuChoice){
            case DRAWRECT: // Annotate with rectangle
                drawRect(inImg);
                if (initInsertImg)
                    insertImg.delImg();
                
                break;

            case ANNOPATTERN: // Annotate with pattern
                annoPattern(inImg, insertImg, mainMenuChoice);
                break;

            case INSERTIMG: // Insert another ppm image
                insertion(inImg, insertImg);
                break;

            case SAVE: // Save the image to file
                inImg.saveImg();
                break;

            case EXIT: // Close the program
                cout << "Thank you for using this program" << endl;
                break;
            
            case FAILED: // not a valid input (input is not a int)
                break;

            default: // not a valid choice (input should between 1~5)
                cout << "It's not a valid choice." << endl;
                break;
        }
    }

    // delete the memory spaces
    inImg.delImg();
    if (initInsertImg){
        insertImg.delImg();
    }

    return 0;
}
