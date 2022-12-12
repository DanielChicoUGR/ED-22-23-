#include "letters_set.h"

#include <string>
#include <cctype>

LetterInfo &LetterSet::operator[](const char &ket) {

    if(letters.find(ket) == letters.end()) letters.insert({ket,{0,0}});

    return letters[ket];
}


LetterSet& LetterSet::operator=(const LetterSet &other)=default; //Al ser un operador de asignación trivial, el compilador recomineda usar el default.



int LetterSet::getScore(const std::string &palabra) const {
    auto p=0;
    for(auto item:palabra) {
        if(letters.find(item)!=letters.end())
            p+=letters.at(item).score;
    }
    return p;
}

std::istream &operator>>(std::istream &is, LetterSet &cl) {

    std::string primera_linea;
    std::getline(is, primera_linea,'\n');
//    is>>primera_linea;
    char letra;
    int catidad,puntos;
    while(is){
        is>>letra>>catidad>>puntos;
        letra=std::tolower(letra);
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

