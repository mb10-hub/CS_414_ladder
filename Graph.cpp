#include "Graph.hpp"

using namespace std;

Graph::Graph(const vector<string> &words)
{
    cout << "Graph Constructor printing words . . ." << endl;
    for (auto word : words)
    {
        std::cout << word << std::endl;
        listOfWords.push_back(word);
        //create space to push to inside vector
        Alist.push_back(vector<int>());
    }

    // allocate the visisted Vector
    visited.resize(words.size());
    addedToList.resize(words.size());
}

void Graph::printVector(vector<string> ladder)
{
    for (auto word : ladder)
    {
        std::cout << word << std::endl;
    }
}

void Graph::createAdjacencyList()
{

    // For Loop that iterates through the graph for
    for (int i = 0; i < listOfWords.size() - 1; i++)
    {

        for (int j = i + 1; j < listOfWords.size(); j++)
        {
            if (isAdjacent(listOfWords[i], listOfWords[j]))
            {
                Alist[i].push_back(j);
                Alist[j].push_back(i);
            }
        }
    }
}

bool Graph::isAdjacent(string vertex1, string vertex2)
{
    int numDiff = 0;

    if (vertex1.size() != vertex2.size())
        return false;

    for (int i = 0; i < vertex1.size(); i++)
    {
        if (vertex1[i] != vertex2[i])
        {
            numDiff++;
        }
    }

    if (numDiff == 1)
        return true;

    else
        return false;
}

int Graph::numConnectedComponents()
{
    queue<int> q;

    // keep count of components
    int numComponents = 0;

    // For Loop that iterates through the graph for
    for (int i = 0; i < listOfWords.size(); i++)
    {
        // vertices that have not been addedToList
        if (!addedToList[i])
        {
            // vetex does not belong to any ladder so it must be a new one.
            numComponents++;

            //create space for my connectedComponent vector
            connectedComponents.push_back(vector<int>());

            //add first to a list of at least itself
            addedToList[i] = true;

            q.push(i);
            //push vertex that belong to the same component to their respected space numComponents - 1
            connectedComponents[numComponents - 1].push_back(i);

            while (!q.empty())
            {
                int front = q.front();
                q.pop();

                for (int j = 0; j < listOfWords.size(); j++)
                {
                    // if !visited and isAdjacent no need to check i == j
                    if (!addedToList[j] && isAdjacent(listOfWords[front], listOfWords[j]))
                    {
                        //it made the cut and need to add it belongs in a ladder.
                        addedToList[j] = true;
                        q.push(j);
                        //push vertex that belong to the same component to their respected space numComponents - 1
                        connectedComponents[numComponents - 1].push_back(j);
                    }
                }
            }
        }
    }
    return numComponents;
}

int Graph::sizeOfConnectedComponent(int i)
{
    if (i < 0 || i > connectedComponents.size())
    {
        cout << "Error index is out of bounds: " << endl;
        return -1111;
    }
    return connectedComponents[i].size();
}

tuple<int, int> Graph::indexOfStart_Target(string startWord, string targetWord)
{
    int start;
    int target;
    tuple<int, int> start_target;

    for (int i = 0; i < listOfWords.size(); i++)
    {

        if (listOfWords[i] == startWord)
        {
            start = i;
        }
        else if (listOfWords[i] == targetWord)
        {
            target = i;
        }
    }
    return make_tuple(start, target);
}

bool Graph::ladderExists(string startWord, string targetWord)
{
    //function needs testing

    tuple<int, int> Start_End = indexOfStart_Target(startWord, targetWord);
    int start = get<0>(Start_End);
    int target = get<1>(Start_End);

    bool flag1 = false;
    bool flag2 = false;

    //traverse thrugh connectedcomponents vector and find if they're in there
    for (int i = 0; i < connectedComponents.size(); i++)
    {
        for (int j = 0; j < connectedComponents[i].size(); j++)
        {
            if (!flag1 && start == connectedComponents[i][j])
            {
                flag1 = true;
            }
            if (!flag2 && target == connectedComponents[i][j])
            {
                flag2 = true;
            }
            if (flag1 && flag2)
            {

                return true;
            }
        }
    }
    return false;
}

void Graph::pfs_helper(int start, int target, vector<string> &ladder, int top, bool foundLadder)
{
    while (!ladder.empty() || !foundLadder)
    {

        for (int i = 0; i < listOfWords.size(); i++)
        {

            if (!visited[i] && isAdjacent(listOfWords[top], listOfWords[i]))
            {
                visited[i] = true;
                ladder.push_back(listOfWords[i]);
                track.push_back(i);

                if (listOfWords[i] == listOfWords[target])
                {
                    foundLadder = true;
                    return;
                }
                top = i;
                pfs_helper(start, target, ladder, top, foundLadder);
            }

            // else if (visited[i])
            // {
            //     ladder.pop_back();
            // }
        }
        if (!foundLadder)
        {
            ladder.pop_back();
            track.pop_back();
            top = track[track.size() - 1];
        }
    }
    return;
}

void Graph::pfsPathFromTo(string startWord, string targetWord, vector<string> &ladder)
{
    // iterativley if neighbor add to ladder, if theres no more neighbors then back track one. repeat
    tuple<int, int> Start_End = indexOfStart_Target(startWord, targetWord);
    int start = get<0>(Start_End);
    int target = get<1>(Start_End);
    int top = -1111;
    stack<int> s;

    s.push(start);
    visited[start] = true;
    ladder.push_back(listOfWords[start]);

    while (!s.empty())
    {
        top = s.top();
        s.pop();

        for (int i = 0; i < listOfWords.size(); i++)
        {

            if (!visited[i] && isAdjacent(listOfWords[top], listOfWords[i]))
            {
                s.push(i);
                visited[i] = true;
                ladder.push_back(listOfWords[i]);
                //what to look for adjacent values for the most recent adjacent member.
                top = i;
                //found path to target word.
                if (listOfWords[i] == targetWord)
                {
                    return;
                }
                //start looking from beggining
                i = 0;
            }
        }
        //backtrack the vector and the stack. ***stack might be unecessary
        ladder.pop_back();
        s.pop();
    }
    return;
}

// void Graph::bfs_helper(vector<int> &startList, vector<int> &unionList, vector<int> &targetList, string startWord, string targetWord)
// {
//     tuple<int, int> Start_End = indexOfStart_Target(startWord, targetWord);
//     int start = get<0>(Start_End);
//     int target = get<1>(Start_End);

//     for (int i = 0; i < Alist.size(); i++)
//     {
//         for (int j = 0; j < Alist[i].size(); j++)
//         {
//             if (i == start)
//             {
//                 startList.push_back(Alist[start][j]);
//             }
//             if (i == target)
//             {
//                 targetList.push_back(Alist[target][j]);
//             }
//         }
//     }
// }

Node *Graph::newNode(int index, Node *parent_index)
{
    Node *temp = new Node;
    temp->index = index;
    temp->parent = parent_index;
    return temp;
}

void Graph::printLadder(Node *grandChild)
{
    vector<int> ladder;
    ladder.push_back(grandChild->index);
    int iter = 0;

    while (grandChild->parent != nullptr)
    {
        ladder.push_back(grandChild->parent->index);
        grandChild = grandChild->parent;
    }

    for (int i = ladder.size() - 1; i >= 0; i--)
    {
        cout << iter + 1 << ": " << listOfWords[ladder[i]] << endl;
        iter++;
    }
}

int Graph::printMin_Paths(vector<tuple<int, int>> &depths_target_vect, vector<Node *> &minPaths)
{
    int min = 1000;
    int startAfter_i = 0;
    int end_i = 0;
    int numMins = 0;

    for (const auto &i : depths_target_vect)
    {
        if (get<1>(i) < min)
        {
            end_i += get<0>(i);
            startAfter_i = abs(end_i - get<0>(i));
            min = get<1>(i);
            numMins = get<0>(i);
        }
    }
    cout << endl;
    cout << "Number of min ladders: " << numMins << endl;
    for (int i = startAfter_i; i < end_i; i++)
    {
        printLadder(minPaths[startAfter_i]);
    }
    return numMins;
}

void Graph::num_paths(Node *root, vector<Node *> &Paths, vector<tuple<int, int>> &depths_target_vect, int target)
{
    if (root == nullptr)
    {
        return;
    }

    queue<Node *> q_node;
    q_node.push(root);
    Node *curr = nullptr;
    int sizeOfLevel = 0;
    int depthOfTarget = 0; // can be used for max depth aka longest path
    bool targetFound = false;
    int numTargetFoundAtLevel = 0;

    while (!q_node.empty())
    {
        sizeOfLevel = q_node.size();

        while (sizeOfLevel > 0)
        {

            curr = q_node.front();
            q_node.pop();

            for (int i = 0; i < curr->child.size(); i++)
            {
                q_node.push(curr->child[i]);
                if (curr->child[i]->index == target)
                {
                    numTargetFoundAtLevel++;
                    targetFound = true;
                    Paths.push_back(curr->child[i]);
                }
            }
            sizeOfLevel--;
        }
        depthOfTarget++;
        if (targetFound)
        {
            depths_target_vect.push_back(make_tuple(numTargetFoundAtLevel, depthOfTarget));
            numTargetFoundAtLevel = 0;
            targetFound = false;
        }
    }
}

int Graph::bfsPathFromTo(string startWord, string targetWord, vector<string> &ladder)
{
    // Initializations
    tuple<int, int> Start_End = indexOfStart_Target(startWord, targetWord);
    int start = get<0>(Start_End);
    int target = get<1>(Start_End);
    queue<int> q;
    queue<Node *> q_nodes; //** Might not need for making tree
    int front = -1111;
    int numLadders = 0;
    int depth = 0;
    int numPushes = 0;
    Node *curr = nullptr;
    int i_curr_children = 0;
    int i_Alist = 0;
    vector<Node *> Paths;
    vector<tuple<int, int>> depths_target_vect;
    // Initializations/

    //create root (startWord, no Parent)
    Node *root = newNode(start, nullptr);

    q.push(start);
    q_nodes.push(root); // push root to the queue *** might not need for making tree

    while (!q.empty())
    {

        front = q.front();
        curr = q_nodes.front();
        q.pop();
        q_nodes.pop();

        ladder.push_back(listOfWords[front]);

        if (i_Alist < Alist.size())
        {
            for (int i = 0; i < Alist[front].size(); i++)
            {
                if (((curr->parent == nullptr || Alist[front][i] != curr->parent->index) && (curr->index != Alist[front][i])) && Alist[front][i] != start && curr->index != target)
                {
                    q.push(Alist[front][i]);
                    visited[Alist[front][i]] = true;
                    //add the all the children for curr
                    curr->child.push_back(newNode(Alist[front][i], curr));
                    //add the children to Q of Nodes to look for grandchildren
                    q_nodes.push(curr->child[i_curr_children]);
                    i_curr_children++;
                }
            }
        }
        i_Alist++;
        visited[front] = true;
        i_curr_children = 0;
    }
    num_paths(root, Paths, depths_target_vect, target);
    numLadders = printMin_Paths(depths_target_vect, Paths);
    return numLadders;
}

void Graph::resetVisited()
{
    for (int i = 0; i < visited.size(); i++)
    {
        visited[i] = false;
    }
}

int Graph::getDepth_path(Node *curr, Node *&deepest)
{

    if (curr == nullptr)
    {
        return -1111;
    }

    queue<Node *> q_node;
    q_node.push(curr);
    int sizeOfLevel = 0;
    //save any node
    int depthOfTarget = 0; // can be used for max depth aka longest path

    while (!q_node.empty())
    {
        sizeOfLevel = q_node.size();

        while (sizeOfLevel > 0)
        {

            curr = q_node.front();
            q_node.pop();

            for (int i = 0; i < curr->child.size(); i++)
            {
                q_node.push(curr->child[i]);
                deepest = curr->child[i];
            }
            sizeOfLevel--;
        }
        depthOfTarget++;
    }
    return depthOfTarget;
}

void Graph::inQ_visited(deque<Node *> q_nodes, vector<bool> &visited)
{
    int end = q_nodes.size();

    for (int i = 0; i < end; i++)
    {
        visited[q_nodes.front()->index] = true;
        q_nodes.pop_front();
    }
}

void Graph::children_true(Node *curr, vector<bool> &visited)
{

    for (int i = 0; i < curr->child.size(); i++)
    {
        visited[curr->child[i]->index] = true;
    }
}

void Graph::longestLadder()
{
    // Initializations
    // queue<Node *> q_nodes; //** Might not need for making tree
    deque<Node *> q_nodes;
    int front = -1111;
    int depth = 0;
    int max = -1000;
    Node *curr = nullptr;
    Node *parent = nullptr;
    int i_curr_children = 0;
    int i_Alist = 0;
    vector<Node *> Paths;
    vector<tuple<int, int>> depths_target_vect;
    Node *most_deep = nullptr;
    Node *max_most_deep = nullptr;
    int iter = 0;
    int location = 0;
    // Initializations/

    for (int j = 0; j < listOfWords.size(); j++)
    {
        //create root (startWord, no Parent)
        Node *root = newNode(j, nullptr);
        // visited[0] = true;

        q_nodes.push_front(root); // push root to the queue *** might not need for making tree

        while (!q_nodes.empty())
        {

            curr = q_nodes.back();
            front = curr->index;
            visited[root->index] = true;

            if (curr->child.size() > 0)
            {
                children_true(curr, visited);
            }

            for (int i = 0; i < Alist[front].size(); i++)
            {

                if (!visited[Alist[front][i]])
                {
                    // inQ_visited(q_nodes, visited);??
                    visited[Alist[front][i]] = true;
                    //add the all the children for curr
                    curr->child.push_back(newNode(Alist[front][i], curr));
                    //add the children to Q of Nodes to look for grandchildren
                    q_nodes.push_back(curr->child[curr->child.size() - 1]);

                    front = Alist[front][i];
                    i = 0;
                    curr = curr->child[curr->child.size() - 1];
                }
                resetVisited();
                children_true(curr, visited);
                inQ_visited(q_nodes, visited);
            }

            resetVisited();
            inQ_visited(q_nodes, visited);
            q_nodes.pop_back();
            iter++;
            i_Alist++;
        }

        depth = getDepth_path(root, most_deep);

        if (depth > max)
        {
            max = depth;
            max_most_deep = most_deep;
        }
    }
    cout << "Longest Ladder in Dictionary: " << max << endl;
    printLadder(max_most_deep);
}