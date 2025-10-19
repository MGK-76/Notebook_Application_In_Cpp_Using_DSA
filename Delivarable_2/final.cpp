#include <iostream>
#include <string>
using namespace std;

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
    CategoryList()
    {
        head = nullptr;
    }
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

int main()
{
    NotebookCategories categories;
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

    return 0;
}