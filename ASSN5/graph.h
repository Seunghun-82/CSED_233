#pragma once
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


class Graph{
public:
    Graph(bool _isDirected = false) {
        isDirected = _isDirected;
    };
    ~Graph() { };

    int addEdge(string nodeA, string nodeB);
    string getConnectedComponent();
    int getCycleCount();

private:
    bool isDirected;
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    string adj_list[26];
    string Depth_First(int index, bool visited[]);
    void Cycle_Check(int head_index, int tempt_index, bool visited[], bool Stack[], int& count);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
