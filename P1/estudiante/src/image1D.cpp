/**
 * @file image1D.cpp
 * @brief Fichero con definiciones para los métodos primitivos de la clase Image
 *
 */

//#include <cstring>
#include <cassert>
#include <iostream>
#include <cmath>
#include "image1D.h"
#include "imageIO.h"


using namespace std;

static const imagen::byte MAX_BYTE= 255U;

/********************************
      FUNCIONES PRIVADAS
********************************/
void Image1D::Allocate(int nrows, int ncols, imagen::byte * buffer){
    rows = nrows;
    cols = ncols;

    img = new imagen::byte * [rows];

    if (buffer != 0)
        img[0] = buffer;
    else
        img[0] = new imagen::byte [rows * cols];

    for (int i=1; i < rows; i++)
        img[i] = img[i-1] + cols;
}

// Función auxiliar para inicializar imágenes con valores por defecto o a partir de un buffer de datos
void Image1D::Initialize (int nrows, int ncols, imagen::byte * buffer){
    if ((nrows == 0) || (ncols == 0)){
        rows = cols = 0;
        img = 0;
    }
    else Allocate(nrows, ncols, buffer);
}

// Función auxiliar para copiar objetos Imagen

void Image1D::Copy(const Image1D & orig){
    Initialize(orig.rows,orig.cols);
    for (int k=0; k<rows*cols;k++)
        set_pixel(k,orig.get_pixel(k));
}

// Función auxiliar para destruir objetos Imagen
bool Image1D::Empty() const{
    return (rows == 0) || (cols == 0);
}

void Image1D::Destroy(){
    if (!Empty()){
        delete [] img[0];
        delete [] img;
    }
}

LoadResult Image1D::LoadFromPGM(const char * file_path){
    if (ReadImageKind(file_path) != IMG_PGM)
        return LoadResult::NOT_PGM;

    imagen::byte * buffer = ReadPGMImage(file_path, rows, cols);
    if (!buffer)
        return LoadResult::READING_ERROR;

    Initialize(rows, cols, buffer);
    return LoadResult::SUCCESS;
}

/********************************
       FUNCIONES PÚBLICAS
********************************/

// Constructor por defecto

Image1D::Image1D(){
    Initialize();
}

// Constructores con parámetros
Image1D::Image1D (int nrows, int ncols, imagen::byte value){
    Initialize(nrows, ncols);
    for (int k=0; k<rows*cols; k++) set_pixel(k,value);
}

bool Image1D::Load (const char * file_path) {
    Destroy();
    return LoadFromPGM(file_path) == LoadResult::SUCCESS;
}

// Constructor de copias

Image1D::Image1D (const Image1D & orig){
    assert (this != &orig);
    Copy(orig);
}

// Destructor

Image1D::~Image1D(){
    Destroy();
}

// Operador de Asignación

Image1D & Image1D::operator= (const Image1D & orig){
    if (this != &orig){
        Destroy();
        Copy(orig);
    }
    return *this;
}

// Métodos de acceso a los campos de la clase

int Image1D::get_rows() const {
    return rows;
}

int Image1D::get_cols() const {
    return cols;
}

int Image1D::size() const{
    return get_rows()*get_cols();
}

// Métodos básicos de edición de imágenes
void Image1D::set_pixel (int i, int j, imagen::byte value) {
    img[i][j] = value;
}
imagen::byte Image1D::get_pixel (int i, int j) const {
    return img[i][j];
}

// This doesn't work if representation changes
void Image1D::set_pixel (int k, imagen::byte value) {
    // TODO this makes assumptions about the internal representation
    // TODO Can you reuse set_pixel(i,j,value)?
    img[0][k] = value;

    // set_pixel(k/rows,k%rows,value);
}

// This doesn't work if representation changes
imagen::byte Image1D::get_pixel (int k) const {
    // TODO this makes assumptions about the internal representation
    // TODO Can you reuse get_pixel(i,j)?
    return img[0][k];

    // return get_pixel(k/rows,k%rows);
}

// Métodos para almacenar y cargar imagenes en disco
bool Image1D::Save (const char * file_path) const {
    // TODO this makes assumptions about the internal representation
    imagen::byte * p = img[0];
    return WritePGMImage(file_path, p, rows, cols);
}


void Image1D::Invert(){
    for (auto i = 0; i < rows; i++)
        for(auto j = 0; j < cols; j++)
            set_pixel(i, j,MAX_BYTE-get_pixel(i,j));
}


Image1D Image1D::Crop(int nrow, int ncol, int height, int width) const{
    if(nrow < 0  || ncol < 0 )
        assert(false);

    Image1D nueva(height, width);
    
    for (auto i = 0; i <nueva.get_rows() and nrow+i<get_rows(); i++)
        for(auto j = 0; j < nueva.get_cols() and ncol+i<get_cols(); j++)
            nueva.set_pixel(i, j,this->get_pixel(i+nrow,j+ncol));

    return nueva;
}



Image1D Image1D::Zoom2X(int fila,int columna, int lado)const{
    if(fila < 0 || fila+lado > rows || columna < 0 || columna + lado > cols)
        assert(false);


    Image1D image(this->Crop(fila, columna, lado, lado));



    Image1D ret(2 * image.get_rows()-1 , 2 * image.get_cols()-1);

    double x[ret.get_rows()][ret.get_cols()];

    for (auto i=0; i < image.get_rows(); i++)
        for(auto j=0; j < image.get_cols(); j++) {
            x[2*i][2*j]=image.get_pixel(i, j);
            ret.set_pixel(2 * i, 2 * j, image.get_pixel(i, j));
        }


    for (auto i=0;i<ret.get_rows();i+=2)
        for(auto j=1;j<ret.get_cols();j+=2){
            x[i][j]= (x[i][j-1]+x[i][j+1])/2.f;
            ret.set_pixel(i,j,round(x[i][j]));
        }

    for(auto i=1;i<ret.get_rows();i+=2)
        for(auto j=0;j<ret.get_cols();j++){

            x[i][j]=(x[i-1][j]+x[i+1][j])/2.0f;

            ret.set_pixel(i,j,round(x[i][j]));
        }

    return ret;
}


double Image1D::Mean(int i, int j, int height, int width) const{
    if(i < 0 || j < 0 )
        assert(false);
    
    double  n;

    if (i+height >= get_rows()) //Si se pasa de filas, se fuerza a que no
        height=get_rows()-i;

    if (j+width >= get_cols()) //Si se pasa de columnas, se fuerza a que no
        width =get_cols()-j;

    int aux=0;
    n=double(height*width);

    for(auto a=0;a<height ;a++)
        for(auto b=0;b<width ;b++)
            aux+=get_pixel(i+a,j+b);
    


    return double(aux)/n;
}

//Posible fallo si factor no divide a las filas/columnas de la imagen? -> Solution
Image1D Image1D::Subsample(int factor) const{
    assert(factor>0);

    int nueva_fila=(get_rows()/ (factor));
    int nueva_columa=(get_cols()/(factor));

    Image1D nueva(nueva_fila,nueva_columa);

    for(auto i=0; i < nueva_fila; i++){

        for(auto j=0;j<nueva_columa;j++){
            double valor_pixel=this->Mean(factor*i,factor*j,factor,factor);
        
            nueva.set_pixel(i,j,round(valor_pixel));
        }
    }


    return nueva;
}





void Image1D::AdjustContrast(imagen::byte in1, imagen::byte in2, imagen::byte out1, imagen::byte out2){
    if(in1>=in2 or out1>=out2 or in1<0 or in2<0 or out1<0 or out2<0)
        assert(false);


    const double E0=double(out1-0)/double(in1-0);
    const double E1=double(out2-out1)/double(in2-in1);
    const double E2=double(255-out2)/double(255-in2);
    double E3;
//    for(int i=0;i< size();i++)
//        set_pixel(i,round(out1+(E1*(get_pixel(i)-in1))));
    for(auto i=0;i<get_rows();i++){
        for(auto j=0;j<get_cols();j++){
            imagen::byte valor_pixel=get_pixel(i,j);
            if(valor_pixel < in1)
                E3=0.0f+(E0*double(valor_pixel-0));
            else if(valor_pixel > in2)
                E3=double(out2)+(E2*double(valor_pixel-in2));
            else
                E3=double(out1)+(E1*double(valor_pixel-in1));

            E3=round(E3);
            set_pixel(i,j,E3);
        }
    }
}


void Image1D::ShuffleRows() {
    const int p = 9973;

    Image1D temp(rows,cols);
    
    int newr;
    
    for (int r=0; r<rows; r++){
        newr = r*p % rows;
        for (int c=0; c<cols;c++)
            temp.set_pixel(r,c,get_pixel(newr,c));
    }

    Copy(temp);
}


