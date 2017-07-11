#include "Concrete01.h"

Concrete01::Concrete01()
{

}

string Concrete01::toTcl()
{
    stringstream ss;
    ss<<"uniaxialMaterial Concrete01\t"<<tag<<"\t"<<fpc<<"\t"<<epsc0<<"\t"
      <<fpcu<<"\t"<<epsU<<"\n";
    return ss.str();
}
