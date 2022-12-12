#ifndef __LETTERS_BAG_H__
#define __LETTERS_BAG_H__

#include "bag.h"
#include "letters_set.h"

/**
 * @brief TDA LettersBag
 *
 * Este TDA almacena un conjunto de chars utilizado en el juego de letras.
 * La estructura de datos subyacente es una lista de chars.
 */

class LettersBag{
private:
    Bag<char> letters;


public:

    /**
     * @brief Constructor por defecto.
     */
    LettersBag()=default;

    /**
     * @brief Constructor dado un \e LetterSet
     * Dado un \e LetterSet como argumento, este constructor debe rellenar la LetterBag con las letras que contiene el LetterSet,
     * introduciendo cada letra el número de veces indicado por el campo LetterInfo::repeticiones.
     * @param letterSet TDA \e LetterSet a parsear
     */
    explicit LettersBag( LetterSet & letterSet);

    /**
     * @brief Constructor de copia
     * @param other \e Letterbag a copiar.
     */
    LettersBag(const LettersBag & other)=default;

    /**
     * @brief Introduce una letra en la bolsa
     * @param l Letra a añadir en la \e LetterBag
     */
    inline void insertLetter(const char &l){    letters.add(l);    }

    /**
     * @brief Extrae una letra aleatoria de la bolsa.
     * Extrae una letra aleatoria de la bolsa, eliminandola del conjunto.
     * @return char representa la letra extraida.
     */
    char extractLetter();


    /**
     * @brief Extrae un conjunto de letras.
     * Extrae un conjunto de letras de \e LetterBag, eliminandolas del conjunto
     * @param num Numero de letras a extraer
     * @return Lista con las letras extraidas
     */
    std::vector<char>extractLetters(const unsigned int &num);

    /**
     * @brief Vacia el LetterBag
     * Elimina todo el contenido de \e LetterBad
     */

    inline void clear(){    letters.clear();    }

    /**
     * @brief Tamaño de la bolsa
     * @return DEvuelve la cantidad de letras almacenadas en la bolsa.
     */
    inline size_t size() {    return letters.size();  }

    inline LettersBag& operator=(const LettersBag& other){
        letters=other.letters;
        return *this;
    }

};


#endif
