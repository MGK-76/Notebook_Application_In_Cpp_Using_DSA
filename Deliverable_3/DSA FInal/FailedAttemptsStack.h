#ifndef FAILEDATTEMPTSSTACK_H
#define FAILEDATTEMPTSSTACK_H

#include <string>
using namespace std;

// ====================== FAILED LOGIN ATTEMPTS STACK ===============
struct AttemptNode
{
    string username;
    AttemptNode *next;
};

class FailedAttemptsStack
{
private:
    AttemptNode *top;

public:
    FailedAttemptsStack() { top = nullptr; }

    void push(string uname)
    {
        AttemptNode *newNode = new AttemptNode{uname, top};
        top = newNode;
    }

    int countAttempts(string uname)
    {
        int count = 0;
        AttemptNode *temp = top;
        while (temp)
        {
            if (temp->username == uname)
                count++;
            temp = temp->next;
        }
        return count;
    }

    void clearAttempts(string uname)
    {
        AttemptNode *prev = nullptr;
        AttemptNode *current = top;
        while (current)
        {
            if (current->username == uname)
            {
                if (prev)
                    prev->next = current->next;
                else
                    top = current->next;
                AttemptNode *toDelete = current;
                current = current->next;
                delete toDelete;
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
    }

    ~FailedAttemptsStack()
    {
        while (top)
        {
            AttemptNode *temp = top;
            top = top->next;
            delete temp;
        }
    }
};

#endif

