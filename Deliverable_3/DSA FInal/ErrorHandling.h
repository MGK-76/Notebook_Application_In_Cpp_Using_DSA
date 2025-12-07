#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <iostream>
using namespace std;

void clearInputBuffer()
{
    cin.clear();          
    cin.ignore(9999, '\n');  
}

#endif
