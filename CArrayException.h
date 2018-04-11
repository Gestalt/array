#ifndef CArrayExceptionH
#define CArrayExceptionH

#include <exception>
#include <string>

namespace arr
{

class CArrayException : public std::exception
{
  public:
    CArrayException(
        const std::string& _reason
      ) throw();
    const char* what() const throw();
  private:
    std::string reason;
};

}

#endif

