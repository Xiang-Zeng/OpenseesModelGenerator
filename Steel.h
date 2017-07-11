#ifndef STEEL_H
#define STEEL_H

#include <string>
using namespace std;

class Steel
{
public:
    Steel();
    virtual string toTcl()=0;

    int tag=0;
    double fy=0.0;
    double E0=0.0;
};

#endif // STEEL_H
