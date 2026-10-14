#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Ve.h"

template<typename TypeData>
struct Node {
    TypeData data; 
    Node* pNext; 
    Node(const TypeData& value_) {
        data = value_; 
        pNext = nullptr; 
    }
};

template<typename TypeData>
class LinkedList {
    private: 
        Node<TypeData>* pHead; 
        Node<TypeData>* pTail; 
        int sizeLinkedList; 
    public: 
        LinkedList() {
            pHead = nullptr; 
            pTail = nullptr; 
            sizeLinkedList = 0; 
        }; 
        ~LinkedList() {
            while(pHead!=nullptr){
                Node<TypeData>* tmp = pHead; 
                pHead = pHead->next; 
                delete tmp; 
            }
            pTail = nullptr;
            sizeLinkedList = nullptr; 
        }; 

        //Thao tac xu ly linked list; 
        void push_back(const TypeData& value_) {
            Node<TypeData>* pNew = new Node<TypeData>(value_);
            if(sizeLinkedList == 0) {
                pHead = pNew; 
                pTail = pNew; 
                return; 
            } 
            pTail->next = pNew; 
            pTail = pNew; 
            sizeLinkedList++; 
        } 
        Node<TypeData>* popFront(){
            if(sizeLinkedList==0) {
                return nullptr; 
            }

            Node<TypeData>* tmp = pHead; 
            pHead = pHead->next; 
            if(pHead == nullptr) pTail = nullptr; 
            sizeLinkedList--; 
            return tmp; 
        }   

        bool removeVe(const TypeData& value_) {
            if(sizeLinkedList == 0) return false;

            Node<TypeData>* nodeCurr = pHead;
            Node<TypeData>* nodePre = pHead; 
            while(nodeCurr!=nullptr && nodeCurr->data!=value_) {
                nodePre = nodeCurr; 
                nodeCurr = nodeCurr->next;
            }

            if(nodeCurr==nullptr) return false;
            
            if (nodeCurr == pHead) {
                pHead = pHead->next; 
                if(sizeLinkedList==1) {
                    pTail = nullptr;
                }
            }
            else {
                nodePre->next = nodeCurr->next;
                if(nodeCurr == pTail) {
                    pTail = nodePre; 
                }
            }

            delete nodeCurr; 
            sizeLinkedList--; 
            return true; 
        } 

        void display() const {
            if(sizeLinkedList==0) {
                return; 
            }

            Node<TypeData>* tmp = pHead;
            while(tmp!=nullptr){
                std::cout<<tmp->data<<" "; 
                tmp = tmp->next; 
            }
        }
};

#endif