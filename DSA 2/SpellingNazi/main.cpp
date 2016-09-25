#include "SpellingNazi.h"

using namespace std;

int main(){
    SpellingNazi *speller = new SpellingNazi();
    speller->checkFile();
    delete(speller);
    return 0;
}