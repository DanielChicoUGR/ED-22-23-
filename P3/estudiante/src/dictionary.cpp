#include "dictionary.h"

std::vector<std::string> Dictionary::wordsOfLenght(const int length) {
    std::vector<std::string> ret;

    for(const auto palabra:words)
        if(palabra.size()==length) ret.push_back(palabra);

    return ret;
}

unsigned long int Dictionary::getTotalLetters() {
    unsigned long int total = 0;
    for(const auto& palabra:words){
        total += palabra.size();
    }
    return total;
}

unsigned long int Dictionary::getOccurences(const char c) {
    unsigned long int total = 0;
    for(const auto& palabra:words)
        total+= std::count(palabra.begin(), palabra.end(),c);
    return total;
}

std::istream& operator>>(std::istream &is, Dictionary& a) {
    std::string aux;
    while (std::getline(is, aux))
        a.insert(aux);

    return is;
}
