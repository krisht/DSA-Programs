spell.exe: SpellingNazi.o HashTable.o main.cpp
	g++ -O3 -std=c++11 -o spell.exe main.cpp SpellingNazi.o HashTable.o 

SpellingNazi.o: SpellingNazi.cpp SpellingNazi.h HashTable.h
	g++ -O3 -std=c++11 -c SpellingNazi.cpp

HashTable.o: HashTable.cpp HashTable.h
	g++ -O3 -std=c++11 -c HashTable.cpp

debug:
	g++ -std=c++11 -g -o spellDebug.exe main.cpp SpellingNazi.cpp HashTable.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
