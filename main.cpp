#include <iostream>
#include <string>
#include <fstream>

#include "OpenseesModelGenerator.h"


using namespace std;

int main()
{
    const int nor=100;  // number of realization
    OpenseesModelGenerator osm(0);

    //string dir="";

    //for(int i=0;i<nor;++i)
    //{
    //    osm.randPara();
    //    osm.writeModel();
    //}


    //osm.GenRandPara();
    for(int i=0;i<nor;++i)
    {
        cout<<i<<"\t";
        osm.WriteModel(i);
    }


    return 0;
}
