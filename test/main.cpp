#include <gmock/gmock.h>

#include "CArray.h"
#include "CRandom.h"
#include "CArrayException.h"

using namespace testing;

template<typename T>
struct All : AbstractPredicate<T> {
    bool operator() (const T* const array, unsigned int index) const {
        return true;
    }
};

TEST(EraseIf, DeletesElementIfPredicateConditionAccomplished) {
    CArray<int> array;
    array.push_back(0);
    array.push_back(1);
    array.push_back(2);

    All<int> allPredicate;
    array.eraseIf(allPredicate);

    ASSERT_THAT(array.size(), Eq(0));
}

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

    ASSERT_THROW(array.erase(1), CArrayException);
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

    ASSERT_THROW(array.insert(1, 100), CArrayException);
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

    ASSERT_THROW(array[1], CArrayException);
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

    ASSERT_THROW(array[0], CArrayException);
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
