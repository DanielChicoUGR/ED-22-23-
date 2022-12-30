//
// Created by daniel on 12/7/22.
//

#include "solver.h"
#include <iostream>
#include <fstream>
#include <algorithm>

int main(int argc, char *argv[])
{
  if(argc != 5){
	std::cerr << "Los parametros son: " << std::endl;
	std::cerr << "1.- El fichero con el diccionario" << std::endl;
	std::cerr << "2.- El fichero con las letras y su puntuacion" << std::endl;
	std::cerr << "3.- Modo de Juego: L -> longitud, P-> puntuacion" << std::endl;
	std::cerr << "4.- Cantidad de letras para la partida" << std::endl;

	exit (1);
  }


  ifstream f_diccionario(argv[1]);

  if(!f_diccionario){
	std::cerr << "No puedo abrir el fichero " << argv[1] << std::endl;
	exit (2);
  }

  ifstream f_letras(argv[2]);

  if(!f_letras){
	std::cerr << "No puedo abrir el fichero " << argv[2] << std::endl;
	exit (2);
  }

//    std::cout<<"Fichero diccionario: "<<argv[1]<<"\nFichero Letras: "<<argv[2]<<std::endl;

  char modo_j=argv[3][0];
  modo_j=char(tolower(modo_j));

  if(modo_j!='l' and modo_j!='p'){
	std::cerr << "No especifico bien el modo de juego. ust especifico: " << argv[3] << std::endl;
	std::cerr << "Modo de Juego: L -> longitud, P-> puntuacion" << endl;
	exit (3);
  }

  int n_letras=atoi(argv[4]);

  if(n_letras<=0){
	std::cerr << "El numero de letras ha de ser positivo. ust expecifico: " << argv[4] << std::endl;
	exit (4);
  }
  srand(time(NULL));

  Dictionary diccionario;
  f_diccionario >> diccionario;

  LetterSet letterset;
  f_letras>>letterset;

  Solver s(diccionario,letterset);

  LettersBag bag(letterset);



#ifdef NDEBUG
  std::vector<char> letras_partida={'o' ,'c' ,'f' ,'t' ,'a' ,'d' ,'s' ,'v' ,'e' };
//  	std::vector<char> letras_partida={'c' ,'s' ,'u' ,'c' ,'y' ,'e' ,'s' ,'e' ,'i'};

#else

      auto letras_partida=bag.extractLetters(n_letras);
#endif





  std::for_each(letras_partida.begin(),letras_partida.end(),[](char & x){ if(x<='Z')  x= std::tolower(x);});

  auto sol=s.getSolucioneseficiente(letras_partida, modo_j == 'p');

  std::cout<<"LETRAS DISPONIBLES:\n";
  for(auto l:letras_partida)
	std::cout<<l<<" ";

  std::cout<<"\nSOLUCIONES:\n";


  for(auto solucion:sol.first)
	std::cout<<solucion<<std::endl;
  std::cout<<"PUNTUACION:\n"<<sol.second<<std::endl;

  return 0;
}