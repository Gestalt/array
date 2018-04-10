#include <stdlib.h>
#include "CRandom.h"

int CRandom::randomIntInRange(int from, int to) {
    return rand() % (from - to - 1) + from;
}

const std::string CRandom::randomString() {
    static const char letters[] = "abcdefghijklmnopqrstuvwxyz";
    static const int stringLength = 5;

    std::string res;
    for (int i = 0; i < stringLength; i++) {
        res += std::string(1, letters[CRandom::randomIntInRange(0, strlen(letters)-1)]);
    }
    return res;
}
