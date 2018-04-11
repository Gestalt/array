#ifndef CRandomH
#define CRandomH

#include <string>

namespace app
{

class CRandom
{
  public:

    static int randomIntInRange(
        int _from, int _to
      );

    static const std::string randomString();
};

}

#endif

