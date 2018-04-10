#ifndef CArrayExceptionH
#define CArrayExceptionH

#include <exception>
#include <string>

class CArrayException : public std::exception {
    public:
        CArrayException(const std::string& reason) throw();
        const char* what() const throw();
    private:
        std::string reason;
};

#endif
