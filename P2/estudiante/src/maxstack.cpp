/**
 * @file maxstack.cpp
 * @brief  Archivo de implementación del TDA MaxStack
 * @author
 */
#include <cstring>
#include <iostream>
#include "maxstack.h"
//
//MaxStack::MaxStack() {
//}

MaxStack::MaxStack( MaxStack &other) {
    clear();

    copia(other.pila);

}

unsigned int MaxStack::size() const {
    return pila.size();
}

MaxStack::Element MaxStack::top() const {
    return pila.front();
}

int MaxStack::max() const {
    return pila.front().maximum;
}

void MaxStack::clear() {
    while(!pila.empty())
        pila.pop();

}

bool MaxStack::isEmpty() const {
    return pila.empty();
}

void MaxStack::push(int number) {
    auto aux=std::queue<Element>();
    int max;
    if(pila.front().maximum>number)
        max=pila.front().maximum;
    else
        max=number;

    aux.push({number,max});
    while(!pila.empty()) {
        aux.push(pila.front());
        pila.pop();
    }
    pila.swap(aux);

//    delete aux;
}

void MaxStack::copia( const std::queue<Element> &otro) {
    pila=otro;
}

void MaxStack::pop() {
    pila.pop();

}

int MaxStack::top_value() const {
    return pila.front().value;
}

MaxStack::MaxStack(const MaxStack &other) {
    clear();
    copia(other.pila);

}

MaxStack &MaxStack::operator=(const MaxStack &other) {
    new MaxStack(other);
    return *this;
}
