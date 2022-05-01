#include "tree.h"
#include "avl.h"
#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
int maximum(int left, int right)
{
    if (left > right)
    {
        return left;
    }
    else
    {
        return right;
    }
}

int get_height(Node* node)
{
    if (node == NULL)
    {
        return -1;
    }
    else
    {
        node->height = maximum(get_height(node->left), get_height(node->right)) + 1;
        return node->height;
    }
}

int get_factor(Node* node)
{
    if (node == NULL)
        return 0;
    else
    {
        return get_height(node->left) - get_height(node->right);
    }
}

Node* right_rotate(Node* node)
{
    Node* tree_1 = node->left;
    node->left = tree_1->right;
    tree_1->right = node;
    node->height = get_height(node);
    tree_1->height = get_height(tree_1);

    return tree_1;
}

Node* left_rotate(Node* node)
{
    Node* tree_1 = node->right;
    node->right = tree_1->left;
    tree_1->left = node;

    tree_1->height = get_height(tree_1);
    node->height = get_height(node);

    return tree_1;
}

Node* AVLTree::insertion(Node* node, int key)
{
    if (node == NULL)
    {
        Node* NODE = new Node(key);
        return NODE;
    }

    if (key < node->key)
    {
        node->left = insertion(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = insertion(node->right, key);
    }
    else
    {
        return node;
    }
    node->height = get_height(node);
    int factor = get_factor(node);

    if (factor > 1 && key < node->left->key)
    {
        return right_rotate(node);
    }
    else if (factor > 1 && key > node->left->key)
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    else if (factor < -1 && key > node->right->key)
    {
        return left_rotate(node);
    }
    else if (factor < -1 && key < node->right->key)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;

}

Node* AVLTree::deletion(Node* node, int key)
{
    if (node == NULL)
    {
        return node;
    }

    if (key < node->key)
    {
        node->left = deletion(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = deletion(node->right, key);
    }
    else
    {
        if ((node->left == NULL) || (node->right == NULL))
        {
            Node* tempt;
            if (node->left == NULL)
            {
                tempt = node->right;
            }
            else
            {
                tempt = node->left;
            }

            if (tempt == NULL)
            {
                tempt = node;
                node = NULL;
            }
            else
            {
                node = tempt;
            }
        }
        else
        {
            Node* current = node->right;
            while (current->left != NULL)
            {
                current = current->left;
            }
            node->key = current->key;
            node->right = deletion(node->right, current->key);
        }
    }

    if (node == NULL)
    {
        return node;
    }

    node->height = get_height(node);

    int factor = get_factor(node);

    if (factor > 1 && get_factor(node->left) >= 0)
    {
        return right_rotate(node);
    }
    if (factor > 1 && get_factor(node->left) < 0)
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    if (factor < -1 && get_factor(node->right) <= 0)
    {
        return left_rotate(node);
    }
    if (factor < -1 && get_factor(node->right) > 0)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    
    return node;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


int AVLTree::insert(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    Node* current = _root;
    while (current != NULL)
    {
        if (current->key > key)
        {
            current = current->left;
        }
        else if (current->key < key)
        {
            current = current->right;
        }
        else
        {
            return 1;
        }
    }
    _root = insertion(_root, key);

    return 0;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int AVLTree::erase(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    Node* current = _root;
    bool del = false;
    while (current != NULL)
    {
        if (current->key > key)
        {
            current = current->left;
        }
        else if (current->key < key)
        {
            current = current->right;
        }
        else
        {
            del = true;
            break;
        }
    }
    if (del == true)
    {
        _root = deletion(_root, key);
        return 0;
    }
    else
    {
        return 1;
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
