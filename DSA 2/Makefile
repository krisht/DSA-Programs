HeapChecker.exe: HeapChecker.o Heap.o HashTable.o
	g++ -o HeapChecker.exe HeapChecker.o Heap.o HashTable.o

HeapChecker.o: HeapChecker.cpp
	g++ -c HeapChecker.cpp

Heap.o: Heap.cpp Heap.h
	g++ -c Heap.cpp

HashTable.o: HashTable.cpp HashTable.h
	g++ -c HashTable.cpp

debug:
	g++ -g -o HeapCheckerDebug.exe HeapChecker.cpp Heap.cpp HashTable.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
