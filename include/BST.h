
#ifndef BST_H
#define BST_H

#include <iostream> 
#include <vector> 
#include <algorithm> 

template<typename DataType>
struct Node {
    Node* pLeft; 
    Node* pRight; 
    DataType data_; 
    int height; 
    Node(const DataType& value_) {
        data_ = value_; 
        pLeft = nullptr;  
        pRight = nullptr; 
        height = 1; 
    }
};

template<typename DataType>
class Tree {
    private: 
        Node<DataType>* root_;                                            
        int sizeBST_;  

        int getHeight(Node<DataType>* node_) const {
            return (node_ == nullptr) ? 0 : node_->height;
        }

        void updateHeight(Node<DataType>* node_) {
            if (node_ != nullptr) {
                node_->height = 1 + std::max(getHeight(node_->pLeft), getHeight(node_->pRight));
            }
        }

        int getBalanceFactor(Node<DataType>* node_) const {
            return (node_ == nullptr) ? 0 : getHeight(node_->pLeft) - getHeight(node_->pRight);
        }

        void rotateRight(Node<DataType>* &node_) {
            Node<DataType>* pLeftChild = node_->pLeft;
            Node<DataType>* pSubRight = pLeftChild->pRight;

            pLeftChild->pRight = node_;
            node_->pLeft = pSubRight;

            updateHeight(node_);
            updateHeight(pLeftChild);

            node_ = pLeftChild; 
        }

        void rotateLeft(Node<DataType>* &node_) {
            Node<DataType>* pRightChild = node_->pRight;
            Node<DataType>* pSubLeft = pRightChild->pLeft;

            pRightChild->pLeft = node_;
            node_->pRight = pSubLeft;

            updateHeight(node_);
            updateHeight(pRightChild);

            node_ = pRightChild; 
        }

        void insert_(Node<DataType>* &node_, const DataType& value_) {
            if (node_ == nullptr) {
                node_ = new Node<DataType>(value_);
                sizeBST_++; 
                return;
            }

            if (value_ < node_->data_) {
                insert_(node_->pLeft, value_); 
            } else if (value_ > node_->data_) {
                insert_(node_->pRight, value_); 
            } else {
                return;
            }

            updateHeight(node_);

            int balance = getBalanceFactor(node_);

            if (balance > 1 && value_ < node_->pLeft->data_) {
                rotateRight(node_);
                return;
            }

            if (balance < -1 && value_ > node_->pRight->data_) {
                rotateLeft(node_);
                return;
            }

            if (balance > 1 && value_ > node_->pLeft->data_) {
                rotateLeft(node_->pLeft);
                rotateRight(node_);
                return;
            }

            if (balance < -1 && value_ < node_->pRight->data_) {
                rotateRight(node_->pRight);
                rotateLeft(node_);
                return;
            }
        }

        void inorder_(Node<DataType>* node_) const {
            if (node_ == nullptr) return; 
            inorder_(node_->pLeft); 
            std::cout << node_->data_ << std::endl; 
            inorder_(node_->pRight); 
        }
        void getList_(std::vector<DataType*>& res, Node<DataType>* node_) {
            if (node_ == nullptr) return; 
            getList_(res, node_->pLeft);
            res.push_back(&(node_->data_));
            getList_(res, node_->pRight); 
        }

        Node<DataType>* search_(Node<DataType>* node_, const DataType& value_) const {
            if (node_ == nullptr || value_ == node_->data_) return node_; 
            if (value_ < node_->data_) 
                return search_(node_->pLeft, value_); 
            else
                return search_(node_->pRight, value_); 
        }

        void clear(Node<DataType>* &node_) {
            if (node_ == nullptr) return; 
            clear(node_->pLeft); 
            clear(node_->pRight); 
            delete node_; 
            node_ = nullptr; 
        }

    public: 
        Tree() {
            root_ = nullptr; 
            sizeBST_ = 0; 
        }

        ~Tree() {
            clear(root_); 
            root_ = nullptr; 
        }

        void insert(const DataType& value_) {
            insert_(root_, value_); 
        }

        void xuat() const {
            inorder_(root_); 
        }
        
        void getList(std::vector<DataType*>& res) {
            res.clear(); 
            getList_(res, root_); 
        }

        Node<DataType>* search(const DataType& value_) {
            return search_(root_, value_); 
        }
};

#endif