/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Timer.h"

using namespace std;

namespace sdds
{
    // directly cpoied from notes
    void Timer::start() 
    {
        startTime = chrono::steady_clock::now();
    }

    // Stops the timer (takes the current timestamp) and returns how many nanoseconds passed since the timer has started
    long long Timer::stop() 
    {
        endTime = chrono::steady_clock::now();
        chrono::nanoseconds duration = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);

        return static_cast<long long>(duration.count());
    }
}
