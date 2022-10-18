/**
 * @file maxqueue.h
 * @brief  Archivo de especificación del TDA MaxQueue
 * @author
 */


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