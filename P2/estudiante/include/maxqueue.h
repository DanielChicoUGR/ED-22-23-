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
 * @brief T.D.A. MaxQueue
 *
 * Una instancia del T.D.A. MAXQUEUE nos permite almacenar una Cola de enteros en el que
 * se pueda consultar el mayor elemento almacenado en el TDA
 *
 * Para poder usar el TDA MaxQueue se debe incluir el fichero
 * \#include "maxqueue.h"
 *
 * @section
 *  Representacion del TDA MaxQueue
 *
 *  Se trata de un TDA en forma lista FIFO (First In First Out) o cola en la que se puede consultar
 *  el mayor elemento almacenado en la lista.
 *
 * @author Daniel Chico Valderas
 * @date 2022
 */

class MaxQueue {

public:
    /**
    * @brief Unidades de almacenamiento de la informacion de la cola
     *
     *
     *      Unidad minima que almacena la cola. Almacena el numero y el elemanto mayor almacenado en la cola.
     *          Element.value -> valor
     *          Element.->maximum -> valor maximo almacenado en la cola.
     *
    */
    struct Element {
        int value; // Current value to store
        int maximum; // Current max value in the structure

        /**
         * @brief Sobrecarga operador de salida
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
 * @brief Constructor de copia constante del TDA MaxQueue
 * @param other -> Elemento a copiar.
 */

    MaxQueue(const MaxQueue& other);

    /**
 * @brief Operador de asignacion del TDA MaxQueue
 * @param other Elemento a asignar
 * @return Copia de \e other
 */


    MaxQueue& operator=(const MaxQueue& other);

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

    /**
    * @brief insertar elemento en la Cola
    * @param number Elemento a insertar.
    */

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