#ifndef SEARCH_ENGINE_AVLTREE_H
#define SEARCH_ENGINE_AVLTREE_H
using namespace std;
#include <iostream>
template<typename T>
class AVLTree {
public:
    class Node{
    public:
        T key;
        int height;
        Node* left;
        Node* right;
        Node(T k){
            height = 1;
            key = k;
            left=nullptr;
            right=nullptr;
        }
    };
    Node* root = nullptr;
    int n;
    void insert(T data){
        root = insertFunc(root, data);
    }
    void remove(T data){
        root = removeFunc(root, data);
    }
    Node* find(T data){
        return search(root, data);
    }
    void inOrder(){
        inOrderFunc(root);
        cout<<endl;
    }
private:
    int getHeight(Node* head){
        if(head == nullptr)
            return 0;
        return head->height;
    }
    Node* rightRotate(Node* head){
        Node* newHead = head->left;
        head->left=newHead->right;
        newHead->right=head;
        head->height=1+max(getHeight(head->left),getHeight(head->right));
        newHead->height=1+max(getHeight(newHead->left),getHeight(newHead->right));
        return newHead;
    }
    Node* leftRotate(Node* head){
        Node* newHead = head->right;
        head->right=newHead->left;
        newHead->left=head;
        head->height=1+max(getHeight(head->left),getHeight(head->right));
        newHead->height=1+max(getHeight(newHead->left),getHeight(newHead->right));
        return newHead;
    }
    void inOrderFunc(Node* head){
        if(head== nullptr)
            return;
        inOrderFunc(head->left);
        cout<<head->key<<" ";
        inOrderFunc(head->right);
    }
    Node* insertFunc(Node* head, T data){
        if(head==nullptr){
            n+=1;
            Node* temporary = new Node(data);
            return temporary;
        }
        if(data < head->key)
            head->left = insertFunc(head->left, data);
        else if(data > head->key)
            head->right = insertFunc(head->right, data);

        head->height = 1 + max(getHeight(head->left),getHeight(head->right));
        int balanceFactor = getHeight(head->left)-getHeight(head->right);
        if(balanceFactor > 1){
            if(data < head->left->key){
                return rightRotate(head);
            }
            else{
                head->left = leftRotate(head->left);
                return rightRotate(head);
            }
        }
        else if(balanceFactor < -1){
            if(data > head->right->key){
                return leftRotate(head);
            }
            else{
                head->right = rightRotate(head->right);
                return leftRotate(head);
            }
        }
        return head;
    }
    Node* removeFunc(Node* head, T x){
        if(head==nullptr) return nullptr;
        if(x < head->key){
            head->left = removeFunc(head->left, x);
        }else if(x > head->key){
            head->right = removeFunc(head->right, x);
        }else{
            Node * tempR = head->right;
            if(head->right==nullptr){
                Node* tempL = head->left;
                delete(head);
                head = tempL;
            }else if(head->left==nullptr){
                delete(head);
                head = tempR;
            }else{
                while(tempR->left!=nullptr) tempR = tempR->left;
                head->key = tempR->key;
                head->right = removeFunc(head->right, tempR->key);
            }
        }
        if(head==nullptr) return head;
        head->height = 1 + max(getHeight(head->left), getHeight(head->right));
        int bal = getHeight(head->left) - getHeight(head->right);
        if(bal>1){
            if(x > head->left->key){
                return rightRotate(head);
            }else{
                head->left = leftRotate(head->left);
                return rightRotate(head);
            }
        }else if(bal < -1){
            if(x < head->right->key){
                return leftRotate(head);
            }else{
                head->right = rightRotate(head->right);
                return leftRotate(head);
            }
        }
        return head;
    }
    Node * search(Node * head, T data){
        if(head == nullptr) return nullptr;
        T k = head->key;
        if(k == data) return head;
        if(k > data) return search(head->left, data);
        if(k < data) return search(head->right, data);
    }
};


#endif //SEARCH_ENGINE_AVLTREE_H