#ifndef PASSWORDSTRENGTH_H
#define PASSWORDSTRENGTH_H

#include <string>
#include <cctype>
using namespace std;

// ====================== PASSWORD STRENGTH CHECK ====================
string checkPasswordStrength(string pass)
{
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
    int length = pass.length();

    for (int i = 0; i < pass.size(); i++) {
        char c = pass[i];
        if (islower(c)) hasLower = true;
        else if (isupper(c)) hasUpper = true;
        else if (isdigit(c)) hasDigit = true;
        else if (!isalnum(c)) hasSpecial = true;
    }

    int strength = 0;
    if (length >= 8) strength++;
    if (hasLower) strength++;
    if (hasUpper) strength++;
    if (hasDigit) strength++;
    if (hasSpecial) strength++;

    if (strength <= 2 || length < 6)
        return "weak";
    else if (strength == 3 || (strength == 4 && length < 8))
        return "medium";
    else
        return "strong";
}

#endif

