/**
 * @file maxqueue.h
 * @brief  Archivo de especificación del TDA MaxQueue
 * @author
 */


#ifndef TDA_MAXSTACK_H
#define TDA_MAXSTACK_H
#include <stack>
#include <iostream>

//#include <ostream>



/**
 * @brief T.D.A. MaxStack
 *
 * Una instancia del T.D.A. MAXSTACK nos permite almacenar una Cola de enteros en el que
 * se pueda consultar el mayor elemento almacenado en el TDA
 *
 * Para poder usar el TDA MaxStack se debe incluir el fichero
 * \#include "maxstack.h"
 *
 * @author Daniel Chico Valderas
 * @date 2022
 */

class MaxQueue {
/**
 * @page page_repMaxStack Representación del TDA MaxStack
 *
 */
public:
    /**
    * @brief Unidades de almacenamiento de la informacion de la cola
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
    MaxQueue()=default;

    /**
     * @brief Constructor de copia del TDA MaxStack
     * @param other
     */
    MaxQueue( MaxQueue& other);

    /**
     * @brief Consulta la cantidad de elementos almacenados en el TDA MaxStack
     * @return Tamaño de la Cola
     */
    unsigned int size() const;

    /**
     * @brief Consulta el primer elemento insertado en la Cola.
     * @return Ultimo elemento de la Cola
     */
    Element front() const;

    /**
     * @brief Consulta el valor del primer elemento insertado en la Cola.
     * @return
     */
    int front_value() const;

    /**
     * @brief Consulta el elemento maximo de la Cola
     * @return Elemento de mayor valor almacenado
     */
    int max() const;

    /**
     * @brief Elimina el primer elemento almacenado
     */
    void pop();

    /**
     * @brief Borra todos los elementos de la Cola
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
    void copia(const std::stack<Element> &otro);

    std::stack<Element> cola;




};


#endif // MaxQueue