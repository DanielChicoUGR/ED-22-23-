#include "letters_set.h"

#include <string>
#include <cctype>

LetterInfo &LetterSet::operator[](const char &ket) {

    if(letters.find(ket) != letters.end()) return letters[ket];

    LetterInfo aux={0,0};

    return aux;
}


LetterSet& LetterSet::operator=(const LetterSet &other)=default; //Al ser un operador de asignación trivial, el compilador recomineda usar el default.
//LetterSet& LetterSet::operator=(const LetterSet &other) {
//    letters=other.letters;
//
//    return *this;
//}


int LetterSet::getScore(const std::string &palabra) const {
    int score=0;
    for(auto letra:palabra) {
        score+=letters.at(letra).score;
    }
    return score;
}

std::istream &operator>>(std::istream &is, LetterSet &cl) {

    std::string primera_linea;
    std::getline(is, primera_linea);
//    is>>primera_linea;
    char letra;
    int catidad,puntos;
    while(is){
        is>>letra>>catidad>>puntos;
        letra=std::toupper(letra);
        cl.letters.insert({letra, {catidad, puntos}});
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const LetterSet &cl) {
    os << "Letra Cantidad Puntos\n";

    for(auto par:cl.letters){
        os<<par.first<<"\t"<<par.second<<"\n";
    }


    return os;
}

