#ifndef CArrayHPP
#define CArrayHPP

#include <iostream>
#include <stdio.h>

#include "CArrayException.h"

template <typename TData>
arr::CArray<TData>::CArray()
    : array(0)
    , arr_size(0u)
    , capacity(0u) {
}

template <typename TData>
arr::CArray<TData>::CArray(const CArray& rhs)
    : array(0)
    , arr_size(rhs.arr_size)
    , capacity(rhs.capacity) {
        array = new TData[rhs.capacity];
        memcpy(&array[0], &rhs.array[0], rhs.arr_size * sizeof(TData));
}

template <typename TData>
arr::CArray<TData>::~CArray() {
    if (array) {
        delete[] array;
        array = 0;
    }
}

template <typename TData>
arr::CArray<TData>& arr::CArray<TData>::operator=(const CArray& rhs) {
    if (this != &rhs) {
        TData* source = array;
        array = new TData[rhs.capacity];
        memcpy(&array[0], &rhs.array[0], rhs.arr_size * sizeof(TData));
        delete source;

        arr_size = rhs.arr_size;
        capacity = rhs.capacity;
    }
    return *this;
}

template <typename TData>
void arr::CArray<TData>::print() const {
    std::cout << "Elements: |";
    for (unsigned int i = 0; i < arr_size; i++) {
        std::cout << array[i] << "|";
    }
    std::cout << std::endl;
}

template <typename TData>
void arr::CArray<TData>::erase(unsigned int index) {
    if (index > arr_size) {
        throw CArrayException("Attempt to erase out of range element");
    }

    for (unsigned int i = index; i < arr_size; i++) {
        array[i] = array[i + 1];
    }
    arr_size--;
}

template <typename TData>
void arr::CArray<TData>::insert(unsigned int index, const TData& value) {
    if (index > arr_size) {
        throw CArrayException("Attempt to insert element out of range array");
    }

    if (capacity == arr_size) {
        realloc();
    }

    for (unsigned int i = arr_size; i > index; i--) {
        array[i] = array[i - 1];
    }

    array[index] = value;
    arr_size++;
}

template <typename TData>
void arr::CArray<TData>::push_back(const TData& value_) {
    if (arr_size == capacity) {
        realloc();
    }
    array[arr_size] = value_;
    arr_size++;
}

template <typename TData>
void arr::CArray<TData>::clear() {
    arr_size = 0u;
    delete[] array;
    array = 0;
}

template <typename TData>
void arr::CArray<TData>::sort() {
    quicksort(0, (int)(arr_size - 1));
}

template <typename TData>
void arr::CArray<TData>::eraseIf(const AbstractPredicate<TData>& predicate) {
    unsigned int i = 0;
    while (i < arr_size) {
        if (predicate(array, i)) {
            erase(i);
        } else {
            i++;
        }
    }
}

template <typename TData>
unsigned int arr::CArray<TData>::size() const {
    return arr_size;
}

template <typename TData>
const TData& arr::CArray<TData>::operator[] (unsigned int index) const {
    return getElement(index);
}

template <typename TData>
TData& arr::CArray<TData>::operator[] (unsigned int index) {
    return getElement(index);
}

template <typename TData>
void arr::CArray<TData>::quicksort(int left, int right) {
    int i = left;
    int j = right;
    const TData mid = array[ (i + j) / 2 ];
    while (i <= j) {
        while (array[i] < mid) {
            i++;
        }
        while (array[j] > mid) {
            j--;
        }
        if (i <= j) {
            const TData tmp = array[j];
            array[j] = array[i];
            array[i] = tmp;

            i++;
            j--;
        }
    }
    if (left < j) {
        quicksort(left, j);
    }
    if (right > i) {
        quicksort(i, right);
    }
}

template <typename TData>
void arr::CArray<TData>::realloc() {
    capacity = (capacity == 0) ? (1u) : (capacity * 2);

    TData* buff = new TData[capacity];

    if (array) {
        memcpy(&buff[0], &array[0], size() * sizeof(TData));
        delete[] array;
    }
    array = buff;
}

template <typename TData>
TData& arr::CArray<TData>::getElement(unsigned int index) const {
    if (arr_size == 0 || index > arr_size - 1) {
        throw CArrayException("Attempt to access on out of range index");
    }

    return array[index];
}


#endif

