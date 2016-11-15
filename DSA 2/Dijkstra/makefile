Dijkstra.exe: Dijkstra.cpp Heap.o HashTable.o Graph.o
	g++ -std=c++11 -o Dijkstra.exe Dijkstra.cpp Graph.o Heap.o HashTable.o

Graph.o: Graph.cpp Graph.h
	g++ -std=c++11 -c Graph.cpp

Heap.o: Heap.cpp Heap.h
	g++ -std=c++11 -c Heap.cpp

HashTable.o: HashTable.cpp HashTable.h
	g++ -std=c++11 -c HashTable.cpp

debug:
	g++ -std=c++11 -g -o GraphDebug.exe Dijkstra.cpp Heap.cpp HashTable.cpp Graph.cpp

clean:
	rm -f *.exe *.o *.stackdump *~