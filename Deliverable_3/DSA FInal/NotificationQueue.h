#ifndef NOTIFICATIONQUEUE_H
#define NOTIFICATIONQUEUE_H

#include <iostream>
#include <string>
using namespace std;

// ====================== NOTIFICATIONS QUEUE ========================
struct Notification {
    string message;
    Notification* next;
};

class NotificationQueue {
private:
    Notification* front;
    Notification* rear;
public:
    NotificationQueue() : front(nullptr), rear(nullptr) {}

    void push(string msg) {
        Notification* newNode = new Notification{msg, nullptr};
        if (!rear) front = rear = newNode;
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void view() {
        if (!front) {
            cout << "No new notifications.\n";
            return;
        }
        cout << "\n--- Notifications ---\n";
        Notification* temp = front;
        while (temp) {
            cout << "- " << temp->message << endl;
            temp = temp->next;
        }
        clear();
    }

    void clear() {
        while (front) {
            Notification* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }
};

#endif

