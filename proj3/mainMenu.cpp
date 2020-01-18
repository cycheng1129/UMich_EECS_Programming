/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: Global function of EECS 402 Fall 2019 Project 3
   Purpose: Get the main menu choices.
*/

#include "mainMenu.h"
#include "cinInt.h"
#include <iostream>
using namespace std;

int mainMenu(void){
    int choice;

    cout << "1. Annotate image with rectangle" << endl;
    cout << "2. Annotate image with pattern from file" << endl;
    cout << "3. Insert another image" << endl;
    cout << "4. Write out current image" << endl;
    cout << "5. Exit the program " << endl;
    cout << "Enter int for main menu choice: ";
    if(!cinInt(choice))
        return 0;

    return choice;
}