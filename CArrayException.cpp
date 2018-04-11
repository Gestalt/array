#include "CArrayException.h"

arr::CArrayException::CArrayException(
    const std::string& _reason
  ) throw() : reason(_reason)
{
}

const char* arr::CArrayException::what() const throw()
{
    return reason.c_str();
}
