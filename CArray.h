#ifndef CArrayH
#define CArrayH

namespace arr {

template<typename TData>
struct AbstractPredicate {
    virtual ~AbstractPredicate() {}
	virtual bool operator()(const TData&) const = 0;
};

template <typename TData>
class CArray {
    public:
        CArray();
        CArray(const CArray& rhs);
        ~CArray();

        CArray& operator=(const CArray& rhs);

        void print() const;
        void erase(unsigned int index);
        void insert(unsigned int index, const TData& value);
        void push_back(const TData& value_);
        void clear();
        void sort();
        void eraseIf(const AbstractPredicate<TData>& predicate);
        unsigned int size() const;
        const TData& operator[] (unsigned int index) const;
        TData& operator[] (unsigned int index);
    protected:
        void quicksort(int left, int right);
        void realloc();
        TData& getElement(unsigned int index) const;
    protected:
        TData* array;
        unsigned int arr_size;
        unsigned int capacity;
};

}

#include "CArray.hpp"

#endif

