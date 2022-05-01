#pragma once
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////
#define INF 10000000
struct node
{
    string vertex;
    int weight;
    node* next;
    int indegree;
};
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph{
public:
    Graph() 
    {
        for (int i = 0; i < 100; i++)
        {
            vertex_adj[i] = new node;
            vertex_adj[i]->indegree = 0;
        }
        for (int i = 0; i < 100; i++)
        {
            visited[i] = false;
        }
        store_number = 0;
        vertex_number = 0;
        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                weight_store[i][j] = INF;
            }
        }
    };
    ~Graph() { };

    int addDirectedEdge(string nodeA, string nodeB);
    int addDirectedEdge(string nodeA, string nodeB, int weight);
    int addUndirectedEdge(string nodeA, string nodeB);
    int addUndirectedEdge(string nodeA, string nodeB, int weight);

    string DFS();
    string getTopologicalSort();
    string getShortestPath(string source, string destination);
    string getAllShortestPaths();
    int primMST(ofstream &, string startNode);
    int kruskalMST(ofstream &);


private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    int vertex_number;
    bool visited[100];
    int* store_vertex;
    int store_number;
    string store_alphabet;
    int weight_store[26][26];
    node* vertex_adj[100];
    string adj_list[26];
    int primMST_main(ofstream& fout, string startNode, int* distance[]);
    int kruskalMST_main(ofstream& fout, int* distance[]);
    string Depth_First(int index, bool visited[]);
    int getCycleCount();
    void Cycle_Check(int head_index, int tempt_index, bool visited[], bool Stack[], int& count);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
