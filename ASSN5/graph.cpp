#include "graph.h"
#include <iostream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

string Graph::Depth_First(int index, bool visited[])
{
    string tempt;
    visited[index] = true;
    for (int i = 0; i < adj_list[index].size(); i++)
    {
        int next = adj_list[index][i] - 65;
        tempt = tempt + adj_list[index][i];
        if (visited[next] == false)
        {
            tempt = tempt + Depth_First(next, visited);
        }
    }

    return tempt;
}

void Graph::Cycle_Check(int head_index, int tempt_index, bool visited[], bool Stack[], int& count)
{
    if (visited[tempt_index] == true)
    {
        return;
    }
    else
    {
        Stack[tempt_index] = true;
        int next;
        for (int i = 0; i < adj_list[tempt_index].length(); i++)
        {
            next = adj_list[tempt_index][i] - 65;
            if (Stack[next] == false)
            {
                Cycle_Check(head_index, next, visited, Stack, count);
                Stack[next] = false;
            }
            else if ((Stack[next] == true) && (next == head_index))
            {
                count++;
            }
        }
    }
    return;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


int Graph::addEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    char A_ = nodeA[0];
    char B_ = nodeB[0];

    int index_A = A_ - 65;
    int index_B = B_ - 65;

    if (isDirected == true)
    {
        adj_list[index_A].push_back(B_);
    }
    else
    {
        adj_list[index_A].push_back(B_);
        adj_list[index_B].push_back(A_);
    }

    return 0;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::getConnectedComponent() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    bool visited[26];
    for (int i = 0; i < 26; i++)
    {
        visited[i] = false;
    }
    string store_longest = "";
    string tempt;

    for (int i = 0; i < 26; i++)
    {
        if (visited[i] == false)
        {
            tempt = Depth_First(i, visited);

            for (int i = 0; i < tempt.length(); ++i)
            {
                for (int j = 0; j < tempt.length() - i - 1; ++j)
                {
                    if (tempt[j] > tempt[j + 1])
                    {
                        char temp = tempt[j];
                        tempt[j] = tempt[j + 1];
                        tempt[j + 1] = temp;
                    }
                }
            }
            string sort;
            sort.push_back(tempt[0]);
            for (int i = 0; i < tempt.length(); i++)
            {
                for (int j = 0; j < sort.length(); j++)
                {
                    if (sort[j] == tempt[i])
                    {
                        break;
                    }
                    if (j == sort.length() - 1)
                    {
                        sort.push_back(' ');
                        sort.push_back(tempt[i]);
                    }
                }
            }
            if (sort.length() > store_longest.length())
            {
                store_longest = sort;
            }
        }
    }

    return store_longest;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::getCycleCount() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    bool visited[26];
    bool Stack[26];
    int count = 0;
    for (int i = 0; i < 26; i++)
    {
        visited[i] = false;
        Stack[i] = false;
    }

    for (int i = 0; i < 26; i++)
    {
        Cycle_Check(i, i, visited, Stack, count);
        visited[i] = true;
    }

    return count;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
