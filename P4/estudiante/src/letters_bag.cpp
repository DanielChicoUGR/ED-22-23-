#include "letters_bag.h"


//LettersBag::LettersBag(const LetterSet &letterSet) {
//    clear();
//    for(auto it:letterSet){
//
//    }
//}



//TODO: Arreglar para que el LetterSet sea CTE


LettersBag::LettersBag(LetterSet &letterSet) {
    clear();
    for(auto it:letterSet){
        char letra=it.first;
        for(auto i=0;i<it.second.repeticiones;i++)
            letters.add(letra);
    }
}

std::vector<char> LettersBag::extractLetters(const unsigned int &num) {
    std::vector<char>ret;

    for(auto i=0;i<num;i++)
        ret.push_back(letters.get());

    return ret;
}

char LettersBag::extractLetter() { return letters.get();  }


