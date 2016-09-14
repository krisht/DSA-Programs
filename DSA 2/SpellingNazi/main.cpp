#include "SpellingNazi.h"

using namespace std;

int main() {
    SpellingNazi *spellchecker = new SpellingNazi();
    spellchecker -> checkFile();
    delete(spellchecker);
    return 0;
}