/*
   Programer: Chen-Yu Cheng
   Date: November 2019
   Title: Global function of EECS 402 Fall 2019 Project 3
   Purpose: Annotate with a pattern
*/

#ifndef ANNOPATTERN_H_
#define ANNOPATTERN_H_

#include "ColorImageClass.h"

// annotate inImg with insertImg
void annoPattern(ColorImageClass inImg, // the original image
                 ColorImageClass insertImg, // the pattern inserted
                 int mainMenuChoice); // which action is taking now

#endif