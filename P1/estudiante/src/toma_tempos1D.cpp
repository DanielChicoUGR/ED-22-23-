//
// Created by daniel on 10/7/22.
//
//
// Created by daniel on 10/6/22.
// Fichero: barajar.cpp
// baraja las columnas de una imagen PGM
//

#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <chrono>

#include <image1D.h>
#include <fstream>

using namespace std;

static const int INCREMENTO=100;



int main (int argc, char *argv[]){

    char *origen, *destino; // nombres de los ficheros
    Image image;

    // Comprobar validez de la llamada
    if (argc != 2){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: negativo <FichImagenOriginal> \n";
        exit (1);
    }

    // Obtener argumentos
    origen  = argv[1];


    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
//    cout << "Fichero resultado: " << destino << endl;

    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }
    //Almacenara copias de las imagenes en funcion de la cantidad de filas que contenga
    unordered_map<int,Image> buffer_filas;

    //Almacenará copias de las imagenes en funcion de la cantidad de columnas que tenga.
    unordered_map<int,Image> buffer_columnas;


    int fila,columna;
    fila=0;
    columna=0;
    for(auto i=1;i*INCREMENTO<image.get_rows();i++){
        buffer_filas[i*INCREMENTO]=image.Crop(fila,columna,INCREMENTO*i,image.get_cols());
    }

    for(auto i=1;i*INCREMENTO<image.get_cols();i++){
        buffer_columnas[i*INCREMENTO]=image.Crop(fila,columna,image.get_rows(),INCREMENTO*i);
    }
    ofstream f("estudiante/data/datos1D.dat");
    if(f) {
//     Testeo distinto numero de filas
        f << "Filas constantes\n";

        for (auto im: buffer_filas) {
            Image aux = im.second;
            auto start = chrono::high_resolution_clock::now();
            aux.ShuffleRows();
            auto stop = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = start - stop;
            f << im.first << "\t" << elapsed.count() << endl;
        }

        f << "Columnas constantes\n";

        for (auto im: buffer_columnas) {
            Image aux = im.second;
            auto start = chrono::high_resolution_clock::now();
            aux.ShuffleRows();
            auto stop = chrono::high_resolution_clock::now();

            chrono::duration<double> elapsed = start - stop;
            f << im.first << "\t" << elapsed.count() << endl;


        }

    }



    return 0;
}


//int main (int argc, char *argv[]){
//
//    char *origen, *destino; // nombres de los ficheros
//    Image image;
//
//    // Comprobar validez de la llamada
//    if (argc != 3){
//        cerr << "Error: Numero incorrecto de parametros.\n";
//        cerr << "Uso: negativo <FichImagenOriginal> <FichImagenDestino>\n";
//        exit (1);
//    }
//
//    // Obtener argumentos
//    origen  = argv[1];
//    destino = argv[2];
//
//    // Mostramos argumentos
//    cout << endl;
//    cout << "Fichero origen: " << origen << endl;
//    cout << "Fichero resultado: " << destino << endl;
//
//    // Leer la imagen del fichero de entrada
//    if (!image.Load(origen)){
//        cerr << "Error: No pudo leerse la imagen." << endl;
//        cerr << "Terminando la ejecucion del programa." << endl;
//        return 1;
//    }
//
//    // Mostrar los parametros de la Imagen
//    cout << endl;
//    cout << "Dimensiones de " << origen << ":" << endl;
//    cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;
//
//    image.Invert();
//
//    // Guardar la imagen resultado en el fichero
//    if (image.Save(destino))
//        cout  << "La imagen se guardo en " << destino << endl;
//    else{
//        cerr << "Error: No pudo guardarse la imagen." << endl;
//        cerr << "Terminando la ejecucion del programa." << endl;
//        return 1;
//    }
//
//    return 0;
//}