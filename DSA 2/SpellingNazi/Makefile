SpellingNazi: SpellingNazi.o HashTable.o main.cpp
	g++ -O3 -std=c++11 -o SpellingNazi.exe main.cpp SpellingNazi.o HashTable.o 

SpellingNazi.o: SpellingNazi.cpp SpellingNazi.h HashTable.h
	g++ -O3 -std=c++11 -c SpellingNazi.cpp

HashTable.o: HashTable.cpp HashTable.h
	g++ -O3 -std=c++11 -c HashTable.cpp

debug:
	g++ -std=c++11 -g -o SpellingNaziDebug.exe main.cpp SpellingNazi.cpp HashTable.cpp

clean:
	rm -f *.exe *.o *.stackdump *~