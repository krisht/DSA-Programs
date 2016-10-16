UseHeap: UseHeap.o Heap.o HashTable.o
	g++ -std=c++11 -o UseHeap.exe UseHeap.o Heap.o HashTable.o

UseHeap.o: UseHeap.cpp
	g++ -std=c++11 -c UseHeap.cpp

Heap.o: Heap.cpp Heap.h
	g++ -std=c++11 -c Heap.cpp

HashTable.o: HashTable.cpp HashTable.h
	g++ -std=c++11 -c HashTable.cpp

debug:
	g++ -g -o UseHeapDebug.exe UseHeap.cpp Heap.cpp HashTable.cpp

clean:
	rm -f *.exe *.o *.stackdump *~