#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
#define INF 10000000

void Graph::Cycle_Check(int head_index, int tempt_index, bool visited[], bool Stack[], int& count) // 저번코드 들고왔습니다.
{
    if (visited[tempt_index] == true)
    {
        return;
    }
    else if (visited[tempt_index] == false)
    {
        Stack[tempt_index] = true;
        int next_int_index ;
        for (node* next_index = vertex_adj[tempt_index]->next; next_index != NULL; next_index = next_index->next)
        {
            for (int i = 0; i < vertex_number; i++)
            {
                if (vertex_adj[i]->vertex == next_index->vertex)
                {
                    next_int_index = i;
                    break;
                }
            }
            if (Stack[next_int_index] == false)
            {
                Cycle_Check(head_index, next_int_index, visited, Stack, count);
                Stack[next_int_index] = false;
            }
            else if ((Stack[next_int_index] == true) && (next_int_index == head_index))
            {
                count++;
            }
        }
    }
    return;
} 

int Graph::getCycleCount() // 저번코드 들고왔습니다.
{

    bool* visited = new bool[vertex_number];
    bool* Stack = new bool[vertex_number];
    int count = 0;

    for (int i = 0; i < vertex_number; i++)
    {
        visited[i] = false;
        Stack[i] = false;
    }

    for (int i = 0; i < vertex_number; i++)
    {
        Cycle_Check(i, i, visited, Stack, count);
        visited[i] = true;
    }

    return count;

}

string Graph::Depth_First(int index, bool visited[])
{
    string tempt;
    visited[index] = true;
    for (node* next_index = vertex_adj[index]->next; next_index != NULL; next_index = next_index->next)
    {
        int next_int_index = 0;
        tempt = tempt + vertex_adj[index]->vertex + " ";
        bool is_it_in = false;
        int vertex_tempt = stoi(vertex_adj[index]->vertex);
        for (int i = 0; i < store_number; i++)
        {
            if (store_vertex[i] == vertex_tempt)
            {
                is_it_in = true;
            }
        }
        if (is_it_in == false)
        {
            int* TEMP = new int[store_number];
            for (int i = 0; i < store_number; i++)
            {
                TEMP[i] = store_vertex[i];
            }
            store_number++;
            store_vertex = new int[store_number];
            for (int i = 0; i < store_number - 1; i++)
            {
                store_vertex[i] = TEMP[i];
            }
            store_vertex[store_number - 1] = stoi(vertex_adj[index]->vertex);
        }
        for (int i = 0; i < vertex_number; i++)
        {
            if (vertex_adj[i]->vertex == next_index->vertex)
            {
                next_int_index = i;
                break;
            }
        }
        if (visited[next_int_index] == false)
        {
            tempt = tempt + Depth_First(next_int_index, visited);
        }
    }

    return tempt;
}

int minimum_index(int distance[], int n, bool found[])
{
    int minimum, minimum_indx;
    minimum = INF;
    minimum_indx = -1;
    for (int i = 0; i < n; i++)
    {
        if (distance[i] < minimum && found[i] == false)
        {
            minimum = distance[i];
            minimum_indx = i;
        }
    }
    return minimum_indx;
}

int Graph::primMST_main(ofstream& fout, string startNode, int* distance[])
{
    int* store_parent = new int[store_alphabet.size()];
    int* store_key = new int[store_alphabet.size()];
    bool* inside_MST = new bool[store_alphabet.size()];
    int sum = 0;

    for (int i = 0; i < store_alphabet.size(); i++)
    {
        store_key[i] = INF;
        inside_MST[i] = false;
    }
    int start_index = startNode[0] - 65;
    store_parent[start_index] = -1;
    store_key[start_index] = 0;

    for (int i = 0; i < store_alphabet.size() - 1; i++)
    {
        int min = INF;
        int min_index;

        for (int j = 0; j < store_alphabet.size(); j++)
        {
            if (inside_MST[j] == false && store_key[j] < min)
            {
                min = store_key[j];
                min_index = j;
            }
        }

        inside_MST[min_index] = true;

        for (int j = 0; j < store_alphabet.size(); j++)
        {
            if (distance[min_index][j] && inside_MST[j] == false && distance[min_index][j] < store_key[j])
            {
                store_parent[j] = min_index;
                store_key[j] = distance[min_index][j];
            }
        }
        int index_K;
        int store_min_key = INF;
        for (int k = 0; k < store_alphabet.size(); k++)
        {
            if (min_index != k)
            {
                if (inside_MST[k] == false)
                {
                    if (store_key[k] < store_min_key)
                    {
                        store_min_key = store_key[k];
                        index_K = k;
                    }
                }
            }
        }
        char parent = store_parent[index_K] + 65;
        char child = index_K + 65;
        fout << parent << " " << child << " " << store_key[index_K] << endl;
        sum += store_key[index_K];
    }
    return sum;
}

int find_index(int index,int parent[])
{
    while (parent[index] != index)
    {
        index = parent[index];
    }
        return index;
}

int Graph::kruskalMST_main(ofstream& fout, int* distance[])
{
    int minimum_cost = 0;
    int* parent = new int[store_alphabet.size()];
    for (int i = 0; i < store_alphabet.size(); i++)
    {
        parent[i] = i;
    }
    for (int edge_count = 0; edge_count < store_alphabet.size() - 1; edge_count++)
    {
        int min_cost = INF;
        int source = -1;
        int desti = -1;
        for (int i = 0; i < store_alphabet.size(); i++)
        {
            for (int j = 0; j < store_alphabet.size(); j++)
            {
                if (find_index(i,parent) != find_index(j,parent) && distance[i][j] < min_cost)
                {
                    min_cost = distance[i][j];
                    source = i;
                    desti = j;
                }
            }
        }
        int starting_index = find_index(source, parent);
        int ending_index = find_index(desti, parent);
        parent[starting_index] = ending_index;

        char parent = source + 65;
        char child = desti + 65;
        fout << parent << " " << child << " " << min_cost << endl;
        minimum_cost += min_cost;
    }
    return minimum_cost;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


int Graph::addDirectedEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    bool A = false;
    bool B = false;
    int index_A = -1;
    int index_B = -1;
    for (int i = 0; i < vertex_number; i++)
    {
        if (vertex_adj[i]->vertex == nodeA)
        {
            A = true;
            index_A = i;
        }
        if (vertex_adj[i]->vertex == nodeB)
        {
            B = true;
            index_B = i;
        }
    }
    for (int i = 0; i < vertex_number; i++)
    {
        if (vertex_adj[i]->vertex == nodeA)
        {
            A = true;
            index_A = i;
        }
        if (vertex_adj[i]->vertex == nodeB)
        {
            B = true;
            index_B = i;
        }
    }
    if ((A == true) && (B == true))
    {
        node* NODE_A = new node;
        NODE_A->next = NULL;
        NODE_A->vertex = nodeB;
        node* add_nodeA = vertex_adj[index_A]->next;
        node* before = vertex_adj[index_A];
        while (add_nodeA != NULL)
        {
            int A, B;
            A = stoi(add_nodeA->vertex);
            B = stoi(NODE_A->vertex);
            if (A > B)
            {
                break;
            }
            add_nodeA = add_nodeA->next;
        }
        while (!((before->next == add_nodeA) || (before == add_nodeA)))
        {
            before = before->next;
        }
        vertex_adj[index_B]->indegree++;

        before->next = NODE_A;
        NODE_A->next = add_nodeA;
    }
    else if ((A == true) || (B == true))
    {
        node* NODE_A = new node;
        NODE_A->next = NULL;
        NODE_A->vertex = nodeB;

        if (A == false)
        {
            vertex_adj[vertex_number]->vertex = nodeA;
            vertex_adj[vertex_number]->next = NULL;
            vertex_number++;
        }
        else if (B == false)
        {
            vertex_adj[vertex_number]->vertex = nodeB;
            vertex_adj[vertex_number]->next = NULL;
            vertex_number++;
        }
        node* add_node = vertex_adj[vertex_number - 1];
        if (index_A != -1)
        {
            add_node = vertex_adj[index_A];
        }
        else
        {
            add_node = vertex_adj[vertex_number - 1];
        }
        node* before = add_node;
        while (before->next != NULL)
        {
            int A, B;
            A = stoi(add_node->vertex);
            B = stoi(NODE_A->vertex);
            if (A > B)
            {
                break;
            }
            before = add_node;
            add_node = add_node->next;
        }

        if (index_B != -1)
        {
            vertex_adj[index_B]->indegree++;
        }
        else
        {
            vertex_adj[vertex_number - 1];
        }

        if (add_node == before)
        {
            add_node->next = NODE_A;
        }
        else
        {
            before->next = NODE_A;
            NODE_A->next = add_node;
        }
    }
    else
    {
        node* NODE_A = new node;
        NODE_A->next = NULL;
        NODE_A->vertex = nodeB;

        node* NODE_B = new node;
        NODE_B->next = NULL;
        NODE_B->vertex = nodeA;

        vertex_adj[vertex_number]->vertex = nodeA;
        vertex_adj[vertex_number]->next = NULL;
        vertex_number++;

        vertex_adj[vertex_number]->vertex = nodeB;
        vertex_adj[vertex_number]->next = NULL;
        vertex_adj[vertex_number]->indegree++;
        vertex_number++;

        node* add_nodeA = vertex_adj[vertex_number - 2];
        node* before = add_nodeA;
        while (before->next != NULL)
        {
            int A, B;
            A = stoi(add_nodeA->vertex);
            B = stoi(NODE_B->vertex);
            if (A > B)
            {
                break;
            }
            before = add_nodeA;
            add_nodeA = add_nodeA->next;
        }
        if (add_nodeA == before)
        {
            add_nodeA->next = NODE_A;
        }
        else
        {
            before->next = NODE_A;
            NODE_A->next = add_nodeA;
        }
    }

    for (int i = 0; i < vertex_number; ++i)
    {
        for (int j = 0; j < vertex_number - i - 1; ++j)
        {
            int A, B;
            A = stoi(vertex_adj[j]->vertex);
            B = stoi(vertex_adj[j + 1]->vertex);
            if (A > B)
            {
                node* temp = vertex_adj[j];
                vertex_adj[j] = vertex_adj[j + 1];
                vertex_adj[j + 1] = temp;
            }
        }
    }
    return 0;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    char A_ = nodeA[0];
    char B_ = nodeB[0];

    int index_A = A_ - 65;
    int index_B = B_ - 65;

    adj_list[index_A].push_back(B_);
    weight_store[index_A][index_B] = weight;

    bool in_A = false;
    bool in_B = false;

    for (int i = 0; i < store_alphabet.length(); i++)
    {
        if (A_ == store_alphabet[i])
        {
            in_A = true;
        }
        if (B_ == store_alphabet[i])
        {
            in_B = true;
        }
    }
    if (in_A == false)
    {
        store_alphabet.push_back(A_);
    }
    if (in_B == false)
    {
        store_alphabet.push_back(B_);
    }

    for (int i = 0; i < store_alphabet.length(); ++i)
    {
        for (int j = 0; j < store_alphabet.length() - i - 1; ++j)
        {
            if (store_alphabet[j] > store_alphabet[j + 1])
            {
                char temp = store_alphabet[j];
                store_alphabet[j] = store_alphabet[j + 1];
                store_alphabet[j + 1] = temp;
            }
        }
    }

    return 0;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    bool A = false;
    bool B = false;
    int index_A = -1;
    int index_B = -1;
    for (int i = 0; i < vertex_number; i++)
    {
        if (vertex_adj[i]->vertex == nodeA)
        {
            A = true;
            index_A = i;
        }
        if (vertex_adj[i]->vertex == nodeB)
        {
            B = true;
            index_B = i;
        }
    }
    if ((A == true) && (B == true))
    {
        node* NODE_A = new node;
        NODE_A->next = NULL;
        NODE_A->vertex = nodeB;
        node* add_nodeA = vertex_adj[index_A]->next;
        node* before = add_nodeA;
        while (add_nodeA != NULL)
        {
            int A, B;
            A = stoi(add_nodeA->vertex);
            B = stoi(NODE_A->vertex);
            if (A > B)
            {
                break;
            }
            add_nodeA = add_nodeA->next;
        }
        while (!((before->next == add_nodeA) || (before == add_nodeA)))
        {
            before = before->next;
        }

        before->next = NODE_A;
        NODE_A->next = add_nodeA;

        node* NODE_B = new node;
        NODE_B->next = NULL;
        NODE_B->vertex = nodeA;
        node* add_nodeB = vertex_adj[index_B]->next;
        before = add_nodeB;

        while (add_nodeB != NULL)
        {
            int A, B;
            A = stoi(add_nodeB->vertex);
            B = stoi(NODE_B->vertex);
            if (A > B)
            {
                break;
            }
            add_nodeB = add_nodeB->next;
        }

        while (!((before->next != add_nodeB) || (before != add_nodeB)))
        {
            before = before->next;
        }

        before->next = NODE_B;
        NODE_B->next = add_nodeB;
    }
    else if ((A == true) || (B == true))
    {
        node* NODE_A = new node;
        NODE_A->next = NULL;
        NODE_A->vertex = nodeB;

        if (A == false)
        {
            vertex_adj[vertex_number]->vertex = nodeA;
            vertex_adj[vertex_number]->next = NULL;
            vertex_number++;
        }
        else if (B == false)
        {
            vertex_adj[vertex_number]->vertex = nodeB;
            vertex_adj[vertex_number]->next = NULL;
            vertex_number++;
        }
        node* add_node = vertex_adj[vertex_number - 1];
        if (index_A != -1)
        {
            add_node = vertex_adj[index_A];
        }
        else
        {
            add_node = vertex_adj[vertex_number - 1];
        }
        node* before = add_node;
        while (before->next != NULL)
        {
            int A, B;
            A = stoi(add_node->vertex);
            B = stoi(NODE_A->vertex);
            if (A > B)
            {
                break;
            }
            before = add_node;
            add_node = add_node->next;
        }

        if (add_node == before)
        {
            add_node->next = NODE_A;
        }
        else
        {
            before->next = NODE_A;
            NODE_A->next = add_node;
        }

        node* NODE_B = new node;
        NODE_B->next = NULL;
        NODE_B->vertex = nodeA;

        if (index_B != -1)
        {
            add_node = vertex_adj[index_B];
        }
        else
        {
            add_node = vertex_adj[vertex_number - 1];
        }
        before = add_node;
        while (before->next != NULL)
        {
            int A, B;
            A = stoi(add_node->vertex);
            B = stoi(NODE_B->vertex);
            if (A > B)
            {
                break;
            }
            before = add_node;
            add_node = add_node->next;
        }
        if (add_node == before)
        {
            add_node->next = NODE_B;
        }
        else
        {
            before->next = NODE_B;
            NODE_B->next = add_node;
        }
    }
    else
    {
        node* NODE_A = new node;
        NODE_A->next = NULL;
        NODE_A->vertex = nodeB;

        node* NODE_B = new node;
        NODE_B->next = NULL;
        NODE_B->vertex = nodeA;

        vertex_adj[vertex_number]->vertex = nodeA;
        vertex_adj[vertex_number]->next = NULL;
        vertex_number++;

        vertex_adj[vertex_number]->vertex = nodeB;
        vertex_adj[vertex_number]->next = NULL;
        vertex_number++;

        node* add_nodeA = vertex_adj[vertex_number - 2];
        node* before = add_nodeA;
        while (before->next != NULL)
        {
            int A, B;
            A = stoi(add_nodeA->vertex);
            B = stoi(NODE_B->vertex);
            if (A > B)
            {
                break;
            }
            before = add_nodeA;
            add_nodeA = add_nodeA->next;
        }
        if (add_nodeA == before)
        {
            add_nodeA->next = NODE_A;
        }
        else
        {
            before->next = NODE_A;
            NODE_A->next = add_nodeA;
        }

        node* add_nodeB = vertex_adj[vertex_number - 1];
        before = add_nodeB;
        while (before->next != NULL)
        {
            int A, B;
            A = stoi(add_nodeB->vertex);
            B = stoi(NODE_B->vertex);
            if (A > B)
            {
                break;
            }
            before = add_nodeB;
            add_nodeB = add_nodeB->next;
        }
        if (add_nodeB == before)
        {
            add_nodeB->next = NODE_B;
        }
        else
        {
            before->next = NODE_B;
            NODE_B->next = add_nodeB;
        }
    }

    for (int i = 0; i < vertex_number; ++i)
    {
        for (int j = 0; j < vertex_number - i - 1; ++j)
        {
            int A, B;
            A = stoi(vertex_adj[j]->vertex);
            B = stoi(vertex_adj[j + 1]->vertex);
            if (A > B)
            {
                node* temp = vertex_adj[j];
                vertex_adj[j] = vertex_adj[j + 1];
                vertex_adj[j + 1] = temp;
            }
        }
    }

    return 0;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    char A_ = nodeA[0];
    char B_ = nodeB[0];

    int index_A = A_ - 65;
    int index_B = B_ - 65;

    adj_list[index_A].push_back(B_);
    adj_list[index_B].push_back(A_);
    weight_store[index_A][index_B] = weight;
    weight_store[index_B][index_A] = weight;

    for (int i = 0; i < adj_list[index_A].length(); ++i)
    {
        for (int j = 0; j < adj_list[index_A].length() - i - 1; ++j)
        {
            if (adj_list[index_A][j] > adj_list[index_A][j+1])
            {
                char temp = adj_list[index_A][j];
                adj_list[index_A][j] = adj_list[index_A][j + 1];
                adj_list[index_A][j + 1] = temp;
            }
        }
    }

    bool in_A = false;
    bool in_B = false;

    for (int i = 0; i < store_alphabet.length(); i++)
    {
        if (A_ == store_alphabet[i])
        {
            in_A = true;
        }
        if (B_ == store_alphabet[i])
        {
            in_B = true;
        }
    }
    if (in_A == false)
    {
        store_alphabet.push_back(A_);
    }
    if (in_B == false)
    {
        store_alphabet.push_back(B_);
    }

    for (int i = 0; i < store_alphabet.length(); ++i)
    {
        for (int j = 0; j < store_alphabet.length() - i - 1; ++j)
        {
            if (store_alphabet[j] > store_alphabet[j + 1])
            {
                char temp = store_alphabet[j];
                store_alphabet[j] = store_alphabet[j + 1];
                store_alphabet[j + 1] = temp;
            }
        }
    }

    return 0;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::DFS() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    for (int i = 0; i < vertex_number; i++)
    {
        visited[i] = false;
    }
    string answer = "\0";
    int component[100];
    int component_number = 1;
    component[0] = 0;
    for (int i = 0; i < vertex_number; i++)
    {
        if (visited[i] == false)
        {
            Depth_First(i, visited);
            component[component_number] = store_number;
            component_number++;
        }
    }

    for (int i = 0; i < component_number - 1; i++)
    {
        for (int j = component[i]; j < component[i + 1]; j++)
        {
            if (j == (component[i + 1] - 1))
            {
                string tempt = to_string(store_vertex[j]);
                answer += tempt;
            }
            else
            {
                string tempt = to_string(store_vertex[j]);
                answer += tempt + " ";
            }
        }
        if (i == (component_number - 2))
        {

        }
        else
        {
            answer += "\n";
        }
    }
    
    return answer;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string Graph::getTopologicalSort() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (getCycleCount() > 0)
    {
        return "error";
    }
    else
    {
        return "";
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string Graph::getShortestPath(string source, string destination) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int start = source[0] - 65;
    bool* check_in = new bool[26];
    int* distance = new int[26];
    int* Ancestor = new int[26];
    for (int i = 0; i < 26; i++)
    {
        distance[i] = weight_store[start][i];
        check_in[i] = false;
    }
    check_in[start] = true;

    for (int i = 0; i < 25 ; i++) 
    {
        
        int minimum;
        minimum = minimum_index(distance, 26, check_in);
        if (minimum == -1)
        {
            break;
        }
        check_in[minimum] = true;

        for(int j = 0; j < 26; j++)
        {
            if (check_in[j] == false)
            {

                if (distance[minimum] + weight_store[minimum][j] < distance[j])
                {
                    distance[j] = distance[minimum] + weight_store[minimum][j];
                    Ancestor[j] = minimum;
                }
            }
        }
    }
    int last_index = destination[0] - 65;
    if (distance[destination[0] - 65] == INF)
    {
        return "error";
    }
    string answer;
    while (1)
    {
        char A = last_index + 65;
        answer += A;
        if (last_index == start)
        {
            break;
        }
        if (last_index < 0)
        {
            break;
        }
        last_index = Ancestor[last_index];
        
    }
    string real_answer;
    for (int i = answer.length() - 1; i >= 0; i--)
    {
        real_answer.push_back(answer[i]);
        real_answer.push_back(' ');
    }
    string dis = to_string(distance[destination[0] - 65]);
    real_answer = real_answer + dis;
    if (distance[destination[0] - 65] == INF)
    {
        return "error";
    }
    return real_answer;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string Graph::getAllShortestPaths() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    int number = store_alphabet.size();

    int** distance = new int*[number];

    for (int i = 0; i < number; i++)
    {
        distance[i] = new int[store_alphabet.length()];
    }
    int* index_list = new int[store_alphabet.length()];
    for (int i = 0; i < store_alphabet.length(); i++)
    {
        char index = store_alphabet[i] - 65;
        index_list[i] = index;
    }

    for (int i = 0; i < store_alphabet.length(); i++)
    {
        for (int j = 0; j < store_alphabet.length(); j++)
        {
            if (i == j)
            {
                distance[i][j] = 0;
            }
            else
            {
                distance[i][j] = weight_store[index_list[i]][index_list[j]];
            }
        }
    }

    for (int i = 0; i < number; i++)
    {  
        for (int j = 0; j < number; j++)
        {
            for (int k = 0; k < number; k++)
            {

                if (distance[j][i] + distance[i][k] < distance[j][k])
                    distance[j][k] = distance[j][i] + distance[i][k];
            }
        }
    }

    string answer;
    for (int i = 0; i < number; i++)
    {
        for (int j = 0; j < number; j++)
        {
            if (j != number - 1)
            {
                if (i == j)
                {
                    answer = answer + "0" + " ";
                }
                else
                {
                    if (distance[i][j] >= (INF / 2))
                    {
                        answer = answer + "INF" + " ";
                    }
                    else
                    {
                        answer = answer + to_string(distance[i][j]) + " ";
                    }
                }
            }
            else
            {
                if (i == j)
                {
                    answer = answer + "0";
                }
                else
                {
                    if (distance[i][j] >= (INF / 2))
                    {
                        answer = answer + "INF";
                    }
                    else
                    {
                        answer = answer + to_string(distance[i][j]);
                    }
                }
            }
        }
        if (i == number - 1)
        {

        }
        else
        {
            answer += "\n";
        }
    }
    
    return answer;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::primMST(ofstream &fout, string startNode) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int number = store_alphabet.size();

    int** distance = new int* [number];

    for (int i = 0; i < number; i++)
    {
        distance[i] = new int[store_alphabet.length()];
    }
    int* index_list = new int[store_alphabet.length()];
    for (int i = 0; i < store_alphabet.length(); i++)
    {
        char index = store_alphabet[i] - 65;
        index_list[i] = index;
    }

    for (int i = 0; i < store_alphabet.length(); i++)
    {
        for (int j = 0; j < store_alphabet.length(); j++)
        {
            if (i == j)
            {
                distance[i][j] = 0;
            }
            else
            {
                distance[i][j] = weight_store[index_list[i]][index_list[j]];
            }
        }
    }

    return primMST_main(fout, startNode, distance);

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream &fout) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int number = store_alphabet.size();

    int** distance = new int* [number];

    for (int i = 0; i < number; i++)
    {
        distance[i] = new int[store_alphabet.length()];
    }
    int* index_list = new int[store_alphabet.length()];
    for (int i = 0; i < store_alphabet.length(); i++)
    {
        char index = store_alphabet[i] - 65;
        index_list[i] = index;
    }

    for (int i = 0; i < store_alphabet.length(); i++)
    {
        for (int j = 0; j < store_alphabet.length(); j++)
        {
            if (i == j)
            {
                distance[i][j] = 0;
            }
            else
            {
                distance[i][j] = weight_store[index_list[i]][index_list[j]];
            }
        }
    }
    return kruskalMST_main(fout, distance);

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}