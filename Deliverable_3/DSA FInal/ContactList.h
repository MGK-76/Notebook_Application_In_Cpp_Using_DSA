#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <iostream>
#include <string>
using namespace std;

// ------------------- Contact Management --------------------
struct Contact
{
    string name;
    string phone;
    string email;
    Contact *next;
    Contact *prev;
};

class ContactList
{
private:
    Contact *head;
    Contact *tail;

public:
    ContactList() { head = tail = nullptr; }

    void addContact(string name, string phone, string email)
    {
        Contact *newContact = new Contact{name, phone, email, nullptr, tail};
        if (!head)
            head = tail = newContact;
        else
        {
            tail->next = newContact;
            tail = newContact;
        }
        cout << "\nContact added successfully!\n";
    }

    void displayContacts()
    {
        if (!head)
        {
            cout << "\nNo contacts found.\n";
            return;
        }
        cout << "\n----- Contact List -----\n";
        Contact *temp = head;
        int count = 1;
        while (temp)
        {
            cout << count++ << ". Name: " << temp->name << ", Phone: " << temp->phone << ", Email: " << temp->email << endl;
            temp = temp->next;
        }
    }

    void deleteContact(string name)
    {
        if (!head)
        {
            cout << "\nNo contacts to delete.\n";
            return;
        }
        Contact *temp = head;
        while (temp)
        {
            if (temp->name == name)
            {
                if (temp->prev)
                    temp->prev->next = temp->next;
                else
                    head = temp->next;
                if (temp->next)
                    temp->next->prev = temp->prev;
                else
                    tail = temp->prev;
                delete temp;
                cout << "\nContact deleted successfully!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "\nContact not found.\n";
    }
};

#endif

