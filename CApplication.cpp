#include "CApplication.h"
#include "CArray.h"
#include "CRandom.h"

struct ContainsLetter : arr::AbstractPredicate<std::string> {
    ContainsLetter(const char* const letters_)
        : letters(letters_) {
        }
    bool operator() (const std::string* const array, unsigned int index) const {
        const char* str = array[index].c_str();
        const size_t size = strlen(str);
        const size_t size_l = strlen(letters);

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size_l; j++) {
                if (str[i] == letters[j]) {
                    return true;
                }
            }
        }
        return false;
    }
    private:
        const char* const letters;
};

static void testInteger() {
    arr::CArray<int> array;

    // fill
    for (int i = 0; i < 20; i++) {
        array.push_back(app::CRandom::randomIntInRange(0, 100));
    }
    array.print();

    // sort
    array.sort();
    array.print();

    // remove every 2nd
    unsigned int j = 1;
    while (j < array.size()) {
        array.erase(j++);
    }
    array.print();

    // random insert
    for (int i = 0; i < 10; i++) {
        unsigned int ind = app::CRandom::randomIntInRange(0, (int)array.size());
        array.insert(ind, app::CRandom::randomIntInRange(0, 100));
    }
    array.print();

    // clear
    array.clear();
    array.print();
}

static void testString() {
    arr::CArray<std::string> array;

    // fill array
    for (int i = 0; i < 15; i++) {
        array.push_back(app::CRandom::randomString());
    }
    array.print();

    // sort
    array.sort();
    array.print();

    // remove if match
    ContainsLetter predicate("abcde");
    array.eraseIf(predicate);
    array.print();

    // random insert
    for (int i = 0; i < 3; i++) {
        unsigned int ind = app::CRandom::randomIntInRange(0, (int)array.size());
        array.insert(ind, app::CRandom::randomString());
    }
    array.print();
}

int app::CApplication::process() {
    testInteger();
    testString();

    return 0;
}

