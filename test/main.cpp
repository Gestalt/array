#include <gmock/gmock.h>

#include "CArray.h"
#include "CRandom.h"
#include "CArrayException.h"

using namespace testing;

template<typename T>
struct All : arr::AbstractPredicate<T> {
    bool operator() (const T&) const {
        return true;
    }
};

TEST(EraseIf, DeletesElementIfPredicateConditionAccomplished) {
    arr::CArray<int> array;
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
    arr::CArray<int> array;
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
    arr::CArray<int> array;
    array.push_back(0);
    array.push_back(1);

    arr::CArray<int> copy(array);

    ASSERT_THAT(copy, isEqualToArray(array));
}

TEST(AssignmentOperator, MakesArrayCopy) {
    arr::CArray<int> array1;
    array1.push_back(0);
    array1.push_back(1);

    arr::CArray<int> array2;
    array2.push_back(2);
    array2.push_back(3);
    array2.push_back(4);

    array2 = array1;

    ASSERT_THAT(array2, isEqualToArray(array1));
}

TEST(Erase, DecreasesArraySize) {    arr::CArray<int> array;
    array.push_back(0);

    array.erase(0);

    ASSERT_THAT(array.size(), Eq(0));
}

TEST(Erase, ThrowsOnErasingOutOfRangeIndex) {
    arr::CArray<int> array;

    ASSERT_THROW(array.erase(1), arr::CArrayException);
}

TEST(Erase, DeletesElementAtRequiredIndexPosition) {
    arr::CArray<int> array;
    array.push_back(1);
    array.push_back(2);

    array.erase(0);

    ASSERT_THAT(array[0], Ne(1));
}

TEST(Erase, ShiftsArrayElementsToLeftAfterDeletedElement) {
    arr::CArray<int> array;
    array.push_back(0);
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    array.erase(1);

    ASSERT_THAT(array[1], Eq(2));
    ASSERT_THAT(array[2], Eq(3));
}

TEST(Insert, IncreasesArraySize) {
    arr::CArray<int> array;

    array.insert(0, 100);

    ASSERT_THAT(array.size(), Gt(0));
}

TEST(Insert, ThrowsOnInsertingOutOfRangeIndex) {
    arr::CArray<int> array;

    ASSERT_THROW(array.insert(1, 100), arr::CArrayException);
}

TEST(Insert, AddsElementAtRequiredIndexPosition) {
    arr::CArray<int> array;

    array.insert(0, 100);

    ASSERT_THAT(array[0], Eq(100));
}

TEST(Insert, ShiftsArrayElementsToRightAfterInsertedElement) {
    arr::CArray<int> array;
    array.push_back(0);
    array.push_back(1);
    array.push_back(2);

    array.insert(1, 100);

    ASSERT_THAT(array[2], Eq(1));
    ASSERT_THAT(array[3], Eq(2));
}

TEST(AccessOperator, ThrowsOnAccessingOutOfRangeIndex) {
    arr::CArray<int> array;
    array.push_back(0);

    ASSERT_THROW(array[1], arr::CArrayException);
}

TEST(AccessOperator, ReturnsArrayElementByIndex) {
    arr::CArray<int> array;

    array.push_back(0);
    array.push_back(1);
    array.push_back(2);

    ASSERT_THAT(array[1], Eq(1));
}

TEST(AccessOperator, ThrowsOnAccessingEmptyArray) {
    arr::CArray<int> array;

    ASSERT_THROW(array[0], arr::CArrayException);
}

TEST(Array, IsEmptyWhenCreated) {
    arr::CArray<int> array;

    ASSERT_THAT(array.size(), Eq(0u));
}

TEST(Array, IsNonEmptyWhenElementAdded) {
    arr::CArray<int> array;

    array.push_back(0);

    ASSERT_THAT(array.size(), Eq(1u));
}

TEST(PushBack, InsertsElementAtArrayEnd) {
    arr::CArray<int> array;

    array.push_back(100);

    ASSERT_THAT(array[0], Eq(100));
}

TEST(Clear, MakesArrayEmpty) {
    arr::CArray<int> array;
    array.push_back(0);

    array.clear();

    ASSERT_THAT(array.size(), Eq(0u));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
