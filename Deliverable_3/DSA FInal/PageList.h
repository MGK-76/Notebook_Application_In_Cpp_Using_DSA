#ifndef PAGELIST_H
#define PAGELIST_H

#include <iostream>
#include <string>
#include "NotificationQueue.h"
using namespace std;

// ====================== PAGE MANAGEMENT ========================
class PageNode
{
public:
    string content;
    PageNode *next;
    PageNode *prev;
    PageNode(string c) { content = c; next = prev = nullptr; }
};

class PageList
{
public:
    PageNode *head;
    PageNode *tail;
    PageList() { head = tail = nullptr; }

    void addBeginning(string val, NotificationQueue &notif)
    {
        PageNode *newNode = new PageNode(val);
        if (!head)
            head = tail = newNode;
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        notif.push("Page added at beginning: " + val);
    }

    void addEnd(string val, NotificationQueue &notif)
    {
        PageNode *newNode = new PageNode(val);
        if (!head)
        {
            head = tail = newNode;
            notif.push("Page added at end: " + val);
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        notif.push("Page added at end: " + val);
    }

    void addAfter(string location, string val, NotificationQueue &notif)
    {
        PageNode *temp = head;
        while (temp)
        {
            if (temp->content == location)
            {
                PageNode *newNode = new PageNode(val);
                newNode->next = temp->next;
                newNode->prev = temp;
                if (temp->next)
                    temp->next->prev = newNode;
                else
                    tail = newNode;
                temp->next = newNode;
                notif.push("Page added after \"" + location + "\": " + val);
                return;
            }
            temp = temp->next;
        }
        cout << "Location not found.\n";
    }

    void removePage(string val, NotificationQueue &notif)
    {
        if (!head)
        {
            cout << "No pages to delete.\n";
            return;
        }
        PageNode *temp = head;
        while (temp)
        {
            if (temp->content == val)
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
                notif.push("Page deleted: " + val);
                return;
            }
            temp = temp->next;
        }
        cout << "Page not found.\n";
    }

    void displayPages()
    {
        if (!head)
        {
            cout << "Notebook is empty.\n";
            return;
        }
        PageNode *temp = head;
        cout << "\n--- Notebook Pages ---\n";
        while (temp)
        {
            cout << "- " << temp->content << endl;
            temp = temp->next;
        }
    }
};

#endif

