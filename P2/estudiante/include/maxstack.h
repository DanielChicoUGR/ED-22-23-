/**
 * @file maxstack.h
 * @brief  Archivo de especificación del TDA MaxStack
 * @author Daniel Chico Valderas.
 */


#ifndef TDA_MAXSTACK_H
#define TDA_MAXSTACK_H
#include <queue>

/**
 * @brief Unidades de almacenamiento de la informacion de la pila
 */
struct Element {
    int value; // Current value to store
    int maximum; // Current max value in the structure

    /**
     * @brief SSObrecarga operador de salida
     * @param f Flujo de salida
     * @param otro Dato a escribir en el flujo
     * @return Flujo de salida.
     */
    inline friend std::ostream & operator<<(std::ostream & f,const Element  & otro){
        f<<otro.value<<","<<otro.maximum;
        return f;
    }
};

/**
 * @brief T.D.A. MaxStack
 *
 * Una instancia del T.D.A. MAXSTACK nos permite almacenar una Pila de enteros en el que
 * se pueda consultar el mayor elemento almacenado en el TDA
 *
 * Para poder usar el TDA MaxStack se debe incluir el fichero
 * \#include "maxstack.h"
 *
 * @author Daniel Chico Valderas
 * @date 2022
 */

class MaxStack{
    /**
     * @page page_repMaxStack Representación del TDA MaxStack
     *
     * @section
     */
public:

    /**
     * @brief Constructor por defecto del TDA MaxStack. Genera una pila vacía
     */
    MaxStack() = default;

    /**
     * @brief Constructor de copia del TDA MaxStack
     * @param other
     */
    MaxStack( MaxStack& other);

    /**
     * @brief Consulta la cantidad de elementos almacenados en el TDA MaxStack
     * @return Tamaño de la pila
     */
    unsigned int size() const;

    /**
     * @brief Consulta el ultimo elemento insertado en la pila.
     * @return Ultimo elemento de la pila
     */
    Element top() const;

    /**
     * @brief Consulta el valor del ultimo elemento insertado en la pila.
     * @return
     */
    int top_value() const;

    /**
     * @brief Consulta el elemento maximo de la pila
     * @return Elemento de mayor valor almacenado
     */
    int max() const;

    /**
     * @brief Elimina el ultimo elemento almacenado
     */
    void pop();

    /**
     * @brief Borra todos los elementos de la pila
     */
    void clear();

    /**
     * @brief Consulta si hay elementos almacenados
     * @return True -> HAy elementos
     * @return False -> No hay elementos almacenados
     */
    bool isEmpty() const;

    void push(int number);


private:


    /**
     * @brief Copia los elementos de un vector de Elementos.
     *
     */
    void copia( std::queue<Element> &otro);

    std::queue<Element> pila;




};










#endif // TDA_MAXSTACK_H

