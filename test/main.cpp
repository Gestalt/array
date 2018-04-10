#include <iostream>
#include <exception>
#include <stdio.h>
#include <vector>

#include <gmock/gmock.h>

using namespace std;
using namespace testing;

template <typename TData>
class CArray {
    public:
        CArray()
            : array(0)
            , arr_size(0u)
            , capacity(0u) {
        }

        CArray(const CArray& rhs)
            : array(0)
            , arr_size(rhs.arr_size)
            , capacity(rhs.capacity) {
                array = new TData[rhs.capacity];
                memcpy(&array[0], &rhs.array[0], rhs.arr_size * sizeof(TData));
        }

        ~CArray() {
            if (array) {
                delete[] array;
                array = 0;
            }
        }

        CArray& operator=(const CArray& rhs) {
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

        void print() const {
            std::cout << "Elements: |";
            for (unsigned int i = 0; i < arr_size; i++) {
                std::cout << array[i] << "|";
            }
            std::cout << std::endl;
        }

        void erase(unsigned int index) {
            if (index > arr_size) {
                throw std::exception();
            }

            for (unsigned int i = index; i < arr_size; i++) {
                array[i] = array[i + 1];
            }
            arr_size--;
        }

        void insert(unsigned int index, const TData& value) {
            if (index > arr_size) {
                throw std::exception();
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

        void push_back(const TData& value_) {
            if (arr_size == capacity) {
                realloc();
            }
            array[arr_size] = value_;
            arr_size++;
        }

        unsigned int size() const {
            return arr_size;
        }

        void clear() {
            arr_size = 0u;
            delete[] array;
            array = 0;
        }

        const TData& operator[] (unsigned int index) const {
            return getElement(index);
        }

        TData& operator[] (unsigned int index) {
            return getElement(index);
        }

        void sort() {
            quicksort(0, (int)(arr_size - 1));
        }

    protected:
        void quicksort(int left, int right) {
            int i = left;
            int j = right;
            const TData& mid = array[ (i + j) / 2 ];
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

        void realloc() {
            capacity = (capacity == 0) ? (1u) : (capacity * 2);

            TData* buff = new TData[capacity];

            if (array) {
                memcpy(&buff[0], &array[0], size() * sizeof(TData));
                delete[] array;
            }
            array = buff;
        }

        TData& getElement(unsigned int index) const {
            if (arr_size == 0 || index > arr_size - 1) {
                throw std::exception();
            }

            return array[index];
        }
    protected:
        TData* array;
        unsigned int arr_size;
        unsigned int capacity;
};

MATCHER(isSorted, "") {
    for (unsigned int i = 0; i < arg.size() - 1; i++) {
        if (arg[i] > arg[i + 1]) {
            return false;
        }
    }
    return true;
}

TEST(Sort, RearrangesArrayElementsInIncreasingOrder) {
    CArray<int> array;
    array.push_back(3);
    array.push_back(4);
    array.push_back(0);
    array.push_back(1);
    array.push_back(4);

    array.sort();

    ASSERT_THAT(array, isSorted());
}

MATCHER_P(isEqualToArray, target, "") {
    if (target.size() != arg.size()) {
        return false;
    }
    for (unsigned int i = 0; i < arg.size(); i++) {
        if (target[i] != arg[i]) {
            return false;
        }
    }
  return true;
}

TEST(CopyConstructor, MakesArrayCopy) {
    CArray<int> array;
    array.push_back(0);
    array.push_back(1);

    CArray<int> copy(array);

    ASSERT_THAT(copy, isEqualToArray(array));
}

TEST(AssignmentOperator, MakesArrayCopy) {
    CArray<int> array1;
    array1.push_back(0);
    array1.push_back(1);

    CArray<int> array2;
    array2.push_back(2);
    array2.push_back(3);
    array2.push_back(4);

    array2 = array1;

    ASSERT_THAT(array2, isEqualToArray(array1));
}

TEST(Erase, DecreasesArraySize) {    CArray<int> array;
    array.push_back(0);

    array.erase(0);

    ASSERT_THAT(array.size(), Eq(0));
}

TEST(Erase, ThrowsOnErasingOutOfRangeIndex) {
    CArray<int> array;

    ASSERT_THROW(array.erase(1), std::exception);
}

TEST(Erase, DeletesElementAtRequiredIndexPosition) {
    CArray<int> array;
    array.push_back(1);
    array.push_back(2);

    array.erase(0);

    ASSERT_THAT(array[0], Ne(1));
}

TEST(Erase, ShiftsArrayElementsToLeftAfterDeletedElement) {
    CArray<int> array;
    array.push_back(0);
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    array.erase(1);

    ASSERT_THAT(array[1], Eq(2));
    ASSERT_THAT(array[2], Eq(3));
}

TEST(Insert, IncreasesArraySize) {
    CArray<int> array;

    array.insert(0, 100);

    ASSERT_THAT(array.size(), Gt(0));
}

TEST(Insert, ThrowsOnInsertingOutOfRangeIndex) {
    CArray<int> array;

    ASSERT_THROW(array.insert(1, 100), std::exception);
}

TEST(Insert, AddsElementAtRequiredIndexPosition) {
    CArray<int> array;

    array.insert(0, 100);

    ASSERT_THAT(array[0], Eq(100));
}

TEST(Insert, ShiftsArrayElementsToRightAfterInsertedElement) {
    CArray<int> array;
    array.push_back(0);
    array.push_back(1);
    array.push_back(2);

    array.insert(1, 100);

    ASSERT_THAT(array[2], Eq(1));
    ASSERT_THAT(array[3], Eq(2));
}

TEST(AccessOperator, ThrowsOnAccessingOutOfRangeIndex) {
    CArray<int> array;
    array.push_back(0);

    ASSERT_THROW(array[1], std::exception);
}

TEST(AccessOperator, ReturnsArrayElementByIndex) {
    CArray<int> array;

    array.push_back(0);
    array.push_back(1);
    array.push_back(2);

    ASSERT_THAT(array[1], Eq(1));
}

TEST(AccessOperator, ThrowsOnAccessingEmptyArray) {
    CArray<int> array;

    ASSERT_THROW(array[0], std::exception);
}

TEST(Array, IsEmptyWhenCreated) {
    CArray<int> array;

    ASSERT_THAT(array.size(), Eq(0u));
}

TEST(Array, IsNonEmptyWhenElementAdded) {
    CArray<int> array;

    array.push_back(0);

    ASSERT_THAT(array.size(), Eq(1u));
}

TEST(PushBack, InsertsElementAtArrayEnd) {
    CArray<int> array;

    array.push_back(100);

    ASSERT_THAT(array[0], Eq(100));
}


TEST(Clear, MakesArrayEmpty) {
    CArray<int> array;
    array.push_back(0);

    array.clear();

    ASSERT_THAT(array.size(), Eq(0u));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
