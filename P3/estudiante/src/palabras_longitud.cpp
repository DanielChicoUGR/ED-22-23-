//
// Created by daniel on 10/25/22.
//
#include <iostream>
#include <fstream>
#include "dictionary.h"

std::ostream& operator<< (std::ostream& os, const std::vector<std::string>& values){
    for(auto& value : values) os<<value<<"\n";
}

int main(int argc, char **argv){

    if(argc < 3){
        std::cerr << "hay que introducir la ruta del archivo y el tamano de las palabras"<<std::endl;
        exit(1);
    }

    std::ifstream fich(argv[1]);

    auto length =atoi(argv[2]);

    if(!fich.is_open()){
        std::cerr << "Error: Couldn't open file";
        exit(2);
    }
    Dictionary palabras;
    fich >> palabras;

    auto ret=palabras.wordsOfLenght(length);
    std::cout << ret << std::endl;





    return 0;
}