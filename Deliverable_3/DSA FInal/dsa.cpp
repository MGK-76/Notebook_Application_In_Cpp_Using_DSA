#include <iostream>
#include <string>
#include "Errorhandling.h"
#include "NotificationQueue.h"
#include "ProfileList.h"
#include "ContactList.h"
#include "PageList.h"
#include "BST.h"
#include "CategoryList.h"
#include "PasswordStrength.h"
#include "PasswordMask.h"
#include "FailedAttemptsStack.h"
#include "UserList.h"
#include "LoginHistory.h"
using namespace std;

// ====================== MAIN PROGRAM ==========================
int main()
{
    UserList users;
    LoginHistory history;
    
    // Removed "global" instances of PageList, ProfileList, etc. from here.
    // They now live inside the User struct.

    int choice;
    string uname, pass;

    cout << "=== MULTI-USER NOTEBOOK PROGRAM ===\n";

    do
    {
        cout << "\n1. Sign Up\n2. Login\n3. Display Users\n4. Login History\n5. Clear Login History\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (cin.fail())
        {
            clearInputBuffer();
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            cout << "Username: ";
            cin >> uname;
            pass = getMaskedPassword();
            users.signUp(uname, pass);
            break;

        case 2:
        {
            cout << "Username: ";
            cin >> uname;
            pass = getMaskedPassword();
            
            User* currentUser = users.login(uname, pass);
            
            if (currentUser != nullptr)
            {
                history.push(uname);
                
                currentUser->profile.createDefaultProfile();
                
                currentUser->notifications.push("Welcome " + uname + "! You are logged in.");

                int subChoice;
                do
                {
                    cout << "\n--- NOTEBOOK MENU (" << currentUser->username << ") ---\n";
                    cout << "1. View Profile\n2. Update Profile\n3. Delete Profile\n4. Manage Contacts\n5. Manage Pages\n6. Manage Categories\n7. View Notifications\n8. Logout\n";
                    cout << "Enter option: ";
                    cin >> subChoice;
                    if (cin.fail())
                    {
                        clearInputBuffer();
                        cout << "Invalid input! Please enter a number.\n";
                        continue;
                    }

                    switch (subChoice)
                    {
                    case 1:
                        currentUser->profile.viewProfile();
                        break;
                    case 2:
                    {
                        string field, value;
                        cout << "\nEnter field name to update (e.g., Full Name, Email, Bio): ";
                        cin.ignore();
                        getline(cin, field);
                        cout << "Enter new value: ";
                        getline(cin, value);
                        currentUser->profile.updateField(field, value);
                        currentUser->notifications.push("Profile updated: " + field);
                        break;
                    }
                    case 3:
                        currentUser->profile.deleteProfile();
                        currentUser->notifications.push("Profile deleted.");
                        break;
                    case 4:
                    {
                        int contactChoice;
                        string name, phone, email;
                        do
                        {
                            cout << "\nContact Management:\n1. Add Contact\n2. Delete Contact\n3. View Contacts\n4. Back\n";
                            cout << "Choice: ";
                            cin >> contactChoice;
                            if (cin.fail())
                            {
                                clearInputBuffer();
                                cout << "Invalid input! Please enter a number.\n";
                                continue;
                            }
                            cin.ignore();
                            switch (contactChoice)
                            {
                            case 1:
                                cout << "Name: ";
                                getline(cin, name);
                                cout << "Phone: ";
                                getline(cin, phone);
                                cout << "Email: ";
                                getline(cin, email);
                                currentUser->contacts.addContact(name, phone, email);
                                currentUser->notifications.push("Contact added: " + name);
                                break;
                            case 2:
                                cout << "Enter contact name to delete: ";
                                getline(cin, name);
                                currentUser->contacts.deleteContact(name);
                                currentUser->notifications.push("Contact deleted: " + name);
                                break;
                            case 3:
                                currentUser->contacts.displayContacts();
                                break;
                            }
                        } while (contactChoice != 4);
                        break;
                    }
                    case 5:
                    {
                        int pageChoice;
                        string content, location;
                        do
                        {
                            cout << "\nPage Menu:\n1. Add Beginning\n2. Add End\n3. Add After\n4. Delete Page\n5. Display Pages\n6. Back\n";
                            cout << "Choice: ";
                            cin >> pageChoice;
                            if (cin.fail())
                            {
                                clearInputBuffer();
                                cout << "Invalid input! Please enter a number.\n";
                                continue;
                            }
                            cin.ignore();
                            switch (pageChoice)
                            {
                            case 1:
                                cout << "Content: ";
                                getline(cin, content);
                                currentUser->pages.addBeginning(content, currentUser->notifications);
                                break;
                            case 2:
                                cout << "Content: \n";
                                getline(cin, content);
                                currentUser->pages.addEnd(content, currentUser->notifications);
                                break;
                            case 3:
                                cout << "Add after page\n";
                                getline(cin, location);
                                cout << "New page content:\n";
                                getline(cin, content);
                                currentUser->pages.addAfter(location, content, currentUser->notifications);
                                break;
                            case 4:
                                cout << "Page to delete:\n";
                                getline(cin, content);
                                currentUser->pages.removePage(content, currentUser->notifications);
                                break;
                            case 5:
                                currentUser->pages.displayPages();
                                std::cout<<"Debt amounts in ascending order \n";
                                currentUser->categories.salary.amountsTree.inordertransversal();
                                break;
                            }
                        } while (pageChoice != 6);
                        break;
                    }
                    case 6:
                    {
                        int catChoice;
                        string noteContent;
                        int amount;
                        do
                        {
                            cout << "\nCategory Menu:\n1. Family\n2. Medical\n3. Work\n4. Leisure\n5. debt\n6. Remove Last Note or selected debt\n7. Show All Notes\n8. Show Net Savings\n9. Back\n";
                            cout << "Choice: ";
                            cin >> catChoice;
                            if (cin.fail())
                            {
                                clearInputBuffer();
                                cout << "Invalid input! Please enter a number.\n";
                                continue;
                            }
                            cin.ignore();
                            switch (catChoice)
                            {
                            case 1:
                                cout << "Note: "; getline(cin, noteContent);
                                cout << "Amount: "; cin >> amount;
                                if (cin.fail())
                                {
                                    clearInputBuffer();
                                    cout << "Invalid input! Please enter a number.\n";
                                    continue;
                                }
                                cin.ignore();
                                currentUser->categories.family.addNote(noteContent, amount, currentUser->notifications);
                                break;
                            case 2:
                                cout << "Note: "; getline(cin, noteContent);
                                cout << "Amount: "; cin >> amount;
                                if (cin.fail())
                                {
                                    clearInputBuffer();
                                    cout << "Invalid input! Please enter a number.\n";
                                    continue;
                                }
                                cin.ignore();
                                currentUser->categories.medical.addNote(noteContent, amount, currentUser->notifications);
                                break;
                            case 3:
                                cout << "Note: "; getline(cin, noteContent);
                                cout << "Amount: "; cin >> amount;
                                if (cin.fail())
                                {
                                    clearInputBuffer();
                                    cout << "Invalid input! Please enter a number.\n";
                                    continue;
                                }
                                cin.ignore();
                                currentUser->categories.work.addNote(noteContent, amount, currentUser->notifications);
                                break;
                            case 4:
                                cout << "Note: "; getline(cin, noteContent);
                                cout << "Amount: "; cin >> amount;
                                if (cin.fail())
                                {
                                    clearInputBuffer();
                                    cout << "Invalid input! Please enter a number.\n";
                                    continue;
                                }
                                cin.ignore();
                                currentUser->categories.leisure.addNote(noteContent, amount, currentUser->notifications);
                                break;
                            case 5:
                                std::cout<<"Input amount owed"<<std::endl;
                                std::cin>>amount;
                                if (cin.fail())
                                {
                                    clearInputBuffer();
                                    cout << "Invalid input! Please enter a number.\n";
                                    continue;
                                }
                                currentUser->categories.salary.amountsTree.insert(amount);
                                break;
                            case 6:
                            {
                                int removeCat;
                                std::cout << "Category to remove last note (1-4): ";
                                cin >> removeCat;
                                if (cin.fail())
                                {
                                    clearInputBuffer();
                                    cout << "Invalid input! Please enter a number.\n";
                                    continue;
                                }
                                cin.ignore();
                                if(removeCat==1||removeCat==2||removeCat==3||removeCat==4){
                                currentUser->categories.removeLastExpense(removeCat, currentUser->notifications);
                            }
                                else if(removeCat==5){
                                    int val1;
                                    std::cout<<"Enter value to delete";
                                    std::cin>>val1;
                                    if (cin.fail())
                                    {
                                        clearInputBuffer();
                                        cout << "Invalid input! Please enter a number.\n";
                                        continue;
                                    }
                                    currentUser->categories.salary.amountsTree.deletion(val1);
                                }
                                break;
                            }
                            case 7:
                                currentUser->categories.showAll();
                                cout << "Total debt "<<std::endl;
                                currentUser->categories.salary.amountsTree.sum();
                                break;
                            }
                        } while (catChoice != 9);
                        break;
                    }
                    case 7:
                        currentUser->notifications.view();
                        break;
                    }
                } while (subChoice != 8);
            }
            break;
        }
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
            cout << "     Goodbye!         \n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    cout << "Exiting program...\n";
    return 0;
}