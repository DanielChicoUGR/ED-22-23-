/**
 * @file maxqueue.cpp
 * @brief  Archivo de implementación del TDA MaxQueue
 * @author
 */
#include "maxqueue.h"

void MaxQueue::copia(const std::stack<Element> &otro) {
    cola=otro;

}



void MaxQueue::push(int number) {
    auto aux=std::stack<Element>();
    while(!cola.empty()){
        aux.push(cola.top());
        cola.pop();
    }
    cola.push({number,number});

    while(!aux.empty()) {
        if(aux.top().maximum<cola.top().maximum)
            aux.top().maximum=cola.top().maximum;
        cola.push(aux.top());
        aux.pop();
    }


}

bool MaxQueue::isEmpty() const {
    return cola.empty();
}
void MaxQueue::pop() {
    cola.pop();
}

int MaxQueue::max() const {
    return cola.top().maximum;
}

int MaxQueue::front_value() const {
    return cola.top().value;
}

MaxQueue::Element MaxQueue::front() const {
    return cola.top();
}

unsigned int MaxQueue::size() const {
    return cola.size();
}

MaxQueue::MaxQueue(MaxQueue &other) {
    copia(other.cola);

}
void MaxQueue::clear() {
    while(!cola.empty()){
        cola.pop();
    }
}

MaxQueue::MaxQueue(const MaxQueue &other) {
    clear();
    copia(other.cola);
}

MaxQueue &MaxQueue::operator=(const MaxQueue &other) {
    new MaxQueue(other);
    return *this;
}



