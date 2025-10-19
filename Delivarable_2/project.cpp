#include <iostream>
#include <string>
using namespace std;

// ====================== ACCOUNT MANAGEMENT =========================
struct User
{
    string username;
    string password;
    User *next;
};

class UserList
{
private:
    User *head;

public:
    UserList()
    { 
        head = nullptr; 
    }

    void signUp(string uname, string pass)
    {
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
        User *newUser = new User{uname, pass, nullptr};
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

    bool login(string uname, string pass)
    {
        User *temp = head;
        while (temp)
        {
            if (temp->username == uname && temp->password == pass)
            {
                cout << "\nLogin successful! Welcome, " << uname << "!\n";
                return true;
            }
            temp = temp->next;
        }
        cout << "\nInvalid username or password.\n";
        return false;
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
    ProfileList() 
    {
        head = tail = nullptr; 
    }

    void createDefaultProfile()
    {
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
};

// ------------------- LOGIN HISTORY -------------------------
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
    LoginHistory()
    {
        top = nullptr;
    }

    void push(string uname) 
    {
        top = new LoginNode{uname, top};
    }

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

    ~LoginHistory()
    {
        clearHistory();
    }
};

// ====================== PAGE MANAGEMENT ========================
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

// ====================== CATEGORY MANAGEMENT ===================
struct NoteNode
{
    string note;
    int amount;
    NoteNode *next;
    NoteNode(string n, int a)
    {
        note = n;
        amount = a;
        next = nullptr;
    }
};

class CategoryList
{
public:
    NoteNode *head;
    CategoryList() { head = nullptr; }
    void addNote(string note, int amount)
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
    void deleteLastNote()
    {
        if (!head)
        {
            cout << "No notes to delete.\n";
            return;
        }
        if (!head->next)
        {
            delete head;
            head = nullptr;
            return;
        }
        NoteNode *temp = head;
        while (temp->next->next)
            temp = temp->next;
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
    void showAll()
    {
        cout << "\n--- Family ---\n";
        family.displayNotes();
        cout << "\n--- Medical ---\n";
        medical.displayNotes();
        cout << "\n--- Leisure ---\n";
        leisure.displayNotes();
        cout << "\n--- Work ---\n";
        work.displayNotes();
        cout << "\n--- Salary ---\n";
        salary.displayNotes();
    }
    void displaySavings()
    {
        int expenses = family.total() + medical.total() + leisure.total();
        int income = salary.total();
        int savings = income - expenses;
        cout << "\nTotal Income: Rs " << income << ", Total Expenses: Rs " << expenses << endl;
        if (savings < 0)
            cout << "You need a loan of Rs " << -savings << " to cover expenses.\n";
        else
            cout << "Net Savings: Rs " << savings << endl;
    }
    void removeLastExpense(int category)
    {
        switch (category)
        {
        case 1:
            family.deleteLastNote();
            break;
        case 2:
            medical.deleteLastNote();
            break;
        case 3:
            work.deleteLastNote();
            break;
        case 4:
            leisure.deleteLastNote();
            break;
        case 5:
            salary.deleteLastNote();
            break;
        default:
            cout << "Invalid category!\n";
        }
    }
};

// ====================== MAIN PROGRAM ==========================
int main()
{
    UserList users;
    LoginHistory history;
    ProfileList profile;
    PageList pages;
    NotebookCategories categories;

    int choice;
    string uname, pass;

    cout << "=== MULTI-USER NOTEBOOK PROGRAM ===\n";

    do
    {
        cout << "\n1. Sign Up\n2. Login\n3. Display Users\n4. Login History\n5. Clear Login History\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Username: ";
            cin >> uname;
            cout << "Password: ";
            cin >> pass;
            users.signUp(uname, pass);
            break;

        case 2:
            cout << "Username: ";
            cin >> uname;
            cout << "Password: ";
            cin >> pass;
            if (users.login(uname, pass))
            {
                history.push(uname);
                profile.createDefaultProfile();

                int subChoice;
                do
                {
                    cout << "\n--- NOTEBOOK MENU ---\n";
                    cout << "1. View Profile\n2. Delete Profile\n3. Manage Pages\n4. Manage Categories\n5. Logout\n";
                    cout << "Enter option: ";
                    cin >> subChoice;

                    switch (subChoice)
                    {
                    case 1:
                        profile.viewProfile();
                        break;
                    case 2:
                        profile.deleteProfile();
                        break;
                    case 3:
                    {
                        int pageChoice;
                        string content, location;
                        do
                        {
                            cout << "\nPage Menu:\n1. Add Beginning\n2. Add End\n3. Add After\n4. Delete Page\n5. Display Pages\n6. Back\n";
                            cout << "Choice: ";
                            cin >> pageChoice;
                            cin.ignore();
                            switch (pageChoice)
                            {
                            case 1:
                                cout << "Content: ";
                                getline(cin, content);
                                pages.addBeginning(content);
                                break;
                            case 2:
                                cout << "Content: ";
                                getline(cin, content);
                                pages.addEnd(content);
                                break;
                            case 3:
                                cout << "Add after page: ";
                                getline(cin, location);
                                cout << "New page content: ";
                                getline(cin, content);
                                pages.addAfter(location, content);
                                break;
                            case 4:
                                cout << "Page to delete: ";
                                getline(cin, content);
                                pages.removePage(content);
                                break;
                            case 5:
                                pages.displayPages();
                                break;
                            }
                        } while (pageChoice != 6);
                        break;
                    }
                    case 4:
                    {
                        int catChoice;
                        string noteContent;
                        int amount;
                        do
                        {
                            cout << "\nCategory Menu:\n1. Family\n2. Medical\n3. Work\n4. Leisure\n5. Salary\n6. Remove Last Note\n7. Show All Notes\n8. Show Net Savings\n9. Back\n";
                            cout << "Choice: ";
                            cin >> catChoice;
                            cin.ignore();
                            switch (catChoice)
                            {
                            case 1:
                                cout << "Note: ";
                                getline(cin, noteContent);
                                cout << "Amount: ";
                                cin >> amount;
                                cin.ignore();
                                categories.family.addNote(noteContent, amount);
                                break;
                            case 2:
                                cout << "Note: ";
                                getline(cin, noteContent);
                                cout << "Amount: ";
                                cin >> amount;
                                cin.ignore();
                                categories.medical.addNote(noteContent, amount);
                                break;
                            case 3:
                                cout << "Note: ";
                                getline(cin, noteContent);
                                cout << "Amount: ";
                                cin >> amount;
                                cin.ignore();
                                categories.work.addNote(noteContent, amount);
                                break;
                            case 4:
                                cout << "Note: ";
                                getline(cin, noteContent);
                                cout << "Amount: ";
                                cin >> amount;
                                cin.ignore();
                                categories.leisure.addNote(noteContent, amount);
                                break;
                            case 5:
                                cout << "Note: ";
                                getline(cin, noteContent);
                                cout << "Amount: ";
                                cin >> amount;
                                cin.ignore();
                                categories.salary.addNote(noteContent, amount);
                                break;
                            case 6:
                                int removeCat;
                                cout << "Category to remove last note (1-5): ";
                                cin >> removeCat;
                                cin.ignore();
                                categories.removeLastExpense(removeCat);
                                break;
                            case 7:
                                categories.showAll();
                                break;
                            case 8:
                                categories.displaySavings();
                                break;
                            }
                        } while (catChoice != 9);
                        break;
                    }
                    }
                } while (subChoice != 5);
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
        }
    } while (choice != 6);

    cout << "Exiting program...\n";
    return 0;
}
