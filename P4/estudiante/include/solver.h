//
// Created by daniel on 12/7/22.
//

#ifndef P04_JUEGO_LETRAS_SOLVER_H
#define P04_JUEGO_LETRAS_SOLVER_H

#include "dictionary.h"
#include "letters_set.h"
#include "letters_bag.h"



class Solver {
private:
    Dictionary dict;
    LetterSet ls;

public:

    /**
     * @brief Constructor por defecto de la clase solver.
     */
    Solver()=default;

    /**
     * @brief Constructor con parámetros.
     *  Crea un Solver asociado a un determinado diccionario y un letterset
     * @param dic Diccionario sobre el que se buscarán las palabras
     * @param letter Conjunto de letras que buscar junto conla puntuacion que tiene cada una
     */
    Solver(const Dictionary &dic,const LetterSet &letter):dict(dic),ls(letter){}

    /**
     * Constructor de copia por defecto
     * @param other Solver a copiar
     */
    Solver(Solver& other);


    /**
     * @brief construye el vector de soluciones a partir de las letras de una partida
     *
     *      Dado un conjunto de letras posibles para crear una solución, y el modo de juego con el que se juega la partida,
     *      se construye un vector con las mejores soluciones encontradas en función del tipo de juego planteado
     *
     * @param avalible_letters  Vector de letras disponibles para la partida
     * @param score_game Bool indicando el tipo de partida. True indica que se juega a puntuación. False se juega a palabra mas larga.
     * @return par <vector<string>,int>, con el vector de palabras se constituyen las mejores soluciones (puede haber empate) y la puntuación que obtienen.
     *
     */
    std::pair<vector<string>,int> getSolutions(const std::vector<char>&avalible_letters,bool score_game)const;


	std::pair<vector<string>,int> getSolucioneseficiente(const std::vector<char> &avalible_letters, bool score_game) const;
private:
    /**
     * devuelve una solución para el modo de juego basado en la puntuación de las palabras
     * @param avalible_letters Conjunto de letras sobre las que formar una solución
     * @return par <vector<string>,int>, con el vector de palabras se constituyen las mejores soluciones (puede haber empate) y la puntuación que obtienen.
     */
    std::pair<vector<string>,int> score_puntuacion(const std::vector<char>&avalible_letters)const;

    /**
     * devuelve una solución para el modo de juego basado en la longitud de las palabras
     * @param avalible_letters Conjunto de letras sobre las que formar una solución
     * @return par <vector<string>,int>, con el vector de palabras se constituyen las mejores soluciones (puede haber empate) y la puntuación que obtienen.
     */

    std::pair<vector<string>,int> score_longitud(const std::vector<char>&avalible_letters)const;


	/**
     * devuelve una solución para el modo de juego basado en la puntuación de las palabras
     * @param avalible_letters Conjunto de letras sobre las que formar una solución
     * @return par <vector<string>,int>, con el vector de palabras se constituyen las mejores soluciones (puede haber empate) y la puntuación que obtienen.
     */
	std::pair<vector<string>,int> score_puntuacion_eficiente(const std::vector<char>&avalible_letters)const;

	/**
	 * devuelve una solución para el modo de juego basado en la longitud de las palabras
	 * @param avalible_letters Conjunto de letras sobre las que formar una solución
	 * @return par <vector<string>,int>, con el vector de palabras se constituyen las mejores soluciones (puede haber empate) y la puntuación que obtienen.
	 */

	std::pair<vector<string>,int> score_longitud_eficiente(const std::vector<char>&avalible_letters)const;


    /**
     * @brief Comprueba si la palabra se puede construir a partir del conjunto de letras pasado por referencia
     * @param avalible_letters
     * @param palabra
     * @return
     */
    static bool palabra_construible(std::vector<char> avalible_letters,const string &palabra);

    static void comprueba_palabra(std::pair<vector<string>, int> &solucion,const std::vector<char>&avalible_letters,const string &palabra, int score);

};


#endif //P04_JUEGO_LETRAS_SOLVER_H
