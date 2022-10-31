#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <set>
#include <string>
#include <vector>
#include <istream>

/**
 * @brief TDA Dictionary
 * @details Almacena las palabras de un fichero de texto y permite iterar sobre ellas
 *
 */

class Dictionary{
private:
    std::set<std::string> words;
public:
    /**
     * @brief Constructor por defecto
     * Crea un \e Dictionary vacio
     */
    Dictionary()=default;

    /**
     * @brief Constructor de copia
     * CRea un \e Dictionary con el mismo contenido que el pasado por parametros
     * @param d \e Dictionary que se quiere copiar.
     */
    Dictionary(const Dictionary& d) : words(d.words){};

    /**
     * @brief Comprueba si una palabra existe en el diccionario o no.
     *  Este metodo comprueba sui una determinada palabra se encuentra o no en el \e Diccionary
     * @param val La palabra que se quiere buscar
     * @return Booleano indicando si la palabra se encuentra o no
     */
    inline bool exists(const std::string& val){ return words.contains(val) ; }

    /**
     *  @brief Inserta una palabra en el \e Dictionary
     * @param val PAlabra a insertar
     * @return Booleano que indica si se ha insertado con exito. Una inserccion tiene exito si la palabra no existia en el \e Dictionary
     */

    inline bool insert(const std::string& val){ return words.insert(val).second;}

    /**
     * @brief Elimina una palabra del diccionario
     * @param val Palabra a borrar del diccionario
     * @return Booleano que indica si al palabra se ha borrado del diccionario
     */
    inline bool erase(const std::string& val){ return words.erase(val);}
    /**
     * @brief Limpia el \e Dictionary
     * Elimina todas las palabras del diccionario.
     */
    inline void clear(){words.clear();}
    /**
     * @brief Comprueba si el diccionario esta vacio
     * @return Boolano que indica si esta vacio, false en caso de que no
     */
    inline bool empty(){return words.empty();}

    /**
     * @brief Tamaño del diccionario
     * @return Numero de palabras almacenadas en el diccionario
     */
    inline unsigned int size(){return words.size();}

    /**
     * @brief Incica el numero de apariciones de una letra
     * @param c Letra a buscar
     * @return Un entero indicando el numero de apariciones
     */
     unsigned long int getOccurences(const char c);

     /**
      * @brief Indica el numero de apariciones de una letra
      * @return Entero indicando la cantidad de apariciones
      */
    unsigned long int getTotalLetters();

    /**
     * @brief DEvuelve las palabras de un diccionario de una longitud dada
     * @param length Longitud de las palabras buscadas
     * @return Vector de palabras con la longitud deseada.
     */
    std::vector<std::string> wordsOfLenght(const int length);

    /**
     * @brief Sobrecarga operador de entrada
     * @param is Operador sobre el que se extrae la información
     * @param a Diccionario a escribir
     * @return Referencia al flujo de entrada
     */
    friend std::istream& operator>>(std::istream&is, Dictionary& a);
};

#endif
