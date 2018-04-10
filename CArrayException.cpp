#include "CArrayException.h"

CArrayException::CArrayException(const std::string& reason_) throw()
    : reason(reason_) {
}

const char* CArrayException::what() const throw() {
    return reason.c_str();
}
