#ifndef CONCRETE02_H
#define CONCRETE02_H

#include "Concrete.h"
#include <sstream>

class Concrete02 : public Concrete
{
public:
    Concrete02();

    double lambda=0.0;
    double ft=0.0;
    double Ets=0.0;
    string  toTcl();
};

#endif // CONCRETE02_H
