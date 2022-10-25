//
// Created by daniel on 10/25/22.
//
#include <letters_set.h>
#include <iostream>
#include <fstream>


//using namespace std;


int main(int argc, char **argv){
    LetterSet letras;

    std::ifstream fich("../data/letras.txt");

    if(!fich.is_open()){
        std::cerr << "Error: Couldn't open file";
        exit(1);
    }

    fich >> letras;

    std::cout << letras << std::endl;


    return 0;
}