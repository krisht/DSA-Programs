useHeap: useHeap.o Heap.o HashTable.o
	g++ -std=c++11 -o useHeap.exe useHeap.o Heap.o HashTable.o

useHeap.o: useHeap.cpp
	g++ -std=c++11 -c useHeap.cpp

Heap.o: Heap.cpp Heap.h
	g++ -std=c++11 -c Heap.cpp

HashTable.o: HashTable.cpp HashTable.h
	g++ -std=c++11 -c HashTable.cpp

debug:
	g++ -g -o useHeapDebug.exe useHeap.cpp Heap.cpp HashTable.cpp

clean:
	rm -f *.exe *.o *.stackdump *~