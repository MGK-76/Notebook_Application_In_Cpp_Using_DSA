#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;

class Node{
    public:
        int value;
        Node* left;
        Node* right;
        Node(int input){
            value = input;
            left = nullptr;
            right = nullptr;
        }
};

class bst{
    public:
        Node* root;

        bst(){
            root = nullptr;
        }
        int sumfinder(Node* currentRoot,int &sum){
			if(currentRoot != nullptr){
				sumfinder(currentRoot->left,sum);
				sum=sum+currentRoot->value;
				sumfinder(currentRoot->right,sum);
			}
            return sum;
        }
        Node* findmin(Node* currentRoot){
            if(currentRoot == nullptr){
                return nullptr;
            }
            while(currentRoot->left != nullptr){
                currentRoot = currentRoot->left;
            }
            return currentRoot;
        }

        Node* deletionhelper(Node* currentRoot, int key,bool &check){
            if(currentRoot == nullptr){
                return nullptr;
            }
            else if(key > currentRoot->value){
                currentRoot->right = deletionhelper(currentRoot->right, key,check);
            }
            else if(key < currentRoot->value){
                currentRoot->left = deletionhelper(currentRoot->left, key,check);
            }
            else{
                check=true;
                if(currentRoot->left == nullptr){
                    Node* temp = currentRoot->right;
                    delete currentRoot;
                    return temp;
                }
                else if(currentRoot->right == nullptr){
                    Node* temp = currentRoot->left;
                    delete currentRoot;
                    return temp;
                }
                else{
                    Node* temp = findmin(currentRoot->right);
                    currentRoot->value = temp->value;
                    currentRoot->right = deletionhelper(currentRoot->right, temp->value,check);
                }
            }
            return currentRoot;
        }

        Node* inserthelper(int key,Node* currentRoot){
            if(currentRoot == nullptr){
                Node* Newnode = new Node(key);
                std::cout << "Value " << key << " has been added.\n";
                return Newnode;
            }
            else{
                if(key > currentRoot->value){
                    currentRoot->right = inserthelper(key, currentRoot->right);
                } 
                else if(key < currentRoot->value){
                    currentRoot->left = inserthelper(key, currentRoot->left);
                }
                return currentRoot;
            }
        }

        void inordertransversal_helper(Node* currentRoot){
			if(currentRoot != nullptr){
				inordertransversal_helper(currentRoot->left);
				std::cout << currentRoot->value << " ";
				inordertransversal_helper(currentRoot->right);
			}
        }
        void deletion(int key){
            bool check = false;
            root = deletionhelper(root, key,check);
            if(check)
                std::cout << "Value " << key << " successfully deleted.\n";
            else
                std::cout << "Value " << key << " not found in the tree.\n";
            }

        void insert(int key){
            root = inserthelper(key, root);
        }

        void inordertransversal(){
            inordertransversal_helper(root);
            std::cout << "\n";
        }
        void sum(){
            int sum=0;
            int val=sumfinder(root,sum);
            std::cout<<"Total debt is"<<sum<<std::endl;
        }
        ~bst() {
            clearTree(root);
            root = nullptr;
        }
        void clearTree(Node* currentRoot) {
            if (currentRoot == nullptr)
            return;
            clearTree(currentRoot->left);
            clearTree(currentRoot->right);
            delete currentRoot;
        }


};

#endif

