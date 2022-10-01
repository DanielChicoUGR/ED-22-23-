/**
 * @file image.cpp
 * @brief Fichero con definiciones para los métodos primitivos de la clase Image
 *
 */

//#include <cstring>
#include <cassert>
#include <iostream>
#include <cmath>
#include <image.h>
#include <imageIO.h>

using namespace std;

static const imagen::byte MAX_BYTE= 255U;

/********************************
      FUNCIONES PRIVADAS
********************************/
void Image::Allocate(int nrows, int ncols, imagen::byte * buffer){
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
void Image::Initialize (int nrows, int ncols, imagen::byte * buffer){
    if ((nrows == 0) || (ncols == 0)){
        rows = cols = 0;
        img = 0;
    }
    else Allocate(nrows, ncols, buffer);
}

// Función auxiliar para copiar objetos Imagen

void Image::Copy(const Image & orig){
    Initialize(orig.rows,orig.cols);
    for (int k=0; k<rows*cols;k++)
        set_pixel(k,orig.get_pixel(k));
}

// Función auxiliar para destruir objetos Imagen
bool Image::Empty() const{
    return (rows == 0) || (cols == 0);
}

void Image::Destroy(){
    if (!Empty()){
        delete [] img[0];
        delete [] img;
    }
}

LoadResult Image::LoadFromPGM(const char * file_path){
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

Image::Image(){
    Initialize();
}

// Constructores con parámetros
Image::Image (int nrows, int ncols, imagen::byte value){
    Initialize(nrows, ncols);
    for (int k=0; k<rows*cols; k++) set_pixel(k,value);
}

bool Image::Load (const char * file_path) {
    Destroy();
    return LoadFromPGM(file_path) == LoadResult::SUCCESS;
}

// Constructor de copias

Image::Image (const Image & orig){
    assert (this != &orig);
    Copy(orig);
}

// Destructor

Image::~Image(){
    Destroy();
}

// Operador de Asignación

Image & Image::operator= (const Image & orig){
    if (this != &orig){
        Destroy();
        Copy(orig);
    }
    return *this;
}

// Métodos de acceso a los campos de la clase

int Image::get_rows() const {
    return rows;
}

int Image::get_cols() const {
    return cols;
}

int Image::size() const{
    return get_rows()*get_cols();
}

// Métodos básicos de edición de imágenes
void Image::set_pixel (int i, int j, imagen::byte value) {
    img[i][j] = value;
}
imagen::byte Image::get_pixel (int i, int j) const {
    return img[i][j];
}

// This doesn't work if representation changes
void Image::set_pixel (int k, imagen::byte value) {
    // TODO this makes assumptions about the internal representation
    // TODO Can you reuse set_pixel(i,j,value)?
    img[0][k] = value;

    // set_pixel(k/rows,k%rows,value);
}

// This doesn't work if representation changes
imagen::byte Image::get_pixel (int k) const {
    // TODO this makes assumptions about the internal representation
    // TODO Can you reuse get_pixel(i,j)?
    return img[0][k];

    // return get_pixel(k/rows,k%rows);
}

// Métodos para almacenar y cargar imagenes en disco
bool Image::Save (const char * file_path) const {
    // TODO this makes assumptions about the internal representation
    imagen::byte * p = img[0];
    return WritePGMImage(file_path, p, rows, cols);
}


void Image::Invert(){
    for (auto i = 0; i < rows; i++)
        for(auto j = 0; j < cols; j++)
            set_pixel(i, j,MAX_BYTE-get_pixel(i,j));
}


Image Image::Crop(int nrow, int ncol, int height, int width) const{
    if(nrow < 0 || nrow+height > rows || ncol < 0 || ncol+width > cols)     
        assert(false);
             
    Image nueva(height, width);
    
    for (auto i = 0; i <nueva.get_rows(); i++)
        for(auto j = 0; j < nueva.get_cols(); j++)
            nueva.set_pixel(i, j,this->get_pixel(i+nrow,j+ncol));

    return nueva;
}



Image Image::Zoom2X(int fila,int columna, int lado)const{
    if(fila < 0 || fila+lado > rows || columna < 0 || columna + lado > cols)
        assert(false);


    Image image(this->Crop(fila, columna, lado, lado));


    Image ret(2 * image.get_rows()-1 , 2 * image.get_cols()-1);
    for (auto i=0; i < image.get_rows(); i++)
        for(auto j=0; j < image.get_cols(); j++)
            ret.set_pixel(2*i,2*j, image.get_pixel(i, j));



    for (auto i=0;i<ret.get_rows();i+=2)
        for(auto j=1;j<ret.get_cols();j+=2){
            int pixel= round((ret.get_pixel(i,j-1)+ret.get_pixel(i,j+1))/2.0);
            ret.set_pixel(i,j,pixel);
        }

    for(auto i=1;i<ret.get_rows();i+=2)
        for(auto j=0;j<ret.get_cols();j++){

            int pixel=round((ret.get_pixel(i-1,j)+ret.get_pixel(i+1,j))/2.0);

            ret.set_pixel(i,j,pixel);
        }

    return ret;
}


double Image::Mean(int i, int j, int height, int width) const{
    if(i < 0 || i+height > rows || j < 0 || j+width > cols)     
        assert(false);
    
    double media, n;
    media=0.0f;
    
    int aux=0;
    n=double(height*width);

    for(auto a=0;a<height;a++)
        for(auto b=0;b<width;b++)
            aux+=get_pixel(i+a,j+b);
    
    media=double(aux);

    return media/n;
}


Image Image::Subsample(int factor) const{
    
        assert(factor>0);

    int nueva_fila=round(get_rows()/double (factor));
    int nueva_columa=round(get_cols()/double(factor));

    Image nueva(nueva_fila,nueva_columa);

    for(int i=0;i<nueva_fila;i++){
        int filas=(nueva_fila-i==1)?get_rows()%factor:factor;
        for(int j=0;j<nueva_columa;j++){
            int columnas=(nueva_columa-j==1)?get_cols()%factor:factor;

            double valor_pixel=this->Mean(factor*i,factor*j,filas,columnas);
        
            nueva.set_pixel(i,j,round(valor_pixel));
        }
    }


    return nueva;
}





void Image::AdjustContrast(imagen::byte in1, imagen::byte in2, imagen::byte out1, imagen::byte out2){
    
    double E1=double(out2-out1)/double(in2-in1);

    for(int i=0;i< size();i++)
        set_pixel(i,round(out1+(E1*(get_pixel(i)-in1))));
}

