#include "SpellingNazi.h"

using namespace std;

int main() {
    SpellingNazi *spellchecker = new SpellingNazi(); //Spell checker declaration
    spellchecker -> checkFile(); //checks file
    delete(spellchecker); //cleans up memory afterwards
    return 0;
}   