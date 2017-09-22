#ifndef CONCRETE_H
#define CONCRETE_H

#include <string>
using namespace std;

class Concrete
{
public:
    Concrete();

    virtual string toTcl()=0;

    int tag=0;
    double fpc=0.0;
    double epsc0=0.0;
    double fpcu=0.0;
    double epsU=0.0;
};

#endif // CONCRETE_H
