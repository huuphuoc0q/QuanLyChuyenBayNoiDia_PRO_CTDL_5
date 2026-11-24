#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <vector>

#include "Ve.h"

template<typename TypeData>
struct listNode {
    TypeData data; 
    listNode* next; 
    listNode(const TypeData& value_) {
        data = value_; 
        next = nullptr; 
    }
};

template<typename TypeData>
class LinkedList {
    private: 
        listNode<TypeData>* pHead; 
        listNode<TypeData>* pTail; 
        int sizeLinkedList; 
    public: 
        LinkedList() {
            pHead = nullptr; 
            pTail = nullptr; 
            sizeLinkedList = 0; 
        }; 
        ~LinkedList() {
            while(pHead!=nullptr){
                listNode<TypeData>* tmp = pHead; 
                pHead = pHead->next; 
                delete tmp; 
            }
            pTail = nullptr;
            sizeLinkedList = 0; 
        }; 

        //Thao tac xu ly linked list; 
        bool push_back(const TypeData& value_) {
            listNode<TypeData>* pNew = new listNode<TypeData>(value_);
            if(pNew == nullptr) return false; 
            if(sizeLinkedList == 0) {
                pHead = pNew; 
                pTail = pNew; 
                sizeLinkedList++; 
                return true;
            } 
            pTail->next = pNew; 
            pTail = pNew; 
            sizeLinkedList++; 
            return true; 
        } 
        listNode<TypeData>* popFront(){
            if(sizeLinkedList==0) {
                return nullptr; 
            }

            listNode<TypeData>* tmp = pHead; 
            pHead = pHead->next; 
            if(pHead == nullptr) pTail = nullptr; 
            sizeLinkedList--; 
            return tmp; 
        }   

        bool empty() const {
            return sizeLinkedList == 0; 
        }
        int getSize() const {
            return sizeLinkedList; 
        }
        void getList(std::vector<TypeData>& res) const {
            res.clear();
            const listNode<TypeData>* current = pHead;
            while (current != nullptr) {
                res.push_back(current->data);
                current = current->next;
            }
        }
        bool removeVe(const TypeData& value_) {
            if(sizeLinkedList == 0) return false;

            listNode<TypeData>* listNodeCurr = pHead;
            listNode<TypeData>* listNodePre = pHead; 
            while(listNodeCurr!=nullptr && listNodeCurr->data!=value_) {
                listNodePre = listNodeCurr; 
                listNodeCurr = listNodeCurr->next;
            }

            if(listNodeCurr==nullptr) return false;
            
            if (listNodeCurr == pHead) {
                pHead = pHead->next; 
                if(sizeLinkedList==1) {
                    pTail = nullptr;
                }
            }
            else {
                listNodePre->next = listNodeCurr->next;
                if(listNodeCurr == pTail) {
                    pTail = listNodePre; 
                }
            }

            delete listNodeCurr; 
            sizeLinkedList--; 
            return true; 
        } 

        void display() const {
            if(sizeLinkedList==0) {
                return; 
            }

            listNode<TypeData>* tmp = pHead;
            while(tmp!=nullptr){
                std::cout<<tmp->data; 
                tmp = tmp->next; 
            }
        }
};

#endif