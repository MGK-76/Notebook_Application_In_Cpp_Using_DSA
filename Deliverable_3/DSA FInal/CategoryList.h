#ifndef CATEGORYLIST_H
#define CATEGORYLIST_H

#include <iostream>
#include <string>
#include "NotificationQueue.h"
#include "BST.h"
using namespace std;

// ====================== CATEGORY MANAGEMENT ===================
struct NoteNode
{
    string note;
    int amount;
    NoteNode *next;
    NoteNode(string n, int a) { note = n; amount = a; next = nullptr; }
};

class CategoryList
{
public:
    NoteNode *head;
    bst amountsTree;
    CategoryList() { head = nullptr; }

    void addNote(string note, int amount, NotificationQueue &notif)
    {
        NoteNode *newNode = new NoteNode(note, amount);
        if (!head)
            head = newNode;
        else
        {
            NoteNode *temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
        }
        notif.push("Note added: " + note + ", Rs " + to_string(amount));
    }

    void displayNotes()
    {
        if (!head)
        {
            cout << "No notes in this category.\n";
            return;
        }
        NoteNode *temp = head;
        while (temp)
        {
            cout << "Note: " << temp->note << ", Amount: Rs " << temp->amount << endl;
            temp = temp->next;
        }
    }

    void deleteLastNote(NotificationQueue &notif)
    {
        if (!head)
        {
            cout << "No notes to delete.\n";
            return;
        }
        if (!head->next)
        {
            notif.push("Last note deleted: " + head->note + ", Rs " + to_string(head->amount));
            delete head;
            head = nullptr;
            return;
        }
        NoteNode *temp = head;
        while (temp->next->next)
            temp = temp->next;
        notif.push("Last note deleted: " + temp->next->note + ", Rs " + to_string(temp->next->amount));
        delete temp->next;
        temp->next = nullptr;
    }

    int total()
    {
        int sum = 0;
        NoteNode *temp = head;
        while (temp)
        {
            sum += temp->amount;
            temp = temp->next;
        }
        return sum;
    }
};

class NotebookCategories
{
public:
    CategoryList family, medical, leisure, work, salary;

    void showAll() { 
        cout << "\n--- Family ---\n"; family.displayNotes();
        cout << "\n--- Medical ---\n"; medical.displayNotes();
        cout << "\n--- Leisure ---\n"; leisure.displayNotes();
        cout << "\n--- Work ---\n"; work.displayNotes();
        cout << "\n--- Salary ---\n"; salary.displayNotes();
    }

    void displaySavings()
    {
        int expenses = family.total() + medical.total() + leisure.total() + work.total();
        int income = salary.total();
        cout << "\nTotal Income: Rs " << income <<std::endl;
        cout<<"Total expenses"<<expenses<<std::endl;
    }

    void removeLastExpense(int category, NotificationQueue &notif)
    {
        switch (category)
        {
        case 1: family.deleteLastNote(notif); break;
        case 2: medical.deleteLastNote(notif); break;
        case 3: work.deleteLastNote(notif); break;
        case 4: leisure.deleteLastNote(notif); break;
        case 5: salary.deleteLastNote(notif); break;
        default: cout << "Invalid category!\n";
        }
    }
};

#endif

