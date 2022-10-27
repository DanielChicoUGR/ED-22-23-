#ifndef __BAG_H__
#define __BAG_H__

#include <vector>
#include <random>
/**
 *  \brief TDA abstracto Bolsa
 *
 *  Este TDA abstracto nos permite trabajar con una colección de elementos que
 *  permite la extracción de elementos de forma aleatoria sin reemplazamiento
 */


template <class T>
class Bag{
private:
    std::vector<T> v;
public:
    /**
     * @brief Constructor por defecto.
     */
    Bag()=default;

    /**
     * @brief Constructor de copia
     * @param other objeto \e Bag a copiar
     */
    Bag(const Bag<T>& other)=default;

    /**
     * @brief añade un elemento a la bolsa
     * @param value Elemento del tipo T a añadir a la bolsa
     */
    inline void add(const T& value){v.push_back(value);}

    /**
     * @brief Extrae un elemento aleatorio de la bolsa.
     * DEvuelve un elemento de la bolsa y lo elimina de la misma
     * @pre La bolsa no está vacía
     * @post El elemento devuelto es extraido de la bolsa.
     *
     */
    inline T get(){
//        srand(time(NULL));
        int elemento=rand()%v.size();

        T ret=v[elemento];

        v.erase(v.begin()+elemento);
        return ret;
    }

    /**
     * @brief Elimina todos los elementos de la bolsa
     * Borra todos los elementos almacenados en la bolsa.
     */
    inline void clear(){v.clear();}

    /**
     * @brief Cantidad de elementos del tipo T que almacena la bolsa
     *
     * @return Numero de elementos almacenados
     */
    inline unsigned int size(){return v.size();}

    /**
     * @brief Comprueba si la bolsa esta vacia
     * @return True en caso de estarlo, falso en caso contrario
     */
    inline bool empty(){return v.empty();}

    /**
     * @brief Sobrecarga del operador de asignacion
     * @param other \e Bag<T> a copiar
     * @return Referencia a this
     */

    inline const Bag<T>& operator=(const Bag<T>& other){
        v=other.v;
        return *this;
    }


};
#endif
