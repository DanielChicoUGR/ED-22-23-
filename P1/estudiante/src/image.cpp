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
#include <map>
#include <cstring>
using namespace std;

static const imagen::byte MAX_BYTE= 255U;

/********************************
      FUNCIONES PRIVADAS
********************************/


void Image::Allocate(int nrows, int ncols, imagen::byte * buffer){
    rows = nrows;
    cols = ncols;
    bool Ebuffer= buffer!=0;
    img = new imagen::byte * [rows];
    for(auto i=0;i<rows;i++){

        img[i] = new imagen::byte[cols];
        if(Ebuffer)  memcpy(img[i],buffer+i*cols,sizeof (imagen::byte) *cols );
    }
}

// Función auxiliar para inicializar imágenes con valores por defecto o a partir de un buffer de datos
void Image::Initialize (int nrows, int ncols, imagen::byte * buffer){
    if ((nrows == 0) || (ncols == 0)){
        rows = cols = 0;
        img = nullptr;
    }

    else {
        Allocate(nrows, ncols, buffer);
    }
}

// Función auxiliar para copiar objetos Imagen

void Image::Copy(const Image & orig){
    Initialize(orig.get_rows(),orig.get_cols());
    for (auto i=0; i<rows;i++)
        for(auto j=0; j<cols;j++) {
            set_pixel(i, j, orig.get_pixel(i, j));

        }
}

// Función auxiliar para destruir objetos Imagen
bool Image::Empty() const{
    return (rows == 0) || (cols == 0);
}
//Cambiar la manera en la que se destruye la memoria
void Image::Destroy(){
    if (!Empty()){
        for(auto i=0; i<rows; i++)
            delete [] img[i];
        delete [] img;
        img=nullptr;
        rows=0;
        cols=0;
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
    for (int k=0; k<nrows*ncols; k++) set_pixel(k,value);
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
    if(img==0 or img[i]==0){
        cerr<<"error de escritura en el pixel "<<i<<"\t"<<j<<"\n";
        assert(false);
    }
    img[i][j] = value;
}
imagen::byte Image::get_pixel (int i, int j) const {
    if(img==0 or img[i]==0){
        cerr<<"error de Lectura en el pixel "<<i<<"\t"<<j<<"\n";
        assert(false);
    }
    return img[i][j];
}

// This doesn't work if representation changes
void Image::set_pixel (int k, imagen::byte value) {

//    img[0][k] = value;

     set_pixel(k/get_cols(),k%get_cols(),value);
}

// This doesn't work if representation changes
imagen::byte Image::get_pixel (int k) const {

//    return img[0][k];

    return get_pixel(k / get_cols(), k % get_cols());
}

// Métodos para almacenar y cargar imagenes en disco
bool Image::Save (const char * file_path) const {
    auto *p=new imagen::byte[size()];
    size_t tam=sizeof(imagen::byte)*cols;
    for(int i=0;i<get_rows(); i++){

        memcpy(p+(i*cols),img[i],tam);

    }

    return WritePGMImage(file_path, p, rows, cols);
}


void Image::Invert(){
    for (auto i = 0; i < rows; i++)
        for(auto j = 0; j < cols; j++)
            set_pixel(i, j,MAX_BYTE-get_pixel(i,j));
}


Image Image::Crop(int nrow, int ncol, int height, int width) const{
    if(nrow < 0 || ncol < 0 )
        assert(false);
             
    Image nueva(height, width);

    for (auto i = 0; i <nueva.get_rows() and nrow+i<get_rows(); i++)
        for(auto j = 0; j < nueva.get_cols() and ncol+i<get_cols(); j++)

            nueva.set_pixel(i, j, get_pixel(i + nrow, j + ncol));


    return nueva;
}





Image Image::Zoom2X(int fila,int columna, int lado)const{
    if(fila < 0 || fila+lado > rows || columna < 0 || columna + lado > cols)
        assert(false);


    Image image(this->Crop(fila, columna, lado, lado));



    Image ret(2 * image.get_rows()-1 , 2 * image.get_cols()-1);

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


double Image::Mean(int i, int j, int height, int width) const{
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
Image Image::Subsample(int factor) const{
    assert(factor>0);

    int nueva_fila=(get_rows()/ (factor));
    int nueva_columa=(get_cols()/(factor));

    Image nueva(nueva_fila,nueva_columa);

    for(auto i=0; i < nueva_fila; i++){

        for(auto j=0;j<nueva_columa;j++){
            double valor_pixel=this->Mean(factor*i,factor*j,factor,factor);
        
            nueva.set_pixel(i,j,round(valor_pixel));
        }
    }


    return nueva;
}





void Image::AdjustContrast(imagen::byte in1, imagen::byte in2, imagen::byte out1, imagen::byte out2){
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



void Image::ShuffleRows(){
    const int p = 9973;

    imagen::byte **im;
    im=new imagen::byte * [get_rows()];

    int newr;

    for (int r=0; r<get_rows(); r++){
        newr = r*p % get_rows();
        im[r]=this->img[newr    ];
    }

    this->img=im;
}
