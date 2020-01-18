#include <iostream>
using namespace std;

/*
   Programer: Chen-Yu Cheng
   Date: September 2019
   Title: EECS 402 Fall 2019 Project 1
   Purpose: Accrue interest for an investment account
*/

/* global constant */
const float MIN_RANGE = 1000.00;
const float MAX_RANGE = 15000.00;
const float MIN_RATE = 0.15 * 0.01;
const float STAND_RATE = 0.225 * 0.01;
const float MAX_RATE = 0.4 * 0.01;

/* global function prototypes and documentation */
bool accrueInterest(
    double &balanceAmt,
    const int numMonths,
    const bool doPrintEachMonth);
bool accrueOneMonthsInterest(
    double &balanceAmt,
    const bool doPrintInfo);

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
    double balanceAmt;
    int numMonths;
    char print;
    bool isPrint = false;

    /* Input variables */
    cout << "Enter the initial balance of the account: ";
    cin >> balanceAmt;
    cout << "Enter the number of months to accrue interest: ";
    cin >> numMonths;
    cout << "Show month-by-month results - 'y' for yes, any other for no: ";
    cin >> print;
    if (print == 'y')
        isPrint = true;

    /* Calculate the interests. 
       If the inputs are illogical, ends the function */
    if(!accrueInterest(balanceAmt, numMonths, isPrint)){
        return 0;
    }

    return 0;
}
#endif

/* global function definitions*/
bool accrueInterest(
    double &balanceAmt,
    const int numMonths,
    const bool doPrintEachMonth
    )
{
    double initBalance = balanceAmt;
    int i;

    /* Check input parameters are logial or not */
    if (numMonths <= 0){
        cout << "ERROR in accrueInterest: ";
        cout << "numMonths must be >" ;
        cout << " 0, but the value " << numMonths;
        cout << " was provided! " << endl;
        cout << "Sorry, an error was detected. ";
        cout << "Unable to provide results!" << endl;
        
        return false;
    }

    /* Calculate the interests of each month */
    for (i = 0; i < numMonths; i++){
        if(!accrueOneMonthsInterest(balanceAmt, doPrintEachMonth))
            return false;
    }

    /* Print the total interests over the months */
    cout << "Interest accrued for " << numMonths << " months!" << endl << endl;
    cout << "Initial balance: " << initBalance << endl;
    cout << "Total interest accrued: " << balanceAmt - initBalance << endl;
    cout << "Final balance: " << balanceAmt << endl;

    return true;
}

bool accrueOneMonthsInterest(
    double &balanceAmt,
    const bool doPrintInfo
    )
{
    double rate, interest;

    /* Check input parameters are logial or not */
    if (balanceAmt < 0.0){
        cout << "ERROR in accrueOneMonthsInterest: ";
        cout << "balanceAmt must be >= 0, ";
        cout << "but the value " << balanceAmt;
        cout << " was provided! " << endl;
        cout << "Sorry, an error was detected. ";
        cout << "Unable to provide results!" << endl;
        
        return false;
    }
    
    /* Check the interest rate */
    if (balanceAmt < MIN_RANGE)
        rate = MIN_RATE;
    else if (balanceAmt >= MAX_RANGE)
        rate = MAX_RATE;
    else 
        rate = STAND_RATE;
        
    interest = balanceAmt * rate;

    /* Calculation of each month */
    if (doPrintInfo)
    {
        cout << "Accruing interest for 1 month: " << endl;
        cout << "  Initial balance: " << balanceAmt << endl;
        cout << "  Initial rate: " << rate << endl;
        cout << "  Interest accrued: " << interest << endl;
        cout << "  New balance: " << balanceAmt + interest << endl;
    }
    balanceAmt += interest;
    
    return true;
}

