#ifndef CRandomH
#define CRandomH

#include <string>

class CRandom {
    public:
    static int randomIntInRange(int from, int to);
    static const std::string randomString();
};

#endif
