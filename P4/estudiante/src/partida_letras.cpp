//
// Created by daniel on 12/7/22.
//

#include "solver.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    if(argc != 5){
        cerr << "Los parametros son: " << endl;
        cerr << "1.- El fichero con el diccionario" << endl;
        cerr << "2.- El fichero con las letras y su puntuacion" << endl;
        cerr << "3.- Modo de Juego: L -> longitud, P-> puntuacion" << endl;
        cerr << "4.- Cantidad de letras para la partida" << endl;

        exit (1);
    }


    ifstream f_diccionario(argv[1]);

    if(!f_diccionario){
        cerr << "No puedo abrir el fichero " << argv[1] << endl;
        exit (2);
    }

    ifstream f_letras(argv[2]);

    if(!f_letras){
        cerr << "No puedo abrir el fichero " << argv[2] << endl;
        exit (2);
    }

    std::cout<<"Fichero diccionario: "<<argv[1]<<"\nFichero Letras: "<<argv[2]<<std::endl;

    char modo_j=argv[3][0];
    modo_j=char(tolower(modo_j));

    if(modo_j!='l' and modo_j!='p'){
        cerr << "No especifico bien el modo de juego. ust especifico: " << argv[3] << endl;
        cerr << "Modo de Juego: L -> longitud, P-> puntuacion" << endl;
        exit (3);
    }

    int n_letras=atoi(argv[4]);

    if(n_letras<=0){
        cerr << "El numero de letras ha de ser positivo. ust expecifico: " << argv[4] << endl;
        exit (4);
    }
//    srand(time(NULL));

    Dictionary diccionario;
    f_diccionario >> diccionario;

    LetterSet letterset;
    f_letras>>letterset;

    Solver s(diccionario,letterset);

    LettersBag bag(letterset);

//    auto letras_partida=bag.extractLetters(n_letras);


    auto letras_partida={};

    auto sol=s.getSolutions(letras_partida, modo_j == 'p');

    std::cout<<"LETRAS DISPONIBLES:\n";
    for(auto l:letras_partida)
        std::cout<<char(toupper(l))<<" ";

    std::cout<<"\nSOLUCIONES\n";

    
    for(auto s:sol.first)
        std::cout<<s<<std::endl;
    std::cout<<"PUNTUACION\n"<<sol.second<<std::endl;

    return 0;
}