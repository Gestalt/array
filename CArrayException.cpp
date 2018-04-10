#include "CArrayException.h"

arr::CArrayException::CArrayException(const std::string& reason_) throw()
    : reason(reason_) {
}

const char* arr::CArrayException::what() const throw() {
    return reason.c_str();
}
