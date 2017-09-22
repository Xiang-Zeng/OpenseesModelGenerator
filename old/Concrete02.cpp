#include "Concrete02.h"

Concrete02::Concrete02()
{

}

string Concrete02::toTcl()
{
    stringstream ss;
    ss<<"uniaxialMaterial Concrete02\t"<<tag<<"\t"<<fpc<<"\t"<<epsc0<<"\t"
      <<fpcu<<"\t"<<epsU<<"\t"<<lambda<<"\t"<<ft<<"\t"<<Ets<<"\n";
    return ss.str();
}

