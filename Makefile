x: main.o Dictionary.o Graph.o
	g++ -std=c++17 main.o Dictionary.o Graph.o -o x

main.o: main.cpp Graph.hpp Dictionary.hpp   
	g++ -std=c++17 main.cpp -c -o main.o

Dictionary.o: Dictionary.cpp Dictionary.hpp 
	g++ -std=c++17 Dictionary.cpp -c -o Dictionary.o

Graph.0: Graph.cpp Graph.hp Dictionary.hpp  
	g++ -std=c++17 Graph.cpp -c -o Graph.o

dubug:
	g++ -g -std=c++17 *.cpp -o x

clean:
	rm -rf *.o x
