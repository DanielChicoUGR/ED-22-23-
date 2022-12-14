//
// Created by daniel on 12/7/22.
//

#include "solver.h"
#include <algorithm>



std::pair<vector<string>, int> Solver::getSolutions(const std::vector<char> avalible_letters, bool score_game) const{
    std::pair<vector<string>, int> ret;
    if(score_game)
         ret=score_puntuacion(avalible_letters);
    else
         ret=score_longitud(avalible_letters);




    return ret;
}


std::pair<vector<string>, int> Solver::score_puntuacion(const std::vector<char> avalible_letters)const {
    std::pair<vector<string>, int> ret={{""},0};

    for(auto palabra:dict){

        //Juego a puntuacion
        auto score=ls.getScore(palabra);
        comprueba_palabra(ret,avalible_letters,palabra,score);

    }


    return ret;
}

std::pair<vector<string>, int> Solver::score_longitud(const std::vector<char> avalible_letters) const{
    std::pair<vector<string>, int> ret;
    ret.first={};
    ret.second=-1;
    for(auto palabra:dict){
        //Juego a puntuacion
        auto score=palabra.length();
        comprueba_palabra(ret,avalible_letters,palabra,score);
    }


    return ret;
}

 bool Solver::palabra_construible( std::vector<char> avalible_letters,const string& palabra) {



    //Si la palabra es mas larga que la cantidad de letras paso y no se puede construir
    if(palabra.size()>avalible_letters.size() or palabra=="")
        return false;


    for (auto letra:palabra){
        std::vector<char>::iterator existe=std::find(avalible_letters.begin(), avalible_letters.end(), letra);

        //Con la primera letra que no se encuentre en las letras disponibles se sale de la función
        if (existe==end(avalible_letters))
            return false;

        avalible_letters.erase(existe);

    }
    return true;
}

void Solver::comprueba_palabra(pair<vector<string>, int> &solucion, const vector<char> &avalible_letters,
                               const string &palabra,int score) {

    if(palabra_construible(avalible_letters,palabra))
        if( score>solucion.second){
            solucion.first.clear();
            solucion.first.push_back(palabra);
            solucion.second =score;
        }else if(score==solucion.second)
            solucion.first.push_back(palabra);


}

std::pair<vector<string>, int> Solver::getSolucioneseficiente(const std::vector<char> avalible_letters, bool score_game) const {
  	std::pair<vector<string>, int> ret;
  	if(score_game)
		ret=score_puntuacion_eficiente(avalible_letters);
  	else
		ret=score_longitud_eficiente(avalible_letters);
  	return ret;
}

std::pair<vector<string>, int> Solver::score_longitud_eficiente(const std::vector<char> &avalible_letters) const {
  std::pair<vector<string>, int> ret={{""},0};

  for(auto it=dict.possible_words_begin(const_cast<vector<char> &>(avalible_letters));it!=dict.possible_words_end();++it){
	//Juego a puntuacion
	auto score=(*it).size();
	if( score>ret.second){
	  ret.first.clear();
	  ret.first.push_back(*it);
	  ret.second =score;
	}else if(score==ret.second)
	  ret.first.push_back(*it);
  }

  return ret;
}

std::pair<vector<string>, int> Solver::score_puntuacion_eficiente(const std::vector<char> &avalible_letters) const {
  	std::pair<vector<string>, int> ret={{""},0};

  	for(auto it=dict.possible_words_begin(const_cast<vector<char> &>(avalible_letters));it!=dict.possible_words_end();++it){
		//Juego a puntuacion
		auto score=ls.getScore(*it);
	  	if( score>ret.second){
			ret.first.clear();
			ret.first.push_back(*it);
			ret.second =score;
	  	}else if(score==ret.second)
			ret.first.push_back(*it);
  	}

  	return ret;
}


