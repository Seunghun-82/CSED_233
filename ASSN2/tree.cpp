#include "tree.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end) {
  if (start > end)
    return -1;

  string s;

  for (int i = start; i <= end; i++) {

    // if open parenthesis, push it
    if (str[i] == '(')
      s.push_back(str[i]);

    // if close parenthesis
    else if (str[i] == ')') {
      if (s.back() == '(') {
        s.pop_back();

        if (!s.length())
          return i;
      }
    }
  }
  // if not found return -1
  return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *BinaryTree::_buildFromString(const char *data, int start, int end) {
  if (start > end)
    return NULL;

  Node *root = new Node(data[start]);
  int index = -1;

  if (start + 1 <= end && data[start + 1] == '(')
    index = findIndex(data, start + 1, end);

  if (index != -1) { 
    root->left = _buildFromString(data, start + 2, index - 1);
    root->right = _buildFromString(data, index + 2, end - 1);
  }
  return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data) {
  Node *root = _buildFromString(data, 0, strlen(data) - 1);
  _root = root;
}

string BinaryTree::preOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
    string answer;
    static int first_trial = 0;
    first_trial++;
    if (_root == NULL)
    {
        return "";
    }
    Node* root_left = _root;
    Node* root_right = _root;
    if (first_trial == 1)
    {
        answer = _root->value;
    }
    else
    {
        answer = " ";
        answer += _root->value;
    }
    if (root_left->left == NULL && root_left->right == NULL)
    {
        answer = " ";
        answer += root_left->value;
        return answer;
    }
    else
    {
        _root = root_left->left;
        answer += preOrder();
    }
    if (root_right->left == NULL && root_right->right == NULL)
    {
        answer = " ";
        answer += root_right->value;
        return answer;
    }
    else
    {
        _root = root_right->right;
        answer += preOrder();
    }
    return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::postOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string answer;
    string tempt;
    static int first_trial = 0;
    if (_root == NULL)
    {
        return "";
    }
    Node* root_left = _root;
    Node* root_right = _root;
    tempt = _root->value;
    if (root_left->left == NULL && root_left->right == NULL)
    {
        if (first_trial == 0)
        {
            first_trial++;
            answer += _root->value;
        }
        else
        {
            answer = " ";
            answer += _root->value;
        }
        return answer;
    }
    else 
    {
        _root = root_left->left;
        answer += postOrder();
    }
    if (root_right->left == NULL && root_right->right == NULL)
    {
        answer = " ";
        answer += root_right->value;
        return answer;
    }
    else
    {
        _root = root_right->right;
        answer += postOrder();
    }
    answer += " ";
    answer += tempt;

    return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::inOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    string answer;
    string tempt;
    static int first_trial = 0;
    if (_root == NULL)
    {
        return "";
    }
    Node* root_left = _root;
    Node* root_right = _root;
    tempt = _root->value;
    if (root_left->left == NULL && root_left->right == NULL)
    {
        if (first_trial == 0)
        {
            first_trial++;
            answer += _root->value;
        }
        else
        {
            answer = " ";
            answer += _root->value;
        }
        return answer;
    }
    else
    {
        _root = root_left->left;
        answer += inOrder();
    }
    answer += " ";
    answer += tempt;
    if (root_right->left == NULL && root_right->right == NULL)
    {
        answer = " ";
        answer += root_right->value;
        return answer;
    }
    else
    {
        _root = root_right->right;
        answer += inOrder();
    }

    return answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BinaryTree::getHeight() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
    int left_max = 0;
    int right_max = 0;
    if (_root == NULL || (_root->right == NULL && _root->left == NULL))
    {
        if (left_max > right_max)
            return left_max;
        else
            return right_max;
    }
    Node* root = _root;
    _root = root->left;
    left_max = getHeight();
    _root = root->right;
    right_max = getHeight();
    if (left_max > right_max)
        return left_max + 1;
    else
        return right_max + 1;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

bool BinaryTree::isComplete() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
    bool left_true = true;
    bool right_true = true;
    bool check_end = false;
    if (_root == NULL)
    {
        return true;
    }
    Node* root = _root;
    if (check_end && (_root->left != NULL || _root->right != NULL))
        return false;

    if (_root->left == NULL && _root->right != NULL)
        return false;
    if (_root->left != NULL)
    {
        _root = root->left;
        left_true = isComplete();
    }
    else
        check_end = true;
    if (_root->right != NULL)
    {
        _root = root->right;
        right_true = isComplete();
    }
    else
        check_end = true;

    if (right_true && left_true)
        return true;
    else
        return false;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional private functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////