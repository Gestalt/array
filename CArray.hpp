#ifndef CArrayHPP
#define CArrayHPP

#include <iostream>
#include <stdio.h>

#include "CArrayException.h"

template <typename TData>
arr::CArray<TData>::CArray()
    : array(0) , arr_size(0u) , capacity(0u)
{
}

template <typename TData>
arr::CArray<TData>::CArray(
    const CArray& _rhs
  ) : array(0) , arr_size(_rhs.arr_size) , capacity(_rhs.capacity)
{
  array = new TData[_rhs.capacity];
  memcpy(array, _rhs.array, _rhs.arr_size * sizeof(TData));
}

template <typename TData>
arr::CArray<TData>::~CArray()
{
  if (array)
  {
    delete[] array;
    array = 0;
  }
}

template <typename TData>
arr::CArray<TData>& arr::CArray<TData>::operator=(
    const CArray& _rhs
  )
{
  if (this != &_rhs)
  {
    TData* source = array;
    array = new TData[_rhs.capacity];
    memcpy(array, _rhs.array, _rhs.arr_size * sizeof(TData));
    delete source;

    arr_size = _rhs.arr_size;
    capacity = _rhs.capacity;
  }
  return *this;
}

template <typename TData>
void arr::CArray<TData>::print() const
{
  std::cout << "Elements: |";
  for (unsigned int i = 0; i < arr_size; i++)
  {
    std::cout << array[i] << "|";
  }
  std::cout << std::endl;
}

template <typename TData>
void arr::CArray<TData>::erase(
    unsigned int _index
  )
{
  if (_index >= arr_size)
  {
    throw CArrayException("Attempt to erase out of range element");
  }
  if (_index < arr_size - 1)
  {
    memcpy(&array[_index], &array[_index + 1], (arr_size - 1 - _index) * sizeof(TData));
  }
  arr_size--;
}

template <typename TData>
void arr::CArray<TData>::insert(
    unsigned int _index, const TData& _value
  )
{
  if (_index > arr_size)
  {
    throw CArrayException("Attempt to insert element out of range array");
  }

  if (capacity == arr_size)
  {
    realloc();
  }

  memcpy(&array[_index + 1], &array[_index], (arr_size - _index) * sizeof(TData));

  array[_index] = _value;
  arr_size++;
}

template <typename TData>
void arr::CArray<TData>::push_back(
    const TData& _value
  )
{
  if (arr_size == capacity)
  {
    realloc();
  }
  array[arr_size] = _value;
  arr_size++;
}

template <typename TData>
void arr::CArray<TData>::clear()
{
  arr_size = 0u;
  delete[] array;
  array = 0;
}

template <typename TData>
void arr::CArray<TData>::sort()
{
  quicksort(0, (int)(arr_size - 1));
}

template <typename TData>
void arr::CArray<TData>::eraseIf(
    const AbstractPredicate<TData>& _predicate
  )
{
  unsigned int i = 0;
  while (i < arr_size)
  {
    if (_predicate(array[i]))
    {
      erase(i);
    }
    else
    {
      i++;
    }
  }
}

template <typename TData>
unsigned int arr::CArray<TData>::size() const
{
  return arr_size;
}

template <typename TData>
const TData& arr::CArray<TData>::operator[] (
    unsigned int _index
  ) const
{
  return getElement(_index);
}

template <typename TData>
TData& arr::CArray<TData>::operator[] (
    unsigned int _index
  )
{
  return getElement(_index);
}

template <typename TData>
void arr::CArray<TData>::quicksort(
    int _left, int _right
  )
{
  int i = _left;
  int j = _right;
  const TData mid = array[ (i + j) / 2 ];
  while (i <= j)
  {
    while (array[i] < mid)
    {
      i++;
    }
    while (array[j] > mid)
    {
      j--;
    }
    if (i <= j)
    {
      const TData tmp = array[j];
      array[j] = array[i];
      array[i] = tmp;

      i++;
      j--;
    }
  }
  if (_left < j)
  {
    quicksort(_left, j);
  }
  if (_right > i)
  {
    quicksort(i, _right);
  }
}

template <typename TData>
void arr::CArray<TData>::realloc()
{
  capacity = (capacity == 0) ? (1u) : (capacity * 2);

  TData* buff = new TData[capacity];

  if (array)
  {
    memcpy(buff, array, size() * sizeof(TData));
    delete[] array;
  }
  array = buff;
}

template <typename TData>
TData& arr::CArray<TData>::getElement(
    unsigned int _index
  ) const
{
  if (arr_size == 0 || _index > arr_size - 1)
  {
    throw CArrayException("Attempt to access on out of range index");
  }
  return array[_index];
}

#endif

