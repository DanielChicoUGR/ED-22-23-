//
// Created by daniel on 10/1/22.
//
#include <iostream>
//#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]){

    char *origen, *destino; // nombres de los ficheros
    Image image;

    int fila,col,altura,anchura;

    // Comprobar validez de la llamada
    if (argc != 7){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: zoom <FichImagenOriginal> <FichImagenDestino> <fila> <columna> <NumeroFilaRecortar> <NumeroColumnaRecortar>\n";
        exit (1);
    }

    // Obtener argumentos
    origen  = argv[1];
    destino = argv[2];

    fila= stoi(argv[3]);
    col= stoi(argv[4]);
    altura= stoi(argv[5]);
    anchura= stoi(argv[6]);

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;
    cout<<"Filas: "<<fila<<endl;
    cout<<"Columnas: "<<col<<endl;
    cout<<"Filas a recortar: "<<altura<<endl;
    cout<<"Columnas a recortar: "<<anchura<<endl;

    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << origen << ":" << endl;
    cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

    auto nueva=image.Crop(fila,col,altura,anchura);

    // Guardar la imagen resultado en el fichero
    if (nueva.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;
}