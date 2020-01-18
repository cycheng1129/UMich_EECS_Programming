#ifndef CONSTANT_H_
#define CONSTANT_H_

const int MAX = 255;           // max RGB value
const int MIN = 0;             // min RGB value
const int IGNORESIZE = 1;      // cin ignore size
// main menu choices
const int FAILED = 0;
const int DRAWRECT = 1;        // choice of annotating rectangle
const int ANNOPATTERN = 2;     // choice of annotating pattern
const int INSERTIMG = 3;       // choice of inserting an image
const int SAVE = 4;
const int EXIT = 5;
// draw rectangle choice
const int TWOPOINTS = 1;       // upper-left & lower -right
const int ONEPOINTHW = 2;      // upper-left, height & width
const int CENHW = 3;           // center, width, & height
// color choice
const int CHOICERED = 1;
const int CHOICEGREEN = 2;
const int CHOICEBLUE = 3;
const int CHOICEBLACK = 4;
const int CHOICEWHITE = 5;
// fill or not
const int NOFILL = 1;
const int FILL = 2;

#endif