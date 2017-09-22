#ifndef OPENSEESMODELGENERATOR_H
#define OPENSEESMODELGENERATOR_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <direct.h>
#include <math.h>

//#include "Steel02.h"
//#include "ReinforcingSteel.h"
//#include "Concrete01.h"
//#include "Concrete02.h"

using namespace std;

class OpenseesModelGenerator
{
public:

    struct Bound{
        double min=0.0;
        double max=0.0;
    };

    OpenseesModelGenerator(
        int seed=0,
        string randPath="randPara.txt",
        string framePath="model/frame.tcl",
        string nodePath="model/node.tcl",
        string elementPath="model/element.tcl"
    );

    void ReadRandPara();
    //void GenRandPara();
    double random(double min=0.0, double max=1.0);
	int round(double r);

    //void WriteModel();
    //void WriteMain();
    //void WriteSteel();
    //void WriteConcrete();
    //void WriteSection();

    void WriteModel(int id);
	void WriteModelHan(int id);

    //vector<Steel *> steel;
    //vector<Concrete *> concrete;
    //vector<Concrete *> confinedCon;


private:
    int _seed;
    string _randPath;
    string _framePath;
    string _nodePath;
    string _elementPath;

    map<string,Bound> _randParas;

};

#endif // OPENSEESMODELGENERATOR_H
