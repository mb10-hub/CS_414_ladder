#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <stack>
#include <cmath>

using namespace std;

struct Node
{
    int index;
    vector<Node *> child;
    Node *parent;
};

class Graph
{
public:
    Graph();
    Graph(const vector<string> &words);
    int numConnectedComponents();
    int sizeOfConnectedComponent(int i);
    int size() { return listOfWords.size(); }
    bool ladderExists(string, string);
    void pfsPathFromTo(string, string, vector<string> &ladder);
    void pfs_helper(int, int, vector<string> &ladder, int, bool);
    // void bfs_helper(vector<int>&, vector<int>&, vector<int>&);
    void removeFromList(vector<string> &, string);
    void printLadder(Node *);
    void printMin_Paths(vector<tuple<int, int>> &, vector<Node *> &);
    void numMin_paths(Node *, vector<string> &ladder, int, int);
    int bfsPathFromTo(string, string, vector<string> &ladder);
    bool isAdjacent(string, string);
    void createAdjacencyList();
    void printVector(vector<string>);
    tuple<int, int> indexOfStart_Target(string, string);
    Node *newNode(int index, Node *parent_index);

private:
    vector<bool> visited;
    vector<bool> addedToList;
    vector<string> listOfWords;
    vector<vector<int>> Alist;
    vector<vector<int>> connectedComponents;
    vector<int> track;
    vector<vector<int>> levels;
};