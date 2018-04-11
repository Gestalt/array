#include <iostream>
#include "CApplication.h"
#include "CArrayException.h"

int main(int argc, char** argv) {
    try {
        return app::CApplication::process();
    } catch (const arr::CArrayException& ex) {
        std::cout << "CArrayException occured: " << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknown exception occured" << std::endl;
        return 1;
    }
    return 0;
}
