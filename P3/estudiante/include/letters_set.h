#ifndef __LETTER_SET_H__
#define __LETTER_SET_H__
#include <map>
#include <iostream>
/**
 * @brief TDA LetterInfo
 *
 * Contiene información sobre un determinado carácter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra
 */

struct LetterInfo{
    int repeticiones;
    int score;

    /**
     * @brief Sobrecarga del operador de inserccion de flujo
     * @param os Flujo de Salida
     * @param info Informacion a incluir en el flujo
     * @return Flujo de Salida
     */
    friend inline std::ostream &operator<<(std::ostream &os, const LetterInfo &info) {
        os << "repeticiones: " << info.repeticiones << "\tscore: " << info.score;
        return os;
    }


};


/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra
 */

class LetterSet{
private:
    std::map<char, LetterInfo> letters;


public:
    /**
     * @brief Constructor por defecto
     *
     * Crea un \e LetterSet vacio
     *
     */
    inline LetterSet(){ letters= std::map<char, LetterInfo> (); }

    /**
     * @brief Constructor de copia
     * @param other LetterSet a copiar
     */
    inline LetterSet(const LetterSet& other){ letters=other.letters; }

    /**
     * @brief Inserta un elemento en el LetterSet
     * @param val Pareja de letra y LetterInfo asociada
     * @return Boolano que indica si la letra se ha insertado correctamente. No se inserta correctamente si ya existe en el LetterSet.
     */
    inline bool insert(std::pair<char,LetterInfo> &val){ return letters.insert(val).second; }

    /**
     * @brief Elimina un caracter del LetterSet
     * @param key Letra a eliminar del set
     * @return Booleano que indica si se ha borrado correctamente de LetterSet.
     */
    inline bool erase(const char &key){ return letters.erase(key);}

    /**
     * @brief Limpia el contenido de LetterSet
     *  Borra el contenido de LetterSet
     */
    inline void clear(){ letters.clear();}

    /**
     * @brief Consulta si el LetterSet esta vacio
     * @return True si esta vacio, falso en caso contrario
     */
    inline bool empty() const { return letters.empty(); }

    /**
     * @brief Devuelve la cantidad de letras almacenadas en el LetterSet
     * @return
     */
    inline unsigned int size() const { return letters.size(); }

    /**
     * @brief Calcula la puntuación de una palabra dada
     * @param palabra Palabra a la que calcular la puntuación.
     * @return Puntuación de la palabra
     */
    int getScore(const std::string &palabra) const;

    /**
     * @brief Sobrecarga del operador de asignación
     * @param other Letterset a copiar
     * @return Referencia a this para poder encadenar el operador
     */
    LetterSet& operator=(const LetterSet& other);

    /**
     * @brief Sobrecarga del operador de consulta
     * Permite acceder a los elementos del map que hay en nuestra clase
     * @param ket Caracter a consultar
     * @return Estructura del tipo \e LetterInfo con la información del caracter consultado. Numero de repeticiones y puntuación.
     *
     */
    LetterInfo &operator[](const char &ket);

    /**
     * @brief Sobrecarga del operador de salida
     * @param os Flujo de Salida donde escribir el LetterSet
     * @param cl LetterSet que se escribe
     *
     */
    friend std::ostream &operator<<(std::ostream &os, LetterSet const &cl);

    /**
     * @brief Sobrecarga del operador de entrada
     * @param is Flujo de entrada del que leer el LetterSet
     * @param cl LetterSet que se almacena la infiormacion leida
     *
     */
    friend std::istream &operator>>(std::istream &is, LetterSet &cl);

};
#endif
