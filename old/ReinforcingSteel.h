#ifndef REINFORCINGSTEEL_H
#define REINFORCINGSTEEL_H

#include "Steel.h"
#include <sstream>

class ReinforcingSteel : public Steel
{
public:
    ReinforcingSteel();

    string  toTcl();

    double fu=0.0;
    double Esh=0.0;
    double esh=0.0;
    double eult=0.0;
};

#endif // REINFORCINGSTEEL_H
