//
// Created by daniel on 10/26/22.
//
#include <iostream>
#include <fstream>
#include "dictionary.h"
#include "letters_set.h"

std::ostream& operator<< (std::ostream& os, const std::vector<std::string>& values){
    for(auto& value : values) os<<value<<"\n";
}

int main(int argc, char **argv) {

    if (argc < 3) {
        std::cerr << "hay que introducir la ruta del archivo del diccionario y de las letras" << std::endl;
        exit(1);
    }

    std::ifstream dic(argv[1]);

    std::ifstream letras(argv[2]);

    Dictionary diccionario;

    LetterSet letters;

    dic>>diccionario;

    letras>>letters;




}