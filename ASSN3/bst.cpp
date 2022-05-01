#include "tree.h"
#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

int BinarySearchTree::insert(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    string check = preOrder();
    _root = insertion(_root, key);
    string later = preOrder();
    if (check == later)
    {
        return 1;
    }
    return 0;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int BinarySearchTree::erase(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    string check = preOrder();
    _root = deletion(_root, key);
    string later = preOrder();
    if (check == later)
    {
        return 1;
    }
    return 0;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
Node* BinarySearchTree::insertion(Node* node, int key)
{
    if (node == NULL)
    {
        node = new Node(key);
    }
    else
    {
        if (node->key > key)
        {
            node->left = insertion(node->left, key);
        }
        else if(node->key < key)
        {
            node->right = insertion(node->right, key);
        }
        else
        {
            return node;
        }
    }
    return node;
}
/*  Write your codes if you have additional functions  */

Node* find_minimum_node(Node* node)
{
    while (node && node->left)
    {
        node = node->left;
    }
    return node;
}

Node* BinarySearchTree::deletion(Node* node, int key)
{
    if (_root == NULL)
    {
        return node;
    }
    if (node == NULL)
    {
        return node;
    }
    if (key > node->key)
    {
        node->right = deletion(node->right, key);
    }
    else if (key < node->key)
    {
        node->left = deletion(node->left, key);
    }
    else
    {
        if (node->right == NULL)
        {
            Node* node_new = node->left;
            delete node;
            return node_new;
        }
        else if (node->left == NULL)
        {
            Node* node_new = node->right;
            delete node;
            return node_new;
        }
        else
        {
            Node* node_tempt = node;
            while (node_tempt && node_tempt->left)
            {
                node_tempt = node_tempt->left;
            }
            node->key = node_tempt->key;
            node->right = deletion(node->right, node_tempt->key);
        }
    }
    return node;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
