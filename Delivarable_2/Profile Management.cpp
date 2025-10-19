#include <iostream>
#include <string>
using namespace std;

class PageNode
{
public:
    string content;
    PageNode *next;
    PageNode *prev;
    PageNode(string c)
    {
        content = c;
        next = prev = nullptr;
    }
};

class PageList
{
public:
    PageNode *head;
    PageNode *tail;
    PageList()
    {
        head = tail = nullptr;
    }

    void addBeginning(string val)
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
    }

    void addEnd(string val)
    {
        PageNode *newNode = new PageNode(val);
        if (tail)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void addAfter(string location, string val)
    {
        PageNode *temp = head;
        while (temp != nullptr)
        {
            if (temp->content == location)
            {
                PageNode *newNode = new PageNode(val);
                newNode->next = temp->next;
                newNode->prev = temp;
                if (temp->next != nullptr)
                {
                    temp->next->prev = newNode;
                }
                else
                {
                    tail = newNode;
                }
                temp->next = newNode;
                return;
            }
            temp = temp->next;
        }
        cout << "Location not found.\n";
    }

    void removePage(string val)
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
                {
                    temp->prev->next = temp->next;
                }
                else
                {
                    head = temp->next;
                }
                if (temp->next)
                {
                    temp->next->prev = temp->prev;
                }
                else
                {
                    tail = temp->prev;
                }
                delete temp;
                cout << val << " deleted successfully.\n";
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
        while (temp != nullptr)
        {
            cout << "- " << temp->content << endl;
            temp = temp->next;
        }
    }
};
