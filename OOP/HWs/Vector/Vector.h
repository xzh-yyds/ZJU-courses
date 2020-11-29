#ifndef _VECTOR_H
#define _VECTOR_H

#include<cstdlib>
#include<cstring>
#include<iostream>
#define INIT_CAPA 10

template<class T>
class Vector{
private:
    // the number of elements in the container
    int m_nSize;
    // the number of elements that can be held in currently allocated storage
    int m_nCapacity;
    // pointer to the dynamically allocated storage
    T* m_pElements;
    // expand the storage of the container to a new capacity, e.g. 2*m_nCapacity
    void inflate(){
        m_nCapacity*=2;
        m_pElements=(T*)realloc(m_pElements,sizeof(T)*m_nCapacity);
    }
public:
    // creates an empty vector
    Vector(){
        m_nSize=0;
        m_nCapacity=INIT_CAPA;
        m_pElements=(T*)malloc(sizeof(T)*m_nCapacity);
    }
    // creates a vector for holding 'size' elements
    Vector(int size){
        m_nSize=0;
        m_nCapacity=size;
        m_pElements=(T*)malloc(sizeof(T)*m_nCapacity);
    }
    // the copy ctor
    Vector(const Vector& r){
        m_nSize=r.m_nSize;
        m_nCapacity=r.m_nCapacity;
        m_pElements=(T*)malloc(sizeof(T)*m_nCapacity);
        memcpy(m_pElements,r.m_pElements,m_nCapacity*sizeof(T));
    }
    // destructs the vector 
    ~Vector(){

    }
    // accesses the specified element without bounds checking
    T& operator[](int index){
        return *(m_pElements+index);
    }
    // accesses the specified element, throws an exception of type 'std::out_of_range' when index <0 or >=m_nSize
    T& at(int index){
        try{
            if(index<0 || index>=m_nSize){
            throw "std::out_of_range";
        }
        }catch(const char* msg){
            std::cout<<"exception: "<<msg;
        }
        return *(m_pElements+index);
    }
    // return the size of the container
    int size() const{
        return m_nSize;
    }
    // adds an element to the end
    void push_back(const T& x){
        if(m_nSize>=m_nCapacity){
            inflate();
        }
        *(m_pElements+m_nSize)=x;
        m_nSize++;
    }
    // clears the contents
    void clear(){
        m_nSize=0;
    }
    // checks whether the container is empty
    bool empty() const{
        return m_nSize?false:true;
    }
};

#endif