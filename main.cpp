#include <iostream>
#include <string>
#include <fstream>

#include "OpenseesModelGenerator.h"


using namespace std;

int main()
{
    //const int nor=100;  // number of realization
    OpenseesModelGenerator osm(0);

    //string dir="";

    //for(int i=0;i<nor;++i)
    //{
    //    osm.randPara();
    //    osm.writeModel();
    //}

    osm.GenRandPara();
    osm.WriteModel();

    return 0;
}
