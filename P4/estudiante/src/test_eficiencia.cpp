//
// Created by daniel on 12/29/22.
//
#include "solver.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <omp.h>


#define N_ITERACIONES_PRUEBA 20
#define MIN_LETRAS 3
#define MAX_LETRAS 20

 std::ostream &operator<<(std::ostream &os, const std::pair<int,double> &p  ){
//   os<<p.first<<' '<<p.second<<';';
    os<<p.second<<';';
   return os;
 }

    int main(int argc, char *argv[])
{
  if(argc != 5){
    std::cerr << "Los parametros son: " << std::endl;
    std::cerr << "1.- El fichero con el diccionario" << std::endl;
    std::cerr << "2.- El fichero con las letras y su puntuacion" << std::endl;
    std::cerr << "3.- Modo de Juego: L -> longitud, P-> puntuacion" << std::endl;
    std::cerr << "4.- (0) Solucion eficiente o (1) solución normal" << std::endl;

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

  const char modo_j=tolower(argv[3][0]);
//  modo_j=char(tolower(modo_j));

  if(modo_j!='l' and modo_j!='p'){
    std::cerr << "No especifico bien el modo de juego. ust especifico: " << argv[3] << std::endl;
    std::cerr << "Modo de Juego: L -> longitud, P-> puntuacion" << endl;
    exit (3);
  }

  const int eficiencia=atoi(argv[4]);

  if(eficiencia!=0 and eficiencia!=1){
    std::cerr << "(0) Solucion eficiente o (1) solución normal. ust especifico: " << argv[4] << std::endl;
    exit (4);
  }
  srand(time(nullptr));

  Dictionary diccionario;
  f_diccionario >> diccionario;
  f_diccionario.close();

  LetterSet letterset;
  f_letras>>letterset;
  f_letras.close();

   const Solver s(diccionario,letterset);

   LettersBag bag(letterset);


    std::map<int,double> datos{};



    #pragma omp parallel for  default (none) shared(modo_j,eficiencia,datos,s) firstprivate(bag)

  for(int j=MIN_LETRAS;j<=MAX_LETRAS;j++) {

    auto letras_partida = bag.extractLetters(j);

    std::chrono::duration<double, std::micro> t_aux{};

    for (int i = 0; i < N_ITERACIONES_PRUEBA; i++) {
        std::chrono::duration<double, std::micro> t{};

        if (eficiencia==0) {
          auto t1 = std::chrono::high_resolution_clock::now();
          auto sol = s.getSolucioneseficiente(letras_partida, modo_j == 'p');
          auto t2 = std::chrono::high_resolution_clock ::now();
          t=t2-t1;
        } else {
          auto t1 = std::chrono::high_resolution_clock::now();
          auto sol = s.getSolutions(letras_partida, modo_j == 'p');
          auto t2 = std::chrono::high_resolution_clock ::now();
          t=t2-t1;
        }

        t_aux += t;

      }

      auto tiempo=t_aux.count()/N_ITERACIONES_PRUEBA;
      #pragma omp critical
        datos.insert({j,tiempo});

  }

    for(const auto&dato:datos )
      std::cout<<dato;

    return 0;
}