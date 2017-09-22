#include "Steel02.h"

Steel02::Steel02()
{

}

string Steel02::toTcl()
{
    stringstream ss;
    ss<<"uniaxialMaterial Steel02\t"<<tag<<"\t"<<fy<<"\t"<<E0<<"\t"
      <<b<<"\t"<<R0<<"\t"<<cR1<<"\t"<<cR2<<"\n";
    return ss.str();
}
