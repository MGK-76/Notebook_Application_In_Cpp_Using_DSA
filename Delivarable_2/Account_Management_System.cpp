#include <iostream>
#include <string>
using namespace std;

struct User {
    string username;
    string password;
    User* next;
};

class UserList {
private:
    User* head;

public:
    UserList() {
        head = nullptr;
    }

    void signUp(string uname, string pass) {
        User* temp = head;
        while (temp != nullptr) {
            if (temp->username == uname) {
                cout << "\n Username already exists! Try another.\n";
                return;
            }
            temp = temp->next;
        }

        User* newUser = new User;
        newUser->username = uname;
        newUser->password = pass;
        newUser->next = nullptr;

        if (head == nullptr)
            head = newUser;
        else {
            User* ptr = head;
            while (ptr->next != nullptr)
                ptr = ptr->next;
            ptr->next = newUser;
        }
        cout << "\n Account created successfully!\n";
    }

    bool login(string uname, string pass) {
        User* temp = head;
        while (temp != nullptr) {
            if (temp->username == uname && temp->password == pass) {
                cout << "\n Login successful! Welcome, " << uname << "!\n";
                return true;
            }
            temp = temp->next;
        }
        cout << "\n Invalid username or password.\n";
        return false;
    }

    void displayUsers() {
        if (head == nullptr) {
            cout << "\nNo users registered yet.\n";
            return;
        }
        cout << "\nRegistered Users:\n";
        User* temp = head;
        while (temp != nullptr) {
            cout << " - " << temp->username << endl;
            temp = temp->next;
        }
    }
};

struct Profile {
    string fieldName;
    string value;
    Profile* next;
    Profile* prev;
};

class ProfileList {
private:
    Profile* head;
    Profile* tail;

public:
    ProfileList() {
        head = tail = nullptr;
    }

    void createDefaultProfile() {
        addField("Full Name", "Not Set");
        addField("Email", "Not Set");
        addField("Bio", "Not Set");
    }

    void addField(string field, string val) {
        Profile* newField = new Profile;
        newField->fieldName = field;
        newField->value = val;
        newField->next = nullptr;
        newField->prev = nullptr;

        if (head == nullptr)
            head = tail = newField;
        else {
            tail->next = newField;
            newField->prev = tail;
            tail = newField;
        }
    }

    void viewProfile() {
        if (head == nullptr) {
            cout << "\n  Profile empty.\n";
            return;
        }
        cout << "\n----- Profile Details -----\n";
        Profile* temp = head;
        while (temp != nullptr) {
            cout << temp->fieldName << ": " << temp->value << endl;
            temp = temp->next;
        }
    }

    void deleteProfile() {
        Profile* temp = head;
        while (temp != nullptr) {
            Profile* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = tail = nullptr;
        cout << "\n  Profile deleted successfully!\n";
    }
};

struct LoginNode {
    string username;
    LoginNode* next;
};

class LoginHistory {
private:
    LoginNode* top;
public:
    LoginHistory()
    { 
        top = nullptr;
    }
    void push(string uname) {
        LoginNode* node = new LoginNode{uname, top};
        top = node;
    }

    void viewHistory() {
        if (!top) {
            cout << "No login history.\n";
            return;
        }
        cout << "\n--- Login History ---\n";
        LoginNode* temp = top;
        int count = 1;
        while (temp) {
            cout << count++ << ". " << temp->username << endl;
            temp = temp->next;
        }
    }

    void clearHistory() {
        while (top) {
            LoginNode* nextNode = top->next;
            delete top;
            top = nextNode;
        }
        cout << "Login history cleared.\n";
    }

    ~LoginHistory() {
        clearHistory();
    }
};

int main() {
    UserList users;
    LoginHistory history;
    ProfileList profile;
    int choice;
    string uname, pass;

    cout << "============================\n";
    cout << "  ACCOUNT MANAGEMENT SYSTEM \n";
    cout << "============================\n";

    do {
        cout << "\n=== User Management System ===\n";
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Display All Users\n";       
        cout << "4. Display Login History\n";   
        cout << "5. Clear Login History\n";     
        cout << "6. Exit\n";                    
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nEnter Username: ";
            cin >> uname;
            cout << "Enter Password: ";
            cin >> pass;
            users.signUp(uname, pass);
            break;

        case 2:
            cout << "\nEnter Username: ";
            cin >> uname;
            cout << "Enter Password: ";
            cin >> pass;

            if (users.login(uname, pass)) {
                history.push(uname);
                profile.createDefaultProfile();
                int opt;

                do {
                    cout << "\n----- PROFILE MENU -----\n";
                    cout << "1. View Profile\n2. Delete Profile\n3. Logout\n";
                    cout << "Enter option: ";
                    cin >> opt;

                    switch (opt) {
                    case 1:
                        profile.viewProfile();
                        break;
                    case 2:
                        profile.deleteProfile();
                        break;
                    case 3:
                        cout << "\n Logged out successfully!\n";
                        break;
                    default:
                        cout << "\nInvalid option.\n";
                    }
                } while (opt != 3);
            }
            break;

        case 3:
            users.displayUsers();     
            break;
        case 4:
            history.viewHistory();    
            break;
        case 5:
            history.clearHistory();   
            break;
        case 6:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
