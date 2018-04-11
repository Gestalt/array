#ifndef CArrayH
#define CArrayH

namespace arr
{

template<typename TData>
struct AbstractPredicate
{
  virtual ~AbstractPredicate()
  {
  }
  virtual bool operator()(
      const TData&
    ) const = 0;
};

template <typename TData>
class CArray
{
  public:
    CArray();

    CArray(
        const CArray& _rhs
      );

    ~CArray();

    CArray& operator=(
        const CArray& _rhs
      );

    void print() const;

    void erase(
        unsigned int _index
      );

    void insert(
        unsigned int _index, const TData& _value
      );

    void push_back(
        const TData& _value
      );

    void clear();

    void sort();

    void eraseIf(
        const AbstractPredicate<TData>& _predicate
      );

    unsigned int size() const;

    const TData& operator[] (
        unsigned int _index
      ) const;

    TData& operator[] (
        unsigned int _index
      );

  protected:

    void quicksort(
        int _left, int _right
      );

    void realloc();

    TData& getElement(
        unsigned int _index
      ) const;

  protected:
    TData* array;
    unsigned int arr_size;
    unsigned int capacity;
};

}

#include "CArray.hpp"

#endif

