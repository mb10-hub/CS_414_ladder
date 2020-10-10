---------------------Introduction---------------------
This program is based on a dictionary, each word has four letters.
This program builds a Adjacency Graph.
---------------------Features That Work---------------------
1)Compute the print the number of connected components in the graph. For each connected component, print the number of words that it contains.
2)Given two words, determine if there is a ladder between them or not. If there is a ladder between the two words, find a path between the two words via a depth-first search algorithm and the shortest path by use of the breadth-first search algorithm.
3)Find the length of the longest ladder in the dictionary. 

They all work and are tested intensively :)

---------------------Features The Do Not Work---------------------
cant take user input, 
only files. 
---------------------Possible Bugs---------------------
No bugs if you 
Compile: g++ -g -std=c++17 *.cpp -o x
Execute: ./x data.txt data_pairs.txt 

EXAMPLE:

data.txt:   data_pairs.txt 
    fake     fate kate                   
    lake     cell fate
    tate     lake fate
    kate     wall cell
    cell
    ball
    bate
    made
    rate
    fade
    bell
    wall
    fate
    slow