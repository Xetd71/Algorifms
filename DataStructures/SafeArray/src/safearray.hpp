#include "safearray.h"
#include <iostream>



// we have to indicate that methods of the class Safearray are also inside the namespace xi
namespace xi {


    template<typename T>
    SafeArray<T>::SafeArray(size_t cap)
    {
        _capacity = cap;
        _storage = cap != 0 ? new T[_capacity] : nullptr;           //if not null, create array
    }


    template<typename T>
    SafeArray<T>::SafeArray(const SafeArray <T>& copiedObject)
    {
        _capacity = copiedObject._capacity;                                                             //
        _storage = copiedObject._capacity != 0
                   ? new T[_capacity] : nullptr;                            //the same as SafeArray(copiedObject._capacity)
        std::copy(copiedObject._storage, copiedObject._storage + copiedObject._capacity,
                  _storage);     //cory content of _storage
    }


    template<typename T>
    SafeArray <T>& SafeArray<T>::operator=(const SafeArray <T>& copiedObject)
    {
        SafeArray<T> temp(copiedObject);        //create copy from copiedObject
        swap(*this, temp);                      // exchange temp and *this content 

        return *this;                           //delete the 'temp' and return copied object
    }


    template<typename T>
    void swap(SafeArray <T>& first, SafeArray <T>& second)
    {
        std::swap(first._capacity, second._capacity);       //exchange a _capacity content
        std::swap(first._storage, second._storage);         //exchange a _storage content
    }


    template<typename T>
    SafeArray<T>::~SafeArray()
    {
        delete[] _storage;          //delete _storage array
    }


    template<typename T>
    size_t SafeArray<T>::getCapacity() const
    {
        return _capacity;
    }


    template<typename T>
    T& SafeArray<T>::operator[](size_t k)
    {
        checkBounds(k);             //check is index is right
        return _storage[k];         //return element
    }


    template<typename T>
    const T& SafeArray<T>::operator[](size_t k) const
    {
        checkBounds(k);             //check is index is right
        return _storage[k];         //return element
    }


    template<typename T>
    void SafeArray<T>::checkBounds(size_t index) const
    {
        if(index >= _capacity)                                  //check is index is right,
            throw std::out_of_range("Index out of range");      //if not throw exception
    }


    template<typename T>
    std::ostream& operator<<(std::ostream& out, const SafeArray <T>& subj)
    {
        for(size_t i = 0; i < subj._capacity; i++)
            std::cout << subj._storage[i] << std::endl;         //print the element of _storage at ostream
        return out;
    }


} // namespace xi
