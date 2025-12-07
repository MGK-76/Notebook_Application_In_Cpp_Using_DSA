#ifndef PASSWORDMASK_H
#define PASSWORDMASK_H

#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

string getMaskedPassword()
{
    string password = "";
    char ch;
    cout << "Password: ";
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (password.length() > 0)
            {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            password += ch;
            cout << "*";
        }
    }
    cout << endl;
    return password;
}

#endif

