#include "ReinforcingSteel.h"

ReinforcingSteel::ReinforcingSteel()
{

}

string ReinforcingSteel::toTcl()
{
    stringstream ss;
    ss<<"uniaxialMaterial ReinforcingSteel\t"<<tag<<"\t"<<fy<<"\t"<<fu<<"\t"<<E0<<"\t"
      <<Esh<<"\t"<<esh<<"\t"<<eult<<"\n";
    return ss.str();
}
