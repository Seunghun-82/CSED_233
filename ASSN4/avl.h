#pragma once
#include "tree.h"

using namespace std;

class AVLTree: public BinaryTree {
public:
    AVLTree() { };
    ~AVLTree() { };

    int insert(int key);
    int erase(int key);
private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    Node* insertion(Node* node, int key);
    Node* deletion(Node* node, int key);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};