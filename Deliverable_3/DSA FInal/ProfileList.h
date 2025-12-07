#ifndef PROFILELIST_H
#define PROFILELIST_H

#include <iostream>
#include <string>
using namespace std;

// ------------------- Profile Management --------------------
struct Profile
{
    string fieldName;
    string value;
    Profile *next;
    Profile *prev;
};

class ProfileList
{
private:
    Profile *head;
    Profile *tail;

public:
    ProfileList() { head = tail = nullptr; }

    void createDefaultProfile()
    {
        // Only add defaults if empty to avoid duplicates on multiple logins
        if (head) return; 
        addField("Full Name", "Not Set");
        addField("Email", "Not Set");
        addField("Bio", "Not Set");
    }

    void addField(string field, string val)
    {
        Profile *newField = new Profile{field, val, nullptr, tail};
        if (!head)
            head = tail = newField;
        else
        {
            tail->next = newField;
            tail = newField;
        }
    }

    void viewProfile()
    {
        if (!head)
        {
            cout << "\nProfile empty.\n";
            return;
        }
        cout << "\n----- Profile Details -----\n";
        Profile *temp = head;
        while (temp)
        {
            cout << temp->fieldName << ": " << temp->value << endl;
            temp = temp->next;
        }
    }

    void deleteProfile()
    {
        Profile *temp = head;
        while (temp)
        {
            Profile *nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = tail = nullptr;
        cout << "\nProfile deleted successfully!\n";
    }

    void updateField(string field, string val)
    {
        Profile *temp = head;
        while (temp)
        {
            if (temp->fieldName == field)
            {
                temp->value = val;
                cout << "\n" << field << " updated successfully!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "\nField not found. Adding new field.\n";
        addField(field, val);
    }
};

#endif

