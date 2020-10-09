//
// Created by Ali A. Kooshesh on 2020-01-20, modified on 2020-09-15
// Modified by Marco A. Barragan on 2020-09-21
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include "Graph.hpp"

void readStartTargetWords(const std::string &inputFileName, std::vector<std::tuple<std::string, std::string>> &startTargetVector)
{
    std::ifstream pairStream;
    pairStream.open(inputFileName, std::ios_base::in);
    if (!pairStream.is_open())
    {
        std::cout << "Unable to open the input file ->" << inputFileName << "<- that contains pairs of words.\n";
        exit(2);
    }
    std::cout << "Successfully opened " << inputFileName << std::endl;

    std::string start, target;
    while (pairStream >> start && pairStream >> target)
    {
        startTargetVector.push_back(std::make_tuple(start, target));
    }
}

void readWords(std::fstream &inStream, std::vector<std::string> &words)
{
    // inStream is an open stream. This function reads a series of words
    // from the stream and stores them in "words".

    std::string word;
    while (inStream >> word)
        words.push_back(word);
}

int main(int argc, char *argv[])
{ // the main function.
    if (argc != 3)
    {
        std::cout << "usage: " << argv[0] << " inputFileNameThatContainsDictionary inputFileNameThatContainsPairsOfWords\n";
        exit(1);
    }

    std::fstream wordStream;
    wordStream.open(argv[1], std::ios_base::in);
    if (!wordStream.is_open())
    {
        std::cout << "Unable to open input file ->" << argv[1] << "<-\n";
        exit(2);
    }
    std::cout << "Successfully opened " << argv[1] << std::endl;

    std::vector<std::string> dictionary;
    readWords(wordStream, dictionary);
    for (auto word : dictionary)
        std::cout << word << std::endl;

    std::vector<std::tuple<std::string, std::string>> startTargetVector;
    readStartTargetWords(argv[2], startTargetVector);
    for (auto [start, target] : startTargetVector)
        std::cout << start << " " << target << std::endl;

    //Call Graph constructor to give Graph access to the dictionary vector and all my Initializations
    cout << endl;
    Graph Graph(dictionary);
    cout << endl;
    Graph.createAdjacencyList();
    vector<string> ladder;
    int num_connected_components = Graph.numConnectedComponents();

    cout << "number of connected components: " << num_connected_components << endl;

    for (int i = 0; i < num_connected_components; i++)
    {
        cout << "size of connected component at " << i << ": " << Graph.sizeOfConnectedComponent(i) << endl;
    }

    cout << "size of Graph: " << Graph.size() << endl;

    cout << "Is there a ladder between the pairs: " << endl;
    for (const auto &i : startTargetVector)
    {
        cout << get<0>(i) << " ==> " << get<1>(i) << " : " << Graph.ladderExists(get<0>(i), get<1>(i)) << endl;
    }

    cout << "dfs Algorithm: " << endl;
    for (const auto &i : startTargetVector)
    {
        cout << "dfs path for :" << get<0>(i) << " ==> " << get<1>(i) << endl;
        Graph.pfsPathFromTo(get<0>(i), get<1>(i), ladder);
        Graph.printVector(ladder);
    }

    cout << "bfs Algorithm: " << endl;
    for (const auto &i : startTargetVector)
    {
        cout << "bfs path for :" << get<0>(i) << " ==> " << get<1>(i) << endl;
        Graph.bfsPathFromTo(get<0>(i), get<1>(i), ladder);
        Graph.printVector(ladder);
    }

    Graph.longestLadder();

    return 0;
}
