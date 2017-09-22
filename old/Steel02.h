#ifndef STEEL02_H
#define STEEL02_H

#include "Steel.h"
#include <sstream>

class Steel02 : public Steel
{
public:
    Steel02();

    string  toTcl();

    double b=0.0;
    double R0=0.0;
    double cR1=0.925;
    double cR2=0.15;

};

#endif // STEEL02_H
