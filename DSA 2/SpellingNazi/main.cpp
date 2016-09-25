#include "SpellingNazi.h"

using namespace std;

int main() {
    SpellingNazi *speller = new SpellingNazi();
    speller->checkFile(); //Runs program
    delete (speller); //Cleans up after program execution
    return 0;
}