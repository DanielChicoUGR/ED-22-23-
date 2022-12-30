//
// Created by fluque1995 on 8/9/21.
//

#ifndef TREE_DICTIONARY_HPP
#define TREE_DICTIONARY_HPP

#include "tree.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

class Dictionary {
private:

/**
     * @brief Struct to represent a character inside the tree.
     *
     * The struct contains information about the character it that node, and
     * information marking if a valid word of the dictionary finishes in
     * that character
     */
    struct char_info {
        char character;
        bool valid_word;

        /**
         * Default constructor
         */
        inline char_info() : character(0), valid_word(false) {}

        /**
         * @brief Parameters constructor
         *
         * @param character Character to be inserted
         * @param valid Marker for word validity
         */
        inline char_info(char character, bool valid = false) : character(character), valid_word(valid) {}

        inline bool operator==(const char_info &rhs)const {
          return this->character == rhs.character && this->valid_word == rhs.valid_word;
        }

        inline bool operator!=(const char_info &rhs) const{ return !(*this == rhs); }

        inline bool operator*() const { return this->character; }

        inline friend std::ostream &operator<<(std::ostream &os, const char_info &other) {
          os << other.character << (other.valid_word ? "✓" : "×");
          return os;
        }
    };

    tree<char_info> words;
    int total_words;
    typedef tree<char_info>::node node;

    /**
     * @brief Find the lower bound of a character among the children of the current node
     *
     * If the character exists among the children of the current node, that node is returned. If not,
     * the returned node is the one with the biggest character (in terms of alphabetical order) smaller
     * than the searched one
     *
     * @param character Character to be found
     * @param current Reference node, the one whose children are going to be explored
     * @return Lower bound node for the seeked character
     */
    node findLowerBoundChildNode(char character, node current);

    /**
     * @brief Insert character as children of the current node
     *
     * This method tries to insert a new character in the tree, as a child of the current node.
     * If there already exists a node with that character, instead of inserting a new node, the
     * already existing node with the character is returned
     *
     * @param character Character to be inserted
     * @param current Reference node, the one that will be parent of the new inserted node
     * @return Node corresponding to the inserted character
     */
    node insertCharacter(char character, node current);

    int getOccurrences(node curr_node, char c);

    std::pair<int, int> getTotalUsages(node curr_node, char c);

public:

    /**
     * @brief Constructor por defecto
     *
     * Crea un Dictionary vacío
     */
    Dictionary();

    /**
     * @brief Constructor de copia
     *
     * Crea un Dictionary con el mismo contenido que el que se pasa como argumento
     *
     * @param other Dictionary que se quiere copiar
     */
    Dictionary(const Dictionary &other);

    /**
     * @brief Destructor
     *
     * Limpia todos los elementos del Dictionary antes de borrarlo
     */
    ~Dictionary();

    /**
     *  \brief Limpia el Dictionary
     *
     *  Elimina todas las palabras contenidas en el conjunto
     */
    void clear() { this->words.clear(); this->total_words = 0; }

    /**
     * @brief Tamaño del diccionario
     *
     * @return Número de palabras guardadas en el diccionario
     */
    unsigned int size() const { return this->total_words; }

    /**
     * @brief Comprueba si el diccionario está vacio.
     * @return true si el diccionario está vacío, false en caso contrario
     */
    bool empty() const { return this->total_words == 0; }

    /**
     * @brief Indica si una palabra esta en el diccionario o no.
     *
     * Este método comprueba si una determinada palabra se encuentra o no en el dicccionario
     *
     * @param palabra: la palabra que se quiere buscar.
     * @return Booleano indicando si la palabra existe o no en el diccionario
     */
    bool exists(const string &val);

    /**
     * @brief Inserta una palabra en el diccionario
     *
     * @param val palaba a insertar en el diccionario
     * @return Booleano que indica si la inserción ha tenido éxito. Una palabra se inserta
     * con éxito si no existía previamente en el diccionario
     */
    bool insert(const string &val);

    /**
     * @brief Elimina una palabra del diccionario
     *
     * @param val Palabra a borrar del diccionario
     *
     * @return Booleano que indica si la palabra se ha borrado del diccionario
     */
    bool erase(const string &val);

    /**
     * @brief Sobrecarga del operador de asignación
     */
    Dictionary &operator=(const Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de entrada
     *
     * Permite leer las palabras de un fichero de texto e introducirlas en el
     * diccionario
     *
     * @param is Flujo de entrada
     * @param dic Diccionario a rellenar
     * @return Flujo de entrada para poder encadenar el operador
     */
    friend istream &operator>>(istream &is, Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de salida
     *
     * Permite imprimir el diccionario completo a un flujo de salida
     *
     * @param os Flujo de salida, donde imprimir el diccionario
     * @param dic Diccionario a imprimir
     * @return Flujo de salida, para poder encadenar el operador
     */
    friend ostream &operator<<(ostream &os, const Dictionary &dic);

    //////////////////////////////////////////////// Recursive functions ///////////////////////////////////////////////

    int getOccurrences(const char c);

    int getTotalUsages(const char c);

    ///////////////////////////////////////////////////// Iterator ////////////////////////////////////////////////////

    class iterator {
    private:
//        iterator(iterator &other);

        std::string curr_word;
        tree<char_info>::const_preorder_iterator iter;

    public:

        /**
         * @brief Constructor por defecto de la clase iterador.
         */
         iterator();

         /**
          * @brief constructor por parametros.
          * @param iter Iterador de un \e TDA \e Tree parametrizado con TDA char_info
          */
         explicit iterator( tree<char_info>::const_preorder_iterator &iter);

         /**
          * @brief Construtor de copia
          * @param other Iterador a copiar
          */
         iterator(iterator const &other);

         /**
          * @brief Operador de seleccion
          * @return String a la palabra a la que el iterador apunta.
          */
        std::string operator*();

        /**
         * @brief Operador de incremento. Modifica su estado interno para que apunte a la siguiente palabra en el diccionario
         * @return Referencia a si mismo.
         */
        iterator &operator++();
        /**
         * @brief Operador de igualdad. Comprueba que los iteradores apuntan a la misma "palabra"
         * (no es asi exactamente pero no deberia de haber mas info sobre la implementación no?)
         * @param other Iterador a comparar
         * @return True si son iguales, false en otro caso
         */
        bool operator==(const iterator &other);

        /**
         * @brief Operador de desigualdad. Comprueba que los iteradores apuntan a palabras distintas
         * @param other Iterador a comparar
         * @return True si NO son iguales, false en otro caso
         */
        bool operator!=(const iterator &other);

        /**
         * @brief Operador de asignación, copia el contenido de \e other en \e this
         * @param other Iterador a copiar
         * @return Referencia a \e this
         */
        iterator &operator=(const iterator &other);

//        iterator(iterator &other);

        friend class Dictionary;
    };

    /**
     *
     * @return Iterador al inicio del diccionario con los valores internos inicializados para dicho caso
     */
    iterator begin() const;

    /**
     *
     * @return Iterador al final del diccionario con los valores internos inicializados para dicho caso.
     */
    iterator end() const;

    ///////////////////////////////////////////////// Letters Iterator /////////////////////////////////////////////////

    class possible_words_iterator {
    public:
        /**
         * @brief Constructor por defecto
         */
        possible_words_iterator();

        /**
         * @brief Constructor por parametros
         * @param current_node Nodo perteneciente a un Tree sober el que se quiere empezar a iterar
         * @param available_letters Conjunto de letras sobre las que se quiere trabajar
         */
        possible_words_iterator(node current_node, const vector<char>& available_letters);

        /**
         * @brief Constructor de copia
         * @param other Iterador a copiar
         */
        possible_words_iterator(const possible_words_iterator &other);

        /**
         * @brief Operador de asignación. Copia el contenido de \e other en \e this
         * @param other Iterador a copiar
         * @return Referencia a this
         */
        possible_words_iterator &operator=(const possible_words_iterator &other);
        /**
         * @brief Operador de igualdad. Comprueba si se esta apuntando a la misma palabra
         * @param other Iterador a comparar.
         * @return True si son iguales, False en otro caso
         */
        bool operator==(const possible_words_iterator &other) const;
        /**
         *@brief @brief Operador de desigualdad. Comprueba si NO estan apuntando a la misma palabra
         * @param other Iterador a comparar
         * @return True si NO son iguales, False en otro caso
         */
        bool operator!=(const possible_words_iterator &other) const;

        /**
         * @brief Operador de incremento. "mueve" el iterador hasta la proxima palabra formable con las letras almacenadas
         * @return Referencia a this
         */
        possible_words_iterator &operator++();
        /**
         *
         * @return Palabra a la que está apuntando el iterador en el momento de la llamada.
         */
        std::string operator*() const;

    private:
        multiset<char> available_letters;
        int level{};
        node current_node;
        string current_word;

        bool gestion_hi(node nodo);

        bool gestion_hermd(node nodo);

        void gestion_backtrack();


        static bool existe_hi(node current);
        static bool existe_herm(node current);
        static  bool existe_padre(node current);

        friend Dictionary;
    };

    /**
     * @param available_characters Conjunto de letras sobre las que se quieren buscar palabras.
     * @return Devuelve un iterador al inicio del diccionario y almacena los caracteres pasados por  parametros para iterar siolo por las palabras formables.
     */
    possible_words_iterator possible_words_begin(vector<char> &available_characters) const;

    /**
     *
     * @return Devuelve un iterador al final del Diccionario.
     */
    possible_words_iterator possible_words_end() const;
};

#endif //TREE_DICTIONARY_HPP