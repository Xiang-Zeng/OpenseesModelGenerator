#include <iostream>
#include <string>
#include <fstream>

#include "OpenseesModelGenerator.h"


using namespace std;

int main(int argc, char *argv[])
{
    //const int nor=100;  // number of realization
    OpenseesModelGenerator osm();

    //string dir="";

    //for(int i=0;i<nor;++i)
    //{
    //    osm.randPara();
    //    osm.writeModel();
    //}

    osm.randPara();
    osm.writeModel();

    return 0;
}
