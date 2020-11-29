#include"Vector.h"
#include<cstdlib>
#define INIT_CAPA 10
/*
template<class T>
Vector<T>::Vector(){
    m_nSize=0;
    m_nCapacity=INIT_CAPA;
    m_pElements=(T*)malloc(sizeof(T)*m_nCapacity);
}

template<class T>
Vector<T>::Vector(int size){
    m_nSize=0;
    m_nCapacity=size;
    m_pElements=(T*)malloc(sizeof(T)*m_nCapacity);
}

template<class T>
Vector<T>::Vector(const Vector& r){
    m_nSize=r.m_nSize;
    m_nCapacity=r.m_nCapacity;
    m_pElements=(T*)malloc(sizeof(T)*m_nCapacity);
    memcpy(m_pElements,r.m_pElements,m_nCapacity*sizeof(T));
}

template<class T>
void Vector<T>::inflate(){
    m_nCapacity*=2;
    m_pElements=(T*)realloc(m_pElements,sizeof(T)*m_nCapacity);
}

template<class T>
Vector<T>::~Vector(){

}

template<class T>
T& Vector<T>::operator[](int index){
    return *(m_pElements+index);
}

template<class T>
T& Vector<T>::at(int index){
    return *(m_pElements+index);
}

template<class T>
int Vector<T>::size() const{
    return m_nSize;
}

template<class T>
void Vector<T>::push_back(const T& x){
    if(m_nSize>=m_nCapacity){
        inflate();
    }
    *(m_pElements+m_nSize)=x;
    m_nSize++;
}

template<class T>
void Vector<T>::clear(){
    m_nSize=0;
}

template<class T>
bool Vector<T>::empty() const{
    return m_nSize?true:false;
}
*/