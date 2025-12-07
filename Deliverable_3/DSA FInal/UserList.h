#ifndef USERLIST_H
#define USERLIST_H

#include <iostream>
#include <string>
#include "ProfileList.h"
#include "PageList.h"
#include "CategoryList.h"
#include "NotificationQueue.h"
#include "ContactList.h"
#include "FailedAttemptsStack.h"
#include "PasswordStrength.h"
using namespace std;

// ====================== ACCOUNT MANAGEMENT =========================
// Struct is now moved BELOW the classes so it can contain them
struct User
{
    string username;
    string password;
    
    // DATA ISOLATION: These lists now belong to the specific user
    ProfileList profile;
    PageList pages;
    NotebookCategories categories;
    NotificationQueue notifications;
    ContactList contacts;

    User *next;
};

class UserList
{
private:
    User *head;
    FailedAttemptsStack failedAttempts;

public:
    UserList() { head = nullptr; }

    void signUp(string uname, string pass)
    {
        string strength = checkPasswordStrength(pass);
        
        if (strength == "weak")
        {
            cout << "\nPassword is too weak! Please try again with a stronger password.\n";
            cout << "Password should be at least 6 characters and include uppercase, lowercase, digits, or special characters.\n";
            return;
        }
        else if (strength == "medium")
        {
            cout << "\nWarning: Password strength is medium. Consider using a stronger password for better security.\n";
        }
        else if (strength == "strong")
        {
            cout << "\nPassword strength is strong! Good choice.\n";
        }

        User *temp = head;
        while (temp)
        {
            if (temp->username == uname)
            {
                cout << "\nUsername already exists! Try another.\n";
                return;
            }
            temp = temp->next;
        }
        // Initialize new user. The constructors of the member classes 
        // (ProfileList, PageList, etc.) are called automatically.
        User *newUser = new User; 
        newUser->username = uname;
        newUser->password = pass;
        newUser->next = nullptr;

        if (!head)
            head = newUser;
        else
        {
            User *ptr = head;
            while (ptr->next)
                ptr = ptr->next;
            ptr->next = newUser;
        }
        cout << "\nAccount created successfully!\n";
    }

    // UPDATED: Now returns a pointer to the User node
    User* login(string uname, string pass)
    {
        int attempts = failedAttempts.countAttempts(uname);
        if (attempts >= 3)
        {
            cout << "\nAccount locked! Too many failed login attempts. Maximum 3 attempts allowed.\n";
            return nullptr;
        }

        User *temp = head;
        while (temp)
        {
            if (temp->username == uname && temp->password == pass)
            {
                failedAttempts.clearAttempts(uname);
                cout << "\nLogin successful! Welcome, " << uname << "!\n";
                return temp; // Return the user object so we can access THEIR data
            }
            temp = temp->next;
        }
        
        failedAttempts.push(uname);
        attempts = failedAttempts.countAttempts(uname);
        cout << "\nInvalid username or password.\n";
        cout << "Failed attempts: " << attempts << "/3\n";
        if (attempts >= 3)
        {
            cout << "Account locked due to too many failed attempts!\n";
        }
        return nullptr;
    }

    void displayUsers()
    {
        if (!head)
        {
            cout << "\nNo users registered yet.\n";
            return;
        }
        cout << "\nRegistered Users:\n";
        User *temp = head;
        while (temp)
        {
            cout << " - " << temp->username << endl;
            temp = temp->next;
        }
    }
};

#endif

