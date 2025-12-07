#ifndef LOGINHISTORY_H
#define LOGINHISTORY_H

#include <iostream>
#include <string>
using namespace std;

// ------------------- LOGIN HISTORY -------------------------
// This remains global/system-wide
struct LoginNode
{
    string username;
    LoginNode *next;
};

class LoginHistory
{
private:
    LoginNode *top;

public:
    LoginHistory() { top = nullptr; }
    void push(string uname) { top = new LoginNode{uname, top}; }
    void viewHistory()
    {
        if (!top)
        {
            cout << "No login history.\n";
            return;
        }
        cout << "\n--- Login History ---\n";
        LoginNode *temp = top;
        int count = 1;
        while (temp)
        {
            cout << count++ << ". " << temp->username << endl;
            temp = temp->next;
        }
    }
    void clearHistory()
    {
        while (top)
        {
            LoginNode *nextNode = top->next;
            delete top;
            top = nextNode;
        }
        cout << "Login history cleared.\n";
    }
    ~LoginHistory() { clearHistory(); }
};

#endif

